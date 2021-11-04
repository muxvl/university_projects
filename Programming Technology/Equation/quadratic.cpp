#include "quadratic.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
void Quadratic::calculate()
{
    double a, b, c, D;
    double x1 = 0;
    double x2 = 0;
    double variable = 0;
    int choice;
    ofstream fout;
    cout << "Введите коэффициент a: ";
    cin >> a;

    cout << "Введите коэффициент b: ";
    cin >> b;

    cout << "Введите коэффициент c: ";
    cin >> c;

    cout << "Ваше уравнение имеет вид: " << a << "x^2+" << b << "x+" << c << " = 0" << endl;

    cout << "Куда выводим данные?" << endl;
    cout << "|1| - консоль" << endl;
    cout << "|2| - файл" << endl;
    cin >> choice;

    if (choice == 1)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                cout << "Корень уравнения: 0" << endl;
            }
            else
            {
                variable = -(c / a);
                if (variable <= 0)
                {
                    cout << "Нет решений." << endl;
                }
                else
                {
                    x1 = sqrt(variable);
                    x2 = -sqrt(variable);
                    cout << "Первый корень уравнения: " << x1 << endl;
                    cout << "Второй корень уравнения: " << x2 << endl;
                }
            }
        }
        else if (a == 0)
        {
            cout << "" << endl;
            throw logic_error("Это не квадратное уравнение!");
        }
        else if (c == 0)
        {
            x1 = 0; //тут дабл вообще
            x2 = -(b / a);

            cout << "Первый корень уравнения: " << x1 << endl;
            cout << "Второй корень уравнения: " << x2 << endl;
        }
        else
        {
            D = (b * b - 4 * a * c);
            cout << "D = " << D << endl;

            if (D < 0)
            {
                cout << "Нет корней" << endl;
            }
            else if (D == 0)
            {
                x1 = -b / (2 * a);
                cout << "Корень уравнения:" << x1 << endl;
            }
            else
            {
                x1 = (-b + sqrt(D)) / (2 * a); //тут дабл вообще
                x2 = (-b - sqrt(D)) / (2 * a);

                cout << "Первый корень уравнения: " << x1 << endl;
                cout << "Второй корень уравнения: " << x2 << endl;
            }
        }
    }
    else if (choice == 2)
    {
        fout.open("myText.txt");

        if (!fout.is_open())
        {
            cout << "Не удалось открыть файл!" << endl;
        }
        else
        {
            if (b == 0)
            {
                if (c == 0)
                {
                    fout << "Корень уравнения: 0" << endl;
                }
                else
                {
                    variable = -(c / a);
                    if (variable <= 0)
                    {
                        fout << "Нет решений." << endl;
                    }
                    else
                    {
                        x1 = sqrt(variable);
                        x2 = -sqrt(variable);
                        fout << "Первый корень уравнения: " << x1 << endl;
                        fout << "Второй корень уравнения: " << x2 << endl;
                    }
                }
            }
            else if (a == 0)
            {
                cout << "" << endl;
                throw logic_error("Это не квадратное уравнение!");
            }
            else if (c == 0)
            {
                x1 = 0; //тут дабл вообще
                x2 = -(b / a);

                fout << "Первый корень уравнения: " << x1 << endl;
                fout << "Второй корень уравнения: " << x2 << endl;
            }
            else
            {
                D = (b * b - 4 * a * c);
                fout << "D = " << D << endl;

                if (D < 0)
                {
                    fout << "Нет корней" << endl;
                }
                else if (D == 0)
                {
                    x1 = -b / (2 * a);
                    fout << "Корень уравнения:" << x1 << endl;
                }
                else
                {
                    x1 = (-b + sqrt(D)) / (2 * a); //тут дабл вообще
                    x2 = (-b - sqrt(D)) / (2 * a);

                    fout << "Первый корень уравнения: " << x1 << endl;
                    fout << "Второй корень уравнения: " << x2 << endl;
                }
            }
        }
    }
    else
    {
        cout << "Такого выбора нет." << endl;
    }
};