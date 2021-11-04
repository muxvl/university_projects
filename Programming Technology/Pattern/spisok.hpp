#ifndef spisok_hpp
#define spisok_hpp
#include <iostream>
#include <stdio.h>
using namespace std;
template <typename T = int>
class Node
{
public:
    Node<T> *pNext; //указ на след элемент
    T data;         // информация

    explicit Node(T data = 0, Node<T> *pNext = nullptr) //конструктор
    {
        this->data = data;
        this->pNext = pNext;
    }
};
template <typename T>
class List
{
public:
    List()
    { //конструктор
        size = 0;
        head = nullptr;
    };

    ~List()
    {
        while (this->size > 0)
        {
            Node<T> *buffer = head;
            head = buffer->pNext;
            delete buffer;
            size--;
        }
    }

    List<T>(const List &b); //конструктор копирования

    List<T> &operator--(int)
    {
        Node<T> *temp = head;
        if (head == nullptr)
            throw logic_error("Очередь пустая.");
        head = head->pNext;
        cout << "Первый элемент извлечен" << endl;
        delete temp;
        size--;
        return *this;
    };

    List<T> &operator++()
    {
        T data;
        cout << "Введите значение элемента" << endl;
        cin >> data;
        if (head == nullptr)
        {
            head = new Node<T>(data);
            cout << "Добавлен элемент:" << data << endl;
        }
        else
        {
            Node<T> *current = this->head;
            while (current->pNext != nullptr)
            {
                current = current->pNext;
            }
            current->pNext = new Node<T>(data);
            cout << "Добавлен элемент:" << data << endl;
        }
        size++;
        return *this;
    };

    int getsize() { return size; };
    void show() //перегрузить вывод в поток
    {
        Node<T> *buffer = head;
        while (buffer != nullptr)
        {
            cout << buffer->data << "->";
            buffer = buffer->pNext;
        }
        cout << " " << endl;
    };

    bool operator>(const List &b)
    {
        if (this->size > b.size)
            return true;
        else
            return false;
    };

    bool operator<(const List &b)
    {
        if (this->size < b.size)
            return true;
        else
            return false;
    };

private:
    int size;
    Node<T> *head; //голова списка
};
#endif /* spisok_hpp */