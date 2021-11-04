#include "spisok.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void show(List &a, List &b);
int main()
{

    List a, b;
    int option = 1;
    int i = 0;
    int j = 0;
    int choice = 1;
    int z = 0;

    cout << "Однонаправленный список" << endl;
    while (option)
    {
        cout << "|0| - Выход из программы" << endl;
        cout << "|1| - Добавление элемента в конец списка" << endl;
        cout << "|2| - Извлечение первого элемента из списка" << endl;
        cout << "|3| - Вывод элемента списка" << endl;
        cout << "|4| - Присваивание двух списков друг другу" << endl;
        cout << "|5| - Сравнение списков" << endl;
        cout << "|6| - Вывод подсписка" << endl;
        cout << "|7| - Вывод списка" << endl;

        cin >> option;
        switch (option)
        {
        case 0:
            break;

        case 1:
            cout << "В какой список вы хотите добавить элемент? (1 -- 2)" << endl;
            cin >> z;
            if (z == 1)
                ++a;
            else if (z == 2)
                ++b;
            else
                cout << "Номер списка неверный." << endl;

            cout << "Список 1:";
            cout << a;
            cout << "Список 2:";
            cout << b;
            break;

        case 2:
            cout << "Из какого списка вы хотите извлечь элемент? (1 -- 2)" << endl;
            cin >> z;
            if (z == 1)
                a--;
            else if (z == 2)
                b--;
            else
                cout << "Номер списка неверный." << endl;

            cout << "Список 1:";
            cout << a;
            cout << "Список 2:";
            cout << b;
            break;

        case 3:
            cout << "С каким списком работаем? (1 -- 2)" << endl;
            cin >> z;
            if (z == 1)
            {
                cout << "Введите номер элемента, который нужно вывести" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> i;
                cout << "Ваш элемент:" << a[i] << endl;
            }

            else if (z == 2)
            {
                cout << "Введите номер элемента, который нужно вывести" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> i;
                cout << "Ваш элемент:" << b[i] << endl;
            }
            else
                cout << "Номер списка неверный." << endl;
            break;

        case 4:
            cout << "Какой список присвоить? (1 -- 2)" << endl;
            cin >> z;
            if (z == 1)
                b = a;
            else if (z == 2)
                a = b;
            else
                cout << "Номер списка неверный." << endl;

            cout << "Список 1:" << a;
            cout << "Список 2" << b;
            break;

        case 5:
            cout << "Выберите арифметическую операцию:" << endl;
            while (choice != 40)
            {
                cout << "|10| - == и !=- равенство" << endl;
                cout << "|20| - > и < - строгое сравнение " << endl;
                cout << "|30| - >= и <= - нестрогое сравнение " << endl;
                cout << "|40| - Выход" << endl;

                cin >> choice;
                switch (choice)
                {
                case 10:
                    if (a == b)
                        cout << "Списки равны." << endl;
                    if (a != b)
                        cout << "Списки неравны." << endl;
                    break;
                case 20:
                    if (a > b)
                        cout << "Список 1 больше списка 2." << endl;
                    if (a < b)
                        cout << "Список 1 меньше списка 2." << endl;
                    break;
                case 30:
                    if (a >= b)
                    {
                        if (a > b)
                            cout << "Список 1 больше списка 2." << endl;
                        else if (a == b)
                            cout << "Списки равны." << endl;
                    }
                    if (a <= b)
                    {
                        if (a < b)
                            cout << "Список 1 меньше списка 2." << endl;
                        else if (a == b)
                            cout << "Списки равны." << endl;
                    }
                    break;
                case 40:
                    break;
                default:
                    break;
                }
            }
            break;
        case 6:
            cout << "С каким списком работаем? (1 -- 2)" << endl;
            cin >> z;
            if (z == 1)
            {
                cout << "Введите номер элемента,c которого нужно вывести подсписок" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> i;
                cout << "Введите номер элемента,до которого нужно вывести подсписок" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> j;
                a(i, j);
            }
            else
            {
                cout << "Введите номер элемента,c которого нужно вывести подсписок" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> i;
                cout << "Введите номер элемента,до которого нужно вывести подсписок" << endl
                     << "Помните, что нумерация с 0:" << endl;
                cin >> j;
                b(i, j);
            }
            break;
        case 7:
            cout << "Какой список вывести? (1,2,3 - оба)" << endl;
            cin >> z;
            if (z == 1)
                cout << a;
            else if (z == 2)
                cout << b;
            else if (z == 3)
            {
                cout << "Список 1: " << a;
                cout << "Список 2: " << b;
            }
            else
                cout << "Номер списка неверный." << endl;
            break;

        default:
            cout << "некорректный ввод";
            break;
        }
    }
}