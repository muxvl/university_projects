#ifndef equation_hpp
#define equation_hpp
#include "equation.hpp"
#include <iostream>
using namespace std;
class Equation
{ //абстрактный базовый класс
public:
    Equation() { cout << "Вызван конструктор базового класса" << endl; }
    virtual ~Equation() { cout << "Вызван деструктор базового класса" << endl; }
    virtual void calculate() = 0;
};
#endif /* equation_hpp */