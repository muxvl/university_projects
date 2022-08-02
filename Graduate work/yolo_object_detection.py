import cv2
import numpy as np
import imutils
import time
import os
import glob

def overlap(point_l1, point_r1, point_l2, point_r2):
    if (point_l1[0] > point_r2[0] or point_l2[0] > point_r1[0]):
        return False
    if (point_l1[1] > point_r2[1] or point_l2[1] > point_r1[1]):
        return False
    return True

# Load Yolo
net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")
classes = []
with open("coco.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]
print(classes)
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()] #получаем выходные слои для результатов
print(output_layers)
#colors = np.random.uniform(0, 255, size=(len(classes), 3)) #??

# Loading image
img = cv2.imread("p_test.jpeg")
#img = cv2.resize(img, None, fx=1, fy=1)
height, width, channels = img.shape
#print(img.shape)


# Detecting objects
blob = cv2.dnn.blobFromImage(img, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

#for b in blob:
#    for n, img_blob in enumerate(b):
#        cv2.imshow(str(n), img_blob)

net.setInput(blob)
outs = net.forward(output_layers)
#print(outs)

# Showing informations on the screen
class_ids = []
confidences = []
boxes = []
for out in outs:
    for detection in out:
        scores = detection[5:]
        class_id = np.argmax(scores)
        confidence = scores[class_id]

        if confidence > 0.5:
            #print(scores)
            #print(class_id)
            #print(confidence)
            # Object detected
            center_x = int(detection[0] * width)
            center_y = int(detection[1] * height)
            w = int(detection[2] * width)
            h = int(detection[3] * height)
            #print(center_x, center_y)
            #print(w, h)
            # Rectangle coordinates
            x = int(center_x - w / 2)
            y = int(center_y - h / 2)

            boxes.append([x, y, w, h])
            confidences.append(float(confidence))
            class_ids.append(class_id)

indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)
#print(indexes)
font = cv2.FONT_HERSHEY_PLAIN #шрифт
for i in range(len(boxes)):
    if i in indexes:
        #print(class_ids[i])
        #print(boxes[i][2])
        #if int(class_ids[i]) == 2: #если обнаружена машина
            x, y, w, h = boxes[i]
            print("overlap:")
            print(x,y)
            print(x + w, y + h)
            print(round(width / 2.5), 550)
            print(round(width / 1.7), height)
            if (overlap((x, y), (x + w, y + h), (round(width / 2.5), 550), (round(width / 1.7), height)) is True):
                print("True")
            #if boxes[i][2] > 300:
                #label = str(classes[class_ids[i]])
                label = "danger!!!: {:.0f}%".format(confidences[i]*100)
                #print(classes[class_ids[i]], class_ids[i])
                #color = colors[class_ids[i]]
                cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
                cv2.putText(img, label, (x, y - 10), font, 1.5, (255, 0, 0), 2)
            else:
                print("False")
                label = "{}: {:.0f}%".format(classes[class_ids[i]], confidences[i]*100)
                #color = colors[class_ids[i]]
                cv2.rectangle(img, (x, y), (x + w, y + h), (255, 255, 255), 2)
                cv2.putText(img, label, (x, y - 10), font, 1.5, (0, 0, 0), 2)

cv2.imshow("Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()