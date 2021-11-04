#include "spisok.hpp"
#include <iostream>
using namespace std;
List::List()
{ //конструктор
    size = 0;
    head = nullptr;
}
List::~List()
{ //деструктор
    while (this->size > 0)
    {
        Node *buffer = head;
        head = buffer->pNext;
        delete buffer;
        size--;
    }
}
List::List(const List &b)
{ //конструктор копирования
    cout << " KK" << endl;
    Node *source = b.head;
    Node *first = nullptr;
    Node *second = nullptr;
    while (source != nullptr)
    {
        first = new Node(source->data, nullptr);
        if (second == nullptr)
        {
            head = first;
        }
        else
        {
            second->pNext = first;
        }
        second = first;
        source = source->pNext;
    }
    this->size = b.size;
};
ostream &operator<<(ostream &os, List &l)
{
    List::Node *buffer = l.head;
    os << "(";
    while (buffer != nullptr)
    {
        os << "->" << buffer->data;
        buffer = buffer->pNext;
    }
    os << ")" << endl;
    return os;
}
void List::show()
{ //вывод в поток
    Node *buffer = head;
    while (buffer != nullptr)
    {
        cout << buffer->data << "->";
        buffer = buffer->pNext;
    }
    cout << " " << endl;
};
List &List::operator=(const List &b)
{
    if (this == &b)
    {
        return *this;
    }
    Node *source = b.head;
    Node *first = nullptr;
    Node *second = nullptr;
    while (source != nullptr)
    {
        first = new Node(source->data, nullptr);
        if (second == nullptr)
        {
            head = first;
        }
        else
        {
            second->pNext = first;
        }
        second = first;
        source = source->pNext;
    }
    this->size = b.size;
    cout << "size" << this->size << endl;
    return *this;
}
List &List::operator++()
{
    int data;
    cout << "Введите значение элемента" << endl;
    cin >> data;
    if (head == nullptr)
    {
        head = new Node(data);
        cout << "Добавлен элемент:" << data << endl;
    }
    else
    {
        Node *current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node(data);
        cout << "Добавлен элемент:" << data << endl;
    }
    size++;
    return *this;
};
List &List::operator--(int)
{
    Node *temp = head;
    if (head == nullptr)
        throw logic_error("Очередь пустая.");
    head = head->pNext;
    cout << "Первый элемент извлечен" << endl;
    delete temp;
    size--;
    return *this;
};
void List::operator()(int begin, int end)
{
    if (begin < 0 || begin > size || end < 0 || end > size)
        cout << "Некорректный ввод." << endl;
    int cnt = 0;
    Node *ptr = head;
    while (cnt != begin)
    {
        ptr = ptr->pNext;
        cnt++;
    }
    while (cnt <= end)
    {
        cout << cnt << ")" << ptr->data << endl;
        ptr = ptr->pNext;
        cnt++;
    }
    return;
}
int &List::operator[](int index) const
{
    if (index > size)
    {
        throw logic_error("Такого элемента нет");
    }
    if (head == nullptr)
    {
        throw logic_error("Очередь пустая");
    }
    int cnt = 0;
    Node *current = this->head;
    while (current != nullptr)
    {
        if (cnt == index)
        {
            break;
        }
        current = current->pNext;
        cnt++;
    }
    return current->data;
};
bool List::operator==(const List &b)
{
    if (this->size != b.size)
    {
        return false;
    }
    for (int i = 0; i != this->size; i++)
    {
        if (this->operator[](i) != b[i])
        {
            return false;
        }
    }
    return true;
};
bool List::operator!=(const List &b)
{
    if (this->size == b.size)
    {
        return false;
    }
    for (int i = 0; i < this->size; i++)
    {
        if (this->operator[](i) == b[i])
        {
            return false;
        }
    }
    return true;
};
bool List::operator>(const List &b)
{
    if (this->size > b.size)
        return true;
    else
        return false;
};
bool List::operator<(const List &b)
{
    if (this->size < b.size)
        return true;
    else
        return false;
};
bool List::operator>=(const List &b)
{
    if (this->size >= b.size)
        return true;
    else
        return false;
};
bool List::operator<=(const List &b)
{
    if (this->size <= b.size)
        return true;
    else
        return false;
};