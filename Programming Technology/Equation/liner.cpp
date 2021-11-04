#include "liner.hpp"
#include <fstream>
using namespace std;
void Linear::calculate()
{
    double a, b, x = 0;
    int choice;
    ofstream fout;

    cout << "Введите коэффициент a: ";
    cin >> a;

    cout << "Введите коэффициент b: ";
    cin >> b;

    cout << "Ваше уравнение имеет вид: " << a << "x = " << b << endl;

    cout << "Куда выводим данные?" << endl;
    cout << "|1| - консоль" << endl;
    cout << "|2| - файл" << endl;
    cin >> choice;

    if (choice == 1)
    {
        if (a == 0)
        {
            if (b == 0)
            {
                cout << "Бесконечно много корней." << endl;
            }
            else
            {
                cout << "Нет корней." << endl;
            }
        }
        else
        {
            x = b / a;
        }

        cout << "Корень уравнения: " << x << endl;
    }

    else if (choice == 2)
    {

        fout.open("myText.txt");

        if (!fout.is_open())
        {
            cout << "Ошибка открытия файла!" << endl;
        }
        else
        {
            if (a == 0)
            {
                if (b == 0)
                {
                    fout << "Бесконечно много корней." << endl;
                }
                else
                {
                    fout << "Нет корней." << endl;
                }
            }
            else
            {
                x = b / a;
            }

            fout << "Корень уравнения: " << x << endl;
        }
        fout.close();
    }
    else
    {
        cout << "Такого выбора нет." << endl;
    }
};