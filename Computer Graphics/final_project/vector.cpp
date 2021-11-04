#include "vector.h"

//Конструкторы
vector::vector() : data(nullptr), length(0) {}
vector::vector(int size)
{
    data = nullptr;
    length = 0;
    resize(size);
}
vector::vector(const vector &b)
{
    length = b.length;
    data = new double[length];
    for (int i = 0; i < length; ++i)
        data[i] = b.data[i];
}
vector::vector(vector &&b)
{
    data = b.data;
    length = b.length;
    b.data = nullptr;
    b.length = 0;
}
vector::~vector()
{
    delete[] data;
}
//Работа с размером вектора
void vector::resize(int size)
{
    if (length == size)
        return;
    vector tmp(*this);
    int interval = length > size ? size : length;
    delete[] data;
    data = nullptr;
    length = size;
    if (size)
        data = new double[size];
    for (int i = 0; i < interval; ++i)
        data[i] = tmp.data[i];
}
void vector::setVector(double element, ...)
{
    int i;
    va_list ap;
    va_start(ap, element);
    data[0] = element;
    for (i = 1; i < length; ++i)
    {
        data[i] = (double)va_arg(ap, double);
    }
    va_end(ap);
}
vector &vector::operator=(const vector &b)
{
    if (this != &b)
    {
        if (length != b.length)
        {
            delete[] data;
            this->resize(b.length);
        }
        for (int i = 0; i < length; ++i)
            data[i] = b.data[i];
    }
    return *this;
}
vector &vector::operator=(vector &&b)
{
    if (this != &b)
    {
        delete[] data;
        21 data = b.data;
        length = b.length;
        b.data = nullptr;
        b.length = 0;
    }
    return *this;
}