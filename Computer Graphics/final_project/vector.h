#pragma once
#include <cstdarg>
#include <iostream>
class vector
{
public:
    //Конструкторы
    vector();
    vector(int);
    vector(const vector &);
    vector(vector &&);
    //Деструктор
    ~vector();
    //Работа с размером вектора
    int size() const { return length; }
    void resize(int);
    //Установка значения вектора
    void setVector(double, ...);
    //Операторы для работы
    vector &operator=(const vector &);
    vector &operator=(vector &&);
    double &operator[](int i) { return data[i]; }
    double operator[](int i) const { return data[i]; }
    void print()
    {
        for (int j = 0; j < length; ++j)
        {
            std::cout << data[j] << ' ';
        }
        std::cout << std::endl;
    }

private:
    double *data;
    int length;
};