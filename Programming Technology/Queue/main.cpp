#include "child.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
template <class T> //шаблон
void workWithClass(T *queue, int n)
{
    int v;              //выбор
    int counter = 0;    //номер очереди, в которой работаем
    int counterEnd = 1; // номер последней созданной очереди
    int order;          // выбор очереди
    int a = 1;
    while (a)
    {
        int buffer;
        cout << "Используется очередь № " << counter + 1 << endl;
        cout << "|1| - Добавление элемента очереди" << endl;
        cout << "|2| - Извлечение элемента из очереди" << endl;
        cout << "|3| - Вывод очереди на экран" << endl;
        cout << "|4| - Нахождение среднего арифметического элементов с нечетными
            номерами " << endl;
            cout
             << "|5| - Создание копии очереди" << endl;
        cout << "|6| - Слияние очередей" << endl;
        cout << "|7| - Выбор другой очереди" << endl;
        cout << "|8| - Выход" << endl;
        cin >> v;
        int value;
        int size;
        switch (v)
        {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            queue[counter].push(value);
            cout << "Элемент добавлен" << endl;
            break;
        case 2:
            if (queue[counter].isEmpty())
            {
                break;
            }
            buffer = queue[counter].pop();
            cout << "Извлечен элемент " << buffer << endl;
            break;
        case 3:
            if (queue[counter].isEmpty())
            {
                break;
            }
            cout << "Очередь состоит из" << endl;
            queue[counter].showQueue();
            break;
        case 4:
            if (queue[counter].isEmpty())
            {
                {
                    break;
                }
            }
            size = queue[counter].return_size();
            cout << "колво элементов в очереди: " << size << endl;
            cout << "Среднее арифметическое элементов с нечетными номерами:" << queue[counter].average_value(size) << endl;
            break;
        case 5:
            if (queue[counter].isEmpty())
            {
                break;
            }
            queue[counterEnd].copyQueue(queue[counter]); //queue[counterEnd] -
            новая очередь и в нее копируем данные из нынешней
                    cout
                << "Очередь скопирована. Номер очереди " << (counterEnd + 1) << endl;
            break;
        case 6:
            if (queue[counter].isEmpty())
            {
                break;
            }
            if (counterEnd == 1)
            {
                cout << "Существует только одна очередь" << endl;
                break;
            }
            cout << "С какой очередью будет произведено слияние? (1 - " << counterEnd << ") : ";
            cin >> order;
            order--;

            if ((order < 0) || (order == counter) || (order >= counterEnd))
            {
                cout << "Некорректное значение. Объединение не произведено" << endl;
                break;
            }
            queue[counterEnd].merge(queue[counter], queue[order]);
            cout << "Объединение произведено. Номер очереди результата: " << counterEnd++ << endl;
            break;
        case 7:
            if (n == 1)
            {
                cout << "существует только одна очередь" << endl;
                break;
            }
            cout << "Номер очереди, на которую следует переключиться: (1 - " << n << ") : ";
            cin >> order;
            order--;
            if ((order < 0) || (order == counter) || (order >= n))
                cout << "Некорректное значение. Переключение не выполнено" << endl;
            else
                counter = order;
            break;
        case 8:
            a = 0;
            break;
        default:
            cout << "некорректный ввод";
            break;
        }
    }
}
int main()
{
    int v; //выбор
    int n;
    ChildQueuePublic *queue1 = 0;
    ChildQueueProtected *queue2 = 0;
    ChildQueuePrivate *queue3 = 0;
    cout << "Введите количество очередей" << endl;
    cin >> n;
    //cout << "колво очередей" << n << endl;
    cout << "Какой тип наследования будет у производного класса?" << endl;
    cout << "|1| - public" << endl;
    cout << "|2| - protected" << endl;
    cout << "|3| - private" << endl;
    cin >> v;
    switch (v)
    {
    case 1:
        queue1 = new ChildQueuePublic[n];
        //cout << "колво очередей" << n << endl;
        workWithClass(queue1, n);
        delete[] queue1;
        break;
    case 2:
        queue2 = new ChildQueueProtected[n];
        workWithClass(queue2, n);
        delete[] queue2;
        break;
    case 3:
        queue3 = new ChildQueuePrivate[n];
        workWithClass(queue3, n);
        delete[] queue3;
        break;
    default:
        cout << "некорректный ввод";
        break;
    }
    return 1;
}