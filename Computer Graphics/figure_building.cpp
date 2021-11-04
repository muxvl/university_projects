#include <conio.h>
#include <locale.h>
#include <graphics.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;

void mult(float **a, float (&b)[3][3])
{
    int m = 5; //??
    int q = 3;
    int i, j;
    float **c = new float *[m];
    for (i = 0; i < m; i++)
    {
        c[i] = new float[q];
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k <= q + 1; k++)
                c[i][j] += (a[i][k] * b[k][j]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            a[i][j] = c[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        delete[] c[i];
    }
    delete[] c;
}

void move(float **A, float DX, float DY)
{
    float MP[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {DX, DY, 1}};
    mult(A, MP);
}

void mashtab(float **A, float s1)
{
    float MM[3][3] = {
        {s1, 0, 0},
        {0, s1, 0},
        {0, 0, 1}};
    mult(A, MM);
}

void povorot(float **A, float grad) //ïîâîðîò
{
    float alpha = 0.087;
    float MP[3][3] = {
        {cos(grad * alpha), sin(grad * alpha), 0},
        {(-sin(grad * alpha)), cos(grad * alpha), 0},
        {0, 0, 1}};
    mult(A, MP);
}

void draw_line(float **A)
{
    line(A[0][0], A[0][1], A[1][0], A[1][1]);
    line(A[1][0], A[1][1], A[2][0], A[2][1]);
    line(A[2][0], A[2][1], A[3][0], A[3][1]);
    line(A[3][0], A[3][1], A[4][0], A[4][1]);
    line(A[4][0], A[4][1], A[0][0], A[0][1]);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    initwindow(800, 800);
    float DX, DY;
    int code;
    int n = 3;
    int m = 5;
    float **first = new float *[m];
    for (int i = 0; i < m; i++)
    {
        first[i] = new float[n];
    }
    first[0][0] = 38.8;
    first[0][1] = 31.3;
    first[1][0] = 69.4;
    first[1][1] = 53.6;
    first[2][0] = 57.6;
    first[2][1] = 89.5;
    first[3][0] = 19.7;
    first[3][1] = 89.5;
    first[4][0] = 8.2;
    first[4][1] = 53.6;
    first[0][2] = first[1][2] = first[2][2] = first[3][2] = first[4][2] = 1;
    setcolor(4);
    draw_line(first);
    cout << ("действия с линиями->\nфиолетовая линия->вверх-стрелка вверх\nвниз-стрелка вниз\nвправо - стрелка вправо\nвлево - стрелка влево\nувеличить - пробел\n "
    "уменьшить-backspase\nкрутить по часовой стрелке-9\nкрутить против часовой стрелки-7\n");
    while (true)
    {
        if (kbhit())
        {
            code = getch();
            if (code == 27)
                break;
            switch (code)
            {
            case 75:
                move(first, -1, 0);
                break;
            case 77:
                move(first, 1, 0);
                break;
            case 72:
                move(first, 0, -1);
                break;
            case 80:
                move(first, 0, 1);
                break;
            case 32:
                mashtab(first, 1.05);
                break;
            case 8:
                mashtab(first, 0.95);
                break;
            case '0':
                povorot(first, 1);
                break;
            case '9':
                povorot(first, -1);
                break;
            default:
                break;
            }
            cleardevice();
            draw_line(first);
        }
    }
    for (int i = 0; i < m; i++)
    {
        delete[] first[i];
    }
    delete[] first;
    getch();
    closegraph();
    return 0;
}