#include <iostream>
#include <locale.h>
#include <cstdio>
#include <stdbool.h>
#include <stdlib.h>
#include <string>
#include <curses.h>
using namespace std;
class Phone
{
private:
    string NSP;
    string num;
    int time_in;
    int time_out;

public:
    Phone()
    {
        NSP = "None";
        //Surname = "None";
        //Patronymic = "None";
        num = "None";
        time_in = 0;
        time_out = 0;
    }

    Phone(string NSP, string num, int time_in, int time_out)
    {
        this->NSP = NSP;
        3 this->num = num;
        this->time_in = time_in;
        this->time_out = time_out;
    }

    string get_NSP()
    {
        return NSP;
    }

    void set_NSP()
    {
        cout << "Введите фамилию, имя и отчество абонента: ";
        getline(cin, NSP);
    }

    string get_num()
    {
        return num;
    }

    void set_num()
    {
        cout << "Введите номер телефона абонента: ";
        getline(cin, num);
    }

    int get_time_in()
    {
        return time_in;
    }

    void set_time_in()
    {
        cout << "Введите кол-во часов внутригородских звонков абонента: ";
        cin >> time_in;
    }

    int get_time_out()
    {
        return time_out;
    }

    void set_time_out()
    {
        cout << "Введите кол-во часов междугородних звонков абонента: ";
        cin >> time_out;
    }
    void show()
    {
        cout << "Фамилия,имя, отчество абонента: " << NSP << endl;
        cout << "Номер телефона абонента: " << num << endl;
        cout << "Время внутригородских звонков (в часах): " << time_in << endl;
        cout << "Время междугородних звонков (в часах): " << time_out << endl;
    }

    bool print_time_in(int valtime)
    {
        bool found = 0;
        if (time_in > valtime)
            4
            {
                show();
                cout << endl;
                found = 1;
            }
        return found;
    }

    void print_time_out()
    {
        if (time_out != 0)
        {
            show();
            cout << endl;
        }
    }
};
void sort(Phone *phone_info, int num_phones)
{
    for (int i = 0; i < num_phones - 1; i++)
        for (int j = i + 1; j < num_phones; j++)
            if (phone_info[i].get_NSP() > phone_info[j].get_NSP())
            {
                Phone buf = phone_info[i];
                phone_info[i] = phone_info[j];
                phone_info[j] = buf;
            }
}
int main(void)
{
    Phone *phone_info, *temp;
    bool exit = 1;
    bool found = 0;
    char c = ' ';
    string choose;
    int i = 0; //счетчки
    int num_phones = 1;
    int max_time_in = 0;

    setlocale(LC_ALL, "Rus");

    phone_info = new Phone[num_phones];

    phone_info[0].set_NSP();
    phone_info[0].set_num();
    phone_info[0].set_time_in();
    phone_info[0].set_time_out();

    while (exit)
    {
        cout << "Хотите добавить абонента?\n\t 1.да\n\t 2.нет\n"
             << endl;
        cin.ignore(32767, '\n'); //вылавливаем переход на новую строку
        getline(cin, choose);

        if (choose == "1")
        {
            num_phones++;
            temp = new Phone[num_phones];

            for (i = 0; i < num_phones - 1; i++)
                5
                {
                    temp[i] =
                        Phone(phone_info[i].get_NSP(), phone_info[i].get_num(),
                              phone_info[i].get_time_in(), phone_info[i].get_time_out());
                }

            temp[i].set_NSP();
            temp[i].set_num();
            temp[i].set_time_in();
            temp[i].set_time_out();

            delete[] phone_info;
            phone_info = temp;
            temp = nullptr;
        }
        else
            exit = 0;
    }
    exit = 1;

    while (exit)
    {
        cout << "Выберите цифру:\n\t 1.сведения об абонентах, время
            внутригородских разговоров которых превышает заданное;
        \n\t 2.сведения об
            абонентах,
            воспользовавшихся междугородней связью;
        \n\t 3.cведения об
            абонентах,
            выведенные в алфавитном порядке;
        \n\t 4.Выход\n ";

            switch (c = getchar())
        {
        case '1':
            cout << "Введите максимальное время внутригородских
                    разговороd(в часах)\n " << endl;
                    cin >>
                max_time_in;
            cin.ignore(32767, '\n');

            for (i = 0; i < num_phones; i++)
            {
                if (phone_info[i].print_time_in(max_time_in))
                    found = 1;
            }

            if (found == 0)
                cout << "Не найдено схожих абонентов.\n"
                     << endl;

            found = 0;
            cout << "Для продолжения нажмите enter\n";
            getchar();
            break;

        case '2':
            cout << "Вывод абонентов, пользовавшихся междугородней связью"
                 << endl;
            for (i = 0; i < num_phones; i++)
                phone_info[i].print_time_out();
            cout << "Для продолжения нажмите enter\n";
            getchar();
            break;

        case '3':
            cout << "alf" << endl;
            sort(phone_info, num_phones);

            for (i = 0; i < num_phones; i++)
                6
                {
                    phone_info[i].show();
                    cout << endl;
                }

            cout << "Для продолжения нажмите enter\n";
            getchar();
            break;

        case '4':
            cout << "Выход" << endl;
            exit = 0;
            cout << "Для продолжения нажмите enter\n";
            getchar();
            break;

        default:
            cout << "Некорректный выбор.\n"
                 << endl;
            cout << "Для продолжения нажмите enter\n";
            getchar();
            break;
        }
    }

    delete[] phone_info;
    phone_info = nullptr;
    return 0;
}