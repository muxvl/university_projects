файл linear.hpp
#ifndef liner_hpp
#define liner_hpp
#include "equation.hpp"
#include <iostream>
    class Linear : public Equation
{
public:
    Linear() { cout << "Вызван конструктор производного класса Linear" << endl; }
    virtual ~Linear()
    {
        cout << "Вызван деструктор производного класса
            Linear " << endl; }
            void
            calculate() override;
    };
#endif /* liner_hpp */
