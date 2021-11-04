#include <stdio.h>
#define max 10
int main()
{
    int i, p;
    int m[max];
    int *ptr1, *ptr2;
    ptr1 = m;
    ptr2 = m;

    printf("введите массив из %d элементов\n", max);

    for (i = 0; i < max; i++) //ввод массива
        scanf("%d", &m[i]);

    if ((max % 2) == 0) //поиск последнего четного элемента массива
        p = max;
    else
        p = max - 1;

 printf("последний четный элемент массива: %d , значение этого
элемента: %d\n", p, m[p-1]);

 for(i = 1; i < max - 1; i++) //прибавляем ко всем нечетным числам
(кроме первого и последнего) последний четный элемент
 {
        if ((*(ptr1 + i) % 2) != 0)
        {
            (*(ptr1 + i)) += *(ptr2 + p - 1);
        }
 }

 for (i = 0; i < max; i++) //вывод массива
 printf("%d ", *(ptr1+i));
 printf("\n");

 return 0;
}