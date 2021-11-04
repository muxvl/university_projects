#ifndef quadratic_hpp
#define quadratic_hpp
#include "equation.hpp"
#include <iostream>
class Quadratic : public Equation
{
public:
    Quadratic() { cout << "Вызван конструктор производного класса Quadratic"
                       << endl; }
    virtual ~Quadratic()
    {
        cout << "Вызван деструктор производного класса
            Quadratic " << endl; }
            void
            calculate() override;
    };
#endif /* quadratic_hpp */