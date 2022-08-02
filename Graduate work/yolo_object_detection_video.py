# Подключение необходимых для работы библиотек
import numpy as np
import imutils
import time
import cv2

# Функция для обнаружения опасной зоны
def overlap(point_l1, point_r1, point_l2, point_r2):
    if (point_l1[0] > point_r2[0] or point_l2[0] > point_r1[0]):
        return False
    if (point_l1[1] > point_r2[1] or point_l2[1] > point_r1[1]):
        return False
    return True

# Шрифт
font = cv2.FONT_HERSHEY_PLAIN

#Загрузка алгоритма Yolov3, предобученного на датасете COCO(80 классов)
net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")

# Запись объектов из датасета COCO в массив построчно
classes = []
with open("coco.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]
#print(classes)

# Определение "выходных слоев", необходимых для дальнейшей работы
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]
#print(output_layers)
#COLORS = np.random.randint(0, 255, size=(len(classes), 3), dtype="uint8")


# Инициализация видеопотока
vs = cv2.VideoCapture("test_video.avi")

#Настройка скорости воспроизведения видео
fps = vs.get(cv2.CAP_PROP_FRAME_COUNT)
print("Frames per second using video.get(cv2.cv.CV_CAP_PROP_FPS): {0}".format(fps))

# Указатель на выходной видеофайл
writer = None
# Размеры рамки
(W, H) = (None, None)

# Попытка определить общее количество кадров во входном видеофайле
try:
    prop = cv2.cv.CV_CAP_PROP_FRAME_COUNT if imutils.is_cv2() \
        else cv2.CAP_PROP_FRAME_COUNT
    total = int(vs.get(prop))
    print("[INFO] Всего {} кадров в видеофайле.".format(total))

# Если произошла ошибка при определении общего числа кадров в видеофайле
except:
    print("[INFO] Не удалось определить общее число кадров в видеофайле!")
    print("[INFO] Время до завершения работы программы не может быть вычислено!")
    total = -1
#test_total = int(total/7)
# Цикл по всем кадрам из входного видефайла
while True:
#for i in range(0, test_total):

    # Чтение следующего кадра из файла
    (grabbed, frame) = vs.read()

    # Если кадр не был получет, то закончитьь цикл
    if not grabbed:
        break

    # Опредеение размеров ограничивающей рамки
    if W is None or H is None:
        (H, W) = frame.shape[:2]
        #print((H, W))

    # Создание "blob" для передачи в Yolov3
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    net.setInput(blob)

    # Работа детектора Yolo
    start = time.time()
    outs = net.forward(output_layers)
    end = time.time()

    # Инициализация массивов
    class_ids = []
    confidences = []
    boxes = []

    # Цикл по всем выходным слоям
    for out in outs:

        # Цикл по каждому обнаружению
        for detection in out:

            # Извлечение id класса объекта и вероятности обнаружения
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]

            # Если вероятность обнаружения больше 50%
            if confidence > 0.5:

                # Объект обнаружен, записываем центр рамки, высоту и ширину
                box = detection[0:4] * np.array([W, H, W, H])
                (center_x,center_y, width,height) = box.astype("int")
                # print(center_x, center_y)
                # print(w, h)

                # Вычисление координат начала ограничивающей рамки
                x = int(center_x - (width / 2))
                y = int(center_y - (height / 2))

                # Обновление массива ограничивающих рамок с учетом вычисленных значений
                boxes.append([x, y, int(width), int(height)])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    # Если для одного объекта было найдено несколько ограничительных рамок, выполняем подавление
    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)

    # Проверка количества сохраненных индексов
    if len(indexes) > 0:

        # Цикл по сохраненным индексам
        for i in indexes.flatten():
            x, y, w, h = boxes[i]

            # Проверка условия на опасную зону и отрисовка ограничивающей рамки
            if (overlap((x, y), (x + w, y + h), (round(W / 2.5), 550), (round(W / 1.7), H)) is True):
                #print("True")

                # Если объект находится в опасной зоне, то рамка - красного цвета, надпись "danger!!!",
                # что означает "опасно!!!"
                label = "danger!!!: {:.0f}%".format(confidences[i]*100)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
                cv2.putText(frame, label, (x, y - 10), font, 1.5, (255, 0, 0), 2)

            else:
                #print("False")

                # Если объект в безопасной зоне, рамка - черная, надпись - название класса объекта
                # + вероятность обнаружения
                label = "{}: {:.0f}%".format(classes[class_ids[i]], confidences[i]*100)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 255), 2)
                cv2.putText(frame, label, (x, y - 10), font, 1.5, (0, 0, 0), 2)

    if writer is None:

        # Инициализация video-writer
        fourcc = cv2.VideoWriter_fourcc(*'DIVX')
        writer = cv2.VideoWriter('yesdtp_result.avi', fourcc, 30, (frame.shape[1], frame.shape[0]), True)

        # Вывод некоторой информациии об обработке кадров
        if total > 0:
            elap = (end - start)
            print("[INFO] Обработка одного кадра заняла: {:.4f} секунд.".format(elap))
            print("[INFO] Примерное время до завершения работы программы: {:.4f} секунд.".format(
                elap * total))

    # Запись выходных кадров
    writer.write(frame)

# Очистка всех указателей
writer.release()
vs.release()
