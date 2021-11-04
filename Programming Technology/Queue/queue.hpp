#ifndef queue_hpp
#define queue_hpp
struct elementQueue
{
    int value = 0; //значение элемента очереди
    //int number = 0;
    elementQueue *prevEl = 0; //ссылка на предыдущий элемент очереди
};
class Queue
{
private:
    elementQueue *tail = 0; //конец очереди
protected:
    int size; //размер очереди
    elementQueue *qetTail();

public:
    Queue();  //конструктор очереди
    ~Queue(); //деструктор
    void push(int Value);
    int pop();
    void showQueue();
    void copyQueue(Queue &obj);
    void merge(Queue &obj1, Queue &obj2);
    bool isEmpty();
    int return_size();
};
#endif
файл queue.cpp
#include "queue.hpp"
#include <iostream>
    using namespace std;
Queue::Queue()
{ //конструктор очереди
    size = 0;
}
Queue::~Queue()
{ //деструктор очереди
    while (size > 0)
    {
        elementQueue *buffer = tail;
        tail = buffer->prevEl;
        delete buffer;
        size--;
    }
}
void Queue::push(int value)
{ //добавление элементов в конец очереди (value
значение элемента, который добавляем)
 elementQueue *newEl = new(elementQueue); //выделила память под новый элемент
newEl->prevEl = tail;                     //ссылка на предыдущий элемент
newEl->value = value;
tail = newEl; // конец очереди поменялся
size++;
}
int Queue::pop(void)
{ //извлечет первый элемент из очереди
    if (size == 1)
    {
        int firstVal = tail->value; // запомнила значение первого элемента в
        очереди
        tail = 0;
        size--;
        return firstVal;
    }
    elementQueue *buf = tail;
    while (buf->prevEl->prevEl != 0) //???
    {
        buf = buf->prevEl; // дошла до второго элемента в очереди
    }
    elementQueue *firstEl = buf->prevEl; //запомнила 1 элемент очереди
    int firstVal = firstEl->value;       // запомнила значение первого элемента в
    очереди
    buf->prevEl = 0; //обнулила ссылку второго элемента на предыдущий элемент
    delete firstEl;  // удалила первый элемент очереди
    size--;
    return firstVal;
}
void Queue::showQueue()
{
    elementQueue *firstEl = tail;
    while (firstEl->prevEl != 0)
    {
        cout << firstEl->value << " <- ";
        firstEl = firstEl->prevEl;
    }
    cout << firstEl->value << endl;
}
void Queue::copyQueue(Queue &obj)
{
    int *masValueQueue = new int[obj.size];
    elementQueue *buffer = obj.tail;
    for (int i = obj.size - 1; i >= 0; i--)
    {
        masValueQueue[i] = buffer->value;
        buffer = buffer->prevEl;
    }
    for (int i = 0; i < obj.size; i++)
    {
        this->push(masValueQueue[i]);
    }
    delete[] masValueQueue;
    this->showQueue();
}
void Queue::merge(Queue &obj1, Queue &obj2)
{
    int *masValueQueue = new int[obj1.size];
    elementQueue *buffer = obj1.tail;
    for (int i = obj1.size - 1; i >= 0; i--) //расположила элементы первого
        списка в правильном порядке
        {
            masValueQueue[i] = buffer->value;
            buffer = buffer->prevEl;
        }
    for (int i = 0; i < obj1.size; i++) // записала в новый массив элементы
        первого списка в правильном порядке this->push(masValueQueue[i]);
    delete[] masValueQueue;
    int *masValueQueue2 = new int[obj2.size];
    buffer = obj2.tail;
    for (int i = obj2.size - 1; i >= 0; i--) //расположила элементы второго
        списка в правильном порядке
        {
            masValueQueue2[i] = buffer->value;
            buffer = buffer->prevEl;
        }
    for (int i = 0; i < obj2.size; i++) // добавила в новый массив элементы
        второго списка в правильном порядке this->push(masValueQueue2[i]);
    delete[] masValueQueue2;
    this->showQueue();
}
elementQueue *Queue::qetTail()
{
    return tail;
}
int Queue::return_size()
{
    return size;
}
bool Queue::isEmpty()
{
    if (size == 0)
    {
        cout << "Очередь пуста" << endl;
        return true;
    }
    return false;
}