#ifndef spisok_hpp
#define spisok_hpp
#include <iostream>
#include <stdio.h>
using namespace std;
class List
{
public:
    List();
    ~List();
    List(const List &b); //конструктор копирования

    List &operator--(int); //перегрузить друж
    List &operator++();

    int getsize() { return size; };
    friend ostream &operator<<(ostream &os, List &l);
    void show(); //перегрузить вывод в поток
    int &operator[](int index) const;
    void operator()(int begin, int end);
    List &operator=(const List &b);
    bool operator==(const List &b);
    bool operator!=(const List &b);
    bool operator>(const List &b);
    bool operator<(const List &b);
    bool operator>=(const List &b);
    bool operator<=(const List &b);

private:
    class Node
    {
    public:
        Node *pNext; //указ на след элемент
        int data;    // информация

        explicit Node(int data = 0, Node *pNext = nullptr) //конструктор
        {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int size;
    Node *head; //голова списка
};
#endif /* spisok_hpp */