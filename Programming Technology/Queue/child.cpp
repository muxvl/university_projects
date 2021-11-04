#include "child.hpp"
#include <iostream>
int ChildQueuePublic::average_value(int size)
{
    elementQueue *tail = qetTail();
    float average = 0;
    int sum = 0;
    int i = 0;
    elementQueue *buf = tail;
    do
    {
        buf = buf->prevEl;
        if ((size % 2) != 0)
        {
            sum += buf->value;
            size--;
            i++;
        }
    } while (buf->prevEl != 0);
    average = float(sum / i);
    return average;
}
int ChildQueueProtected::pop()
{
    return Queue::pop();
}
int ChildQueueProtected::return_size()
{
    return Queue::return_size();
}
void ChildQueueProtected::push(int Value)
{
    return Queue::push(Value);
}
void ChildQueueProtected::showQueue()
{
    return Queue::showQueue();
}
void ChildQueueProtected::copyQueue(ChildQueueProtected &obj)
{
    return Queue::copyQueue(obj);
}
void ChildQueueProtected::merge(ChildQueueProtected &obj1, ChildQueueProtected &
                                                               obj2)
{
    return Queue::merge(obj1, obj2);
}
bool ChildQueueProtected::isEmpty()
{
    return Queue::isEmpty();
}
int ChildQueueProtected::average_value(int size)
{
    elementQueue *tail = qetTail();
    float average = 0;
    int sum = 0;
    int i = 0;
    elementQueue *buf = tail;
    do
    {
        buf = buf->prevEl;
        if ((size % 2) != 0)
        {
            sum += buf->value;
            size--;
            i++;
        }
    } while (buf->prevEl != 0);
    average = float(sum / i);
    return average;
}
int ChildQueuePrivate::pop()
{
    return Queue::pop();
}
int ChildQueuePrivate::return_size()
{
    return Queue::return_size();
}
void ChildQueuePrivate::push(int Value)
{
    return Queue::push(Value);
}
void ChildQueuePrivate::showQueue()
{
    return Queue::showQueue();
}
void ChildQueuePrivate::copyQueue(ChildQueuePrivate &obj)
{
    return Queue::copyQueue(obj);
}
void ChildQueuePrivate::merge(ChildQueuePrivate &obj1, ChildQueuePrivate &obj2)
{
    return Queue::merge(obj1, obj2);
}
bool ChildQueuePrivate::isEmpty()
{
    return Queue::isEmpty();
}
int ChildQueuePrivate::average_value(int size)
{
    elementQueue *tail = qetTail();
    float average = 0;
    int sum = 0;
    int i = 0;
    elementQueue *buf = tail;
    do
    {
        buf = buf->prevEl;
        if ((size % 2) != 0)
        {
            sum += buf->value;
            size--;
            i++;
        }
    } while (buf->prevEl != 0);
    average = float(sum / i);
    return average;
}