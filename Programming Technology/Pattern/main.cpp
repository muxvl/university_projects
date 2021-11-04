#include <iostream>
#include "spisok.hpp"
using namespace std;
template <typename T> //бинарный поиск
void binary(T *list, T item, int size)
{ //массив, нужный элемент, длина массива
    int low = 0;
    int high = size - 1;
    int mid;
    T guess;

    while (low <= high)
    {
        mid = (low + high) / 2;
        guess = list[mid];

        if (guess == item)
        {
            cout << "Помните, что нумерация элементов начинайется с 0!\nНомер
                вашего элемента : ";
                                  cout
                 << mid
                 << endl;

            break;
        }

        if (guess > item)
            high = mid - 1;
        else if (guess < item)
            low = mid + 1;
    }
}
template <typename T>
void sort(T *list, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--) // для всех элементов после i-ого
        {
            if (list[j - 1] > list[j]) // если текущий элемент меньше
                предыдущего
                {
                    int temp = list[j - 1]; // меняем их местами
                    list[j - 1] = list[j];
                    list[j] = temp;
                }
        }
    }

    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
}
int main()
{
    int size = 0;
    int *list1; //для выделения памяти под массив
    int item1;
    double *list2;
    double item2;
    char *list3;
    char item3;
    float *list4;
    float item4;
    int option = 1;

    List<int> a, b;
    List<double> c, d;

    cout << "Задание 1. Бинарный поиск в массиве." << endl;
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Размер массива должен быть положительным!" << endl;
        return 1;
    }
    while (option)
    {
        cout << "Какой тип данных будет у элементов массива?" << endl;
        cout << "1. - char" << endl;
        cout << "2. - int" << endl;
        cout << "3. - float" << endl;
        cout << "4. - double" << endl;
        cout << "0 - выход из программы" << endl;

        cin >> option;
        switch (option)
        {
        case 0:
            break;
        case 1:
            list3 = new char[size]; // выделение памяти под массив
            for (int i = 0; i < size; i++)
            {
                cout << "list[" << i << "] = ";
                cin >> list3[i];
            }
            sort<char>(list3, size);
            cout << "Введите элемент, который нужно найти:" << endl;
            cin >> item3;
            binary<char>(list3, item3, size);
            delete[] list3;
            break;

        case 2:
            list1 = new int[size]; // выделение памяти под массив
            for (int i = 0; i < size; i++)
            {
                cout << "list[" << i << "] = ";
                cin >> list1[i];
            }
            sort<int>(list1, size);
            cout << "Введите элемент, который нужно найти:" << endl;
            cin >> item1;
            binary<int>(list1, item1, size);
            delete[] list1;
            break;
        case 3:
            list4 = new float[size]; // выделение памяти под массив
            for (int i = 0; i < size; i++)
            {
                cout << "list[" << i << "] = ";
                cin >> list4[i];
            }
            sort<float>(list4, size);
            cout << "Введите элемент, который нужно найти:" << endl;
            cin >> item4;
            binary<float>(list4, item4, size);
            delete[] list4;
            break;
        case 4:
            list2 = new double[size]; // выделение памяти под массив
            for (int i = 0; i < size; i++)
            {
                cout << "list[" << i << "] = ";
                cin >> list2[i];
            }
            sort<double>(list2, size);
            cout << "Введите элемент, который нужно найти:" << endl;
            cin >> item2;
            binary<double>(list2, item2, size);
            delete[] list2;
            break;
        }
    }

    cout << "Задание 2. Односвязный список." << endl;
    option = 1;
    int choice = 1;
    int z = 0;

    while (option)
    {
        cout << "Какой тип данных будет у элементов списка?" << endl;
        cout << "1. - int" << endl;
        cout << "2. - double" << endl;
        cout << "0. - выход из программы" << endl;

        cin >> option;
        switch (option)
        {
        case 0:
            break;
        case 1:
            cout << "|0| - Выход." << endl;
            cout << "|1| - Добавление элемента в конец списка" << endl;
            cout << "|2| - Извлечение первого элемента из списка" << endl;
            cout << "|3| - Сравнение списков" << endl;
            cout << "|4| - Вывод списка" << endl;

            cin >> choice;
            switch (choice)
            {
            case 0:
                break;
            case 1:
                cout << "В какой список вы хотите добавить
                    элемент
                    ? (1 --2) " << endl;
                          cin >>
                          z;
                if (z == 1)
                    ++a;
                else if (z == 2)
                    ++b;
                else
                    cout << "Номер списка неверный." << endl;

                cout << "Список 1:";
                a.show();
                cout << "Список 2:";
                b.show();
                break;
            case 2:
                cout << "Из какого списка вы хотите извлечь
                    элемент
                    ? (1 --2) " << endl;
                          cin >>
                          z;
                if (z == 1)
                    a--;
                else if (z == 2)
                    b--;
                else
                    cout << "Номер списка неверный." << endl;

                cout << "Список 1:";
                a.show();
                cout << "Список 2:";
                b.show();
                break;
            case 3:
                if (a > b)
                    cout << "Список 1 больше списка 2." << endl;
                if (a < b)
                    cout << "Список 1 меньше списка 2." << endl;
                break;
            case 4:
                cout << "Какой список вывести? (1,2,3 - оба)" << endl;
                cin >> z;
                if (z == 1)
                    a.show();
                else if (z == 2)
                    b.show();
                else if (z == 3)
                {
                    cout << "Список 1: ";
                    a.show();
                    cout << endl;
                    cout << "Список 2: ";
                    b.show();
                    cout << endl;
                }
                else
                    cout << "Номер списка неверный." << endl;
                break;
            }
            break;
        case 2:
            cout << "|0| - Выход." << endl;
            cout << "|1| - Добавление элемента в конец списка" << endl;
            cout << "|2| - Извлечение первого элемента из списка" << endl;
            cout << "|3| - Сравнение списков" << endl;
            cout << "|4| - Вывод списка" << endl;

            cin >> choice;
            switch (choice)
            {
            case 0:
                break;
            case 1:
                cout << "В какой список вы хотите добавить
                    элемент
                    ? (1 --2) " << endl;
                          cin >>
                          z;
                if (z == 1)
                    ++c;
                else if (z == 2)
                    ++d;
                else
                    cout << "Номер списка неверный." << endl;

                cout << "Список 1:";
                c.show();
                cout << "Список 2:";
                d.show();
                break;
            case 2:
                cout << "Из какого списка вы хотите извлечь элемент?
                        (1 --2) " << endl;
                        cin >>
                    z;
                if (z == 1)
                    c--;
                else if (z == 2)
                    d--;
                else
                    cout << "Номер списка неверный." << endl;

                cout << "Список 1:";
                c.show();
                cout << "Список 2:";
                d.show();
                break;
            case 3:
                if (c > d)
                    cout << "Список 1 больше списка 2." << endl;
                if (c < d)
                    cout << "Список 1 меньше списка 2." << endl;
                break;
            case 4:
                cout << "Какой список вывести? (1,2,3 - оба)" << endl;
                cin >> z;
                if (z == 1)
                    a.show();
                else if (z == 2)
                    b.show();
                else if (z == 3)
                {
                    cout << "Список 1: ";
                    a.show();
                    cout << endl;
                    cout << "Список 2: ";
                    b.show();
                    cout << endl;
                }
                else
                    cout << "Номер списка неверный." << endl;
                break;
            }
            break;
        default:
            cout << "некорректный ввод";
            break;
        }
    }

    return 0;
}