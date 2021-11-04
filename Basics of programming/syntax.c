#include <stdio.h>
#include <stdlib.h>
#define KNRM "\x1B[0m"
//#define KRED "\x1B[31m"
//#define KGRN "\x1B[32m"
#define KBLU "\x1B[34m"
//#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
//#define KWHT "\x1B[37m"
#define jkl 7.7
int main(void)
{
    //a = 7.7;
    //printf ("%f", 7.7);
    //printf("7.7 %f\n", 7.7);
    FILE *in;

    in = fopen("text.txt", "rt"); //открытие файла для чтения

    if (in == NULL) //если не удалось открыть файл или он пустой
    {
        printf("Файл не найден\n");
        //printf ("%s", KNRM);
        3 return 0;
    }

    char sim;
    int i = 0;
    int j = 0;
    char **string;
    string = (char **)malloc(sizeof(char *));
    *string = (char *)malloc(sizeof(char));

    int dot_pos = 0;
    int cmt_pos_1 = 0;
    int cmt_pos_2 = 0;
    int cmt_2_pos_1 = 0;
    int cmt_2_pos_2 = 0;
    int flag_dot = 0;  // на точку
    int flag_brkt = 0; //на скобку //проверка при выводе на поиск чисел в
    притф

    int flag_cmt_1 = 0; //на закомментированнойсть текста //
    int flag_cmt_2 = 0; //на закомментированнойсть текста /* */
    int flag_true = 0;  //выполнение условия для вещ конст
    do
    {
        do
        {
            do
            {
                sim = getc(in); //взвращает символ из потока в переменную
                sim
                    string[i][j] = sim;
                if (sim == '.') //если нашли точку
                {
                    flag_dot = 1; //флаг точка поднять
                    dot_pos = j;  //запомнить позицию точки
                }
                if (sim == '/' && flag_cmt_2 != 3) //если нашли комментарий
                {
                    // flag_cmt_2=1;
                    cmt_2_pos_1 = j;
                }
                if (sim == '*' && j == cmt_2_pos_1 + 1)
                {
                    flag_cmt_2 = 2;
                    cmt_2_pos_1 = j;
                }
                if (sim == '*' && flag_cmt_2 == 2 && cmt_2_pos_1 != j)
                {
                    cmt_2_pos_2 = j;
                    flag_cmt_2 = 3;
                }
                if (sim == '/' && j == cmt_2_pos_2 + 1 && flag_cmt_2 == 3)
                    flag_cmt_2 = 0;

                if (sim == '/' && flag_cmt_1 != 1)
                {
                    flag_cmt_1 = 1;
                    cmt_pos_1 = j;
                    4 cmt_pos_2 = i;
                }
                if (sim == '"' && flag_brkt == 1)
                    flag_brkt = 2;
                if (sim == '"' && flag_brkt != 2)
                    flag_brkt = 1;

                j++;
                string[i] = (char *)realloc(string[i], (j + 2) * sizeof(char));
            } while (sim != ' ' && sim != '\xff' && sim != '\n' &&
                     sim != '\0' && sim != ';');

            string[i][j] = '\0';

            if (flag_dot == 1 && string[i][dot_pos + 1] >= '0' &&
                string[i][dot_pos + 1] <= '9' && string[i][dot_pos - 1] >= '0' &&
                string[i][dot_pos - 1] <= '9')
                flag_true = 1;
            flag_dot = 0;
            if (flag_cmt_1 == 1 && string[cmt_pos_2][cmt_pos_1 + 1] == '/')
                flag_true = 0;
            if (flag_brkt == 1)
                flag_true = 0;
            if (flag_cmt_2 != 0)
                flag_true = 0;

            if (flag_true == 1)
            {
                for (int u = 0; u < j; u++)
                {
                    if ((string[i][u] > '9' || string[i][u] <
                                                   '0') &&
                        string[i][u] != '.')
                        printf("%s", KNRM);
                    else
                        printf("%s", KCYN);

                    printf("%c", string[i][u]);
                }
                printf("%s", KNRM);
            }
            else
                printf("%s", string[i]);

            flag_true = 0;
            j = 0;
            i++;

            string[i] = (char *)malloc(sizeof(char));
            string = (char **)realloc(string, (i + 2) * sizeof(char *));

        } while (sim != '\n' && sim != '\xff' && sim != '\0'); //конец файла в юникоде
        flag_cmt_1 = 0;
        flag_brkt = 0;
        5

            j = 0;
        i = 0;

    } while (sim != '\xff');

    return 0;
}