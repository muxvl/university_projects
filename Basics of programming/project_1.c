#include <stdio.h>
#include <stdlib.h>

struct Football
{
    int num;
    int record;
    int w; //колво побед
    int l; //колво поражений
    int d; // колво ничьих
    int g; //колво игр
    char team_name[100];
};
struct Football teams[100];

int count = 0;

int cout()

{

    int c = 0;

    FILE *fpin;

    fpin = fopen("text.txt", "r");

    while (!feof(fpin))

    {

        if (fgetc(fpin) == '\n')

            c++;
    }

    return c;
}

int N;
void add(void);
void game(void);
void output(void);
void sort(void);
void file(void); //запись полной таблицы в файл
void del(void);

void copy(char out[], char in[])
{
    int i;
    for (i = 0; out[i] != '\0'; i++)
        in[i] = out[i];
    in[i] = '\0';
};

int main(void)
{
    int a = 0;
    int choice;
    setlocale(LC_ALL, "Russian");

    do
    {
        printf("Выберите опцию:\n\t 1.Пополнение таблицы\n\t 2.Составление пар на игру\n\t 3.Вывод полной таблицы\n\t 4.Вывод турнирной таблицы в порядке убывания очков\n\t 5.Сохранение полной таблицы в файл\n\t 6.Удалить команду \n\t 7.Выход\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            game();
            break;
        case 3:
            output();
            break;
        case 4:
            sort();
            break;
        case 5:
            file();
            break;
        case 6:
            del();
            break;
        case 7:
            a = 1;
        }
    } while (a == 0);
    return 0;
}

void del(void)
{
    FILE *fpin;
    fpin = fopen("text.txt", "w");
    int number;

    printf("Какую команду удалить?\n");
    scanf("%d", &number);
    printf("Данная команда удалена:\n");

    for (int i = 0; i < N; i++)
    {
        if (number == teams[i].num)
        {
            printf("номер команды: %d\n", teams[i].num);
            printf("название команды: %s\n", teams[i].team_name);
            printf("количество очков команды: %d\n", teams[i].record);

            copy(teams[count - 1].team_name, teams[i].team_name);
            teams[i].record = teams[count - 1].record;
            teams[i].w = teams[count - 1].w;
            teams[i].d = teams[count - 1].d;
            teams[i].g = teams[count - 1].g;
            teams[i].l = teams[count - 1].l;
            teams[i].num = teams[count - 1].num;
        }
    }
    count--;
    for (int i = 0; i < count; i++)
    {
        fprintf(fpin, "%d %s\n", teams[i].num, teams[i].team_name);
    }
    fclose(fpin);
}

void file()
{
    count = cout();
    FILE *fpout;
    fpout = fopen("result.txt", "wb");
    if (fpout == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return;
    }
    struct Football tmp;
    int i, j;

    for (i = count - 1; i >= 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (teams[j].num > teams[j + 1].num)
            {
                tmp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = tmp;
            }
        }
    }

    fputs("number|points|games|wins|loses|draw|name\n", fpout);

    for (i = 0; i < count; i++)
    {
        fprintf(fpout, "%-6d|%-6d|%-5d|%-4d|%-5d|%-4d|%-4s\n", teams[i].num, teams[i].record, teams[i].g, teams[i].w, teams[i].l, teams[i].d, teams[i].team_name);
    }
    fclose(fpout);
}

void add(void)
{
    FILE *fpin;
    int i = 0;

    fpin = fopen("text.txt", "wb");
    printf("Сколько команд участвуют в турнире?\n");
    scanf("%d", &N);
    printf("в турнире участвуют %d команды\nВведите названия:\n", N);

    for (i = 0; i < N; i++)
    {
        scanf("%s", teams[i].team_name);
        teams[i].num = i + 1;
        fprintf(fpin, "%d %s\n", teams[i].num, teams[i].team_name);
    }
    fclose(fpin);
}
void game(void)
{
    count = cout();
    int ch1, ch2;
    int a1, a2; //счет

a:
    ch1 = rand() % count + 1;
    ch2 = rand() % count + 1;
    if (ch1 == ch2)
        goto a;
    printf("играют команды %s и %s.\nВведите счет:\n", teams[ch1 - 1].team_name, teams[ch2 - 1].team_name);
    scanf("%d", &a1);
    scanf("%d", &a2);

    teams[ch1 - 1].g += 1;
    teams[ch2 - 1].g += 1;

    if (a1 > a2)
    {
        teams[ch1 - 1].w += 1;
        teams[ch2 - 1].l += 1;

        teams[ch2 - 1].record += 0;
        teams[ch1 - 1].record += 3;
    }
    else if (a1 < a2)
    {
        teams[ch1 - 1].l += 1;
        teams[ch2 - 1].w += 1;
        teams[ch2 - 1].record += 3;
        teams[ch1 - 1].record += 0;
    }
    else
    {
        teams[ch1 - 1].d += 1;
        teams[ch2 - 1].d += 1;
        teams[ch2 - 1].record += 1;
        teams[ch1 - 1].record += 1;
    }
}

void sort(void)
{
    count = cout();
    struct Football tmp;
    int i, j;

    for (i = count - 1; i >= 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (teams[j].record < teams[j + 1].record)
            {
                tmp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = tmp;
            }
        }
    }
    printf("place|points|name\n");
    for (i = 0; i < count; i++)
    {
        printf("%-5d|%-6d|%-4s\n", (i + 1), teams[i].record, teams[i].team_name);
    }
}

void output(void)
{
    count = cout();
    struct Football tmp;
    int i, j;

    for (i = count - 1; i >= 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (teams[j].num > teams[j + 1].num)
            {
                tmp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = tmp;
            }
        }
    }
    printf("number|points|games|wins|loses|draw|name\n");
    for (i = 0; i < count; i++)
    {
        printf("%-6d|%-6d|%-5d|%-4d|%-5d|%-4d|%-4s\n", teams[i].num, teams[i].record, teams[i].g, teams[i].w, teams[i].l, teams[i].d, teams[i].team_name);
    }
}
