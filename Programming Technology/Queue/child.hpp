#ifndef child_hpp
#define child_hpp
#include "queue.hpp"
class ChildQueuePublic : public Queue
{
public:
    int average_value(int size);
};
class ChildQueueProtected : protected Queue
{
public:
    int average_value(int size);
    void push(int Value);
    int pop();
    int return_size();
    void showQueue();
    void copyQueue(ChildQueueProtected &obj);
    void merge(ChildQueueProtected &obj1, ChildQueueProtected &obj2);
    bool isEmpty();
};
class ChildQueuePrivate : private Queue
{
public:
    int average_value(int size);
    void push(int Value);
    int pop();
    int return_size();
    void showQueue();
    void copyQueue(ChildQueuePrivate &obj);
    void merge(ChildQueuePrivate &obj1, ChildQueuePrivate &obj2);
    bool isEmpty();
};
#endif /* child_hpp */