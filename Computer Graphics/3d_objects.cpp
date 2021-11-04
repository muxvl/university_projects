#include <iostream>
#include <graphics.h>
#include <math.h>
#include <vector>
#define N 8
#define M 4
const int DX = 5, DY = 5, color = 10;
const double S1 = 1.1;
const double S2 = 0.95;
const double ALPHA = 0.087;
using namespace std;
void mult(vector<vector<double> > &fig, vector<vector<double> > &mass);
void offset(vector<vector<double> > &fig, double dx, double dy);
void scale(vector<vector<double> > &fig, double S);
void rotateZ(vector<vector<double> > &fig, double angle);
void rotateY(vector<vector<double> > &fig, double angle);
void rotateX(vector<vector<double> > &fig, double angle);
void draw(vector<vector<double> > &fig);
int main()
{
    setlocale(LC_ALL, "Russian");
    initwindow(1000, 600, "", 100, 100);
    vector<vector<double> > AB(N, vector<double>(M));
    AB = {{200, 400, 100, 1},
          {200, 200, 100, 1},
          {400, 200, 100, 1},
          {400, 400, 100, 1},
          {200, 400, 300, 1},
          {200, 200, 300, 1},
          {400, 200, 300, 1},
          {400, 400, 300, 1}};
    draw(AB);
    cout << " Управление:\n W - вверх, S - вниз, А - влево, D - вправо \n Q -
        увеличить, E - уменьшить¸\n Z - поворот по оси Z, X - поворот по оси X, C - поворот по оси Y\n Space - ";
    while (true)
    {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
            break;
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
            offset(AB, 0, -DY), draw(AB);

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
            offset(AB, 0, DY), draw(AB);
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            offset(AB, -DX, 0), draw(AB);
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            offset(AB, DX, 0), draw(AB);
        if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
            scale(AB, S1), draw(AB);

        if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
            scale(AB, S2), draw(AB);
        if (GetAsyncKeyState((unsigned short)'Z') & 0x80
            rotateZ(AB, ALPHA), draw(AB);
        if (GetAsyncKeyState((unsigned short)'X') & 0x8000)
            rotateX(AB, ALPHA), draw(AB);  
        if (GetAsyncKeyState((unsigned short)'C') & 0x8000)
            rotateY(AB, ALPHA), draw(AB);
        delay(10);
    }
    closegraph();
    return 0;
}

void mult(vector<vector<double> > &fig, vector<vector<double> > &mass)
{
    double res[N][M] = {0, 0, 0, 0};
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < M; j++)
                res[k][i] += fig[k][j] * mass[j][i];
        }
    }
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < M; i++)
            fig[k][i] = res[k][i];
    }
}

void offset(vector<vector<double> > &fig, double dx, double dy)
{
    vector<vector<double> > DX_DY(M, vector<double>(M));
    double dz = 5;
    DX_DY = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {dx, dy, dz, 1}};
    mult(fig, DX_DY);
}

void scale(vector<vector<double> > &fig, double S)
{
    double x1 = 0.0, y1 = 0.0, z1 = 0.0;
    int i;
    vector<vector<double> > Sx_Sy(M, vector<double>(M));
    for (i = 0; i < N; i++)
        x1 += fig[i][0];
    x1 = x1 / N;
    for (i = 0; i < N; i++)
        y1 += fig[i][1];
    y1 = y1 / N;
    for (i = 0; i < N; i++)
        z1 += fig[i][2];
    z1 = z1 / N;
    Sx_Sy = {{S, 0, 0, 0},
             {0, S, 0, 0},
             {0, 0, S, 0},
             {x1 * (1 - S), y1 * (1 - S), z1 * (1 - S), 1}};
    mult(fig, Sx_Sy);
}

void draw(vector<vector<double> > &fig1)
{
    clearviewport();
    vector<vector<double> > pro(M, vector<double>(M));
    int grad = 135;
    pro = {{1, 0, 0, 0},
           {0, 1, 0, 0},
           {0, 0, 1, 0},
           {0, 0, 0, 1}};
    mult(fig1, pro); 
    setcolor(color);
    line(fig1[0][0], fig1[0][1], fig1[1][0], fig1[1][1]);
    line(fig1[1][0], fig1[1][1], fig1[2][0], fig1[2][1]);
    line(fig1[2][0], fig1[2][1], fig1[3][0], fig1[3][1]);
    line(fig1[3][0], fig1[3][1], fig1[0][0], fig1[0][1]);
    setcolor(color + 1)
        line(fig1[4][0], fig1[4][1], fig1[5][0], fig1[5][1]);
    line(fig1[5][0], fig1[5][1], fig1[6][0], fig1[6][1]);
    line(fig1[6][0], fig1[6][1], fig1[7][0], fig1[7][1]);
    line(fig1[7][0], fig1[7][1], fig1[4][0], fig1[4][1]);
    setcolor(color + 2);
    line(fig1[0][0], fig1[0][1], fig1[4][0], fig1[4][1]);
    line(fig1[1][0], fig1[1][1], fig1[5][0], fig1[5][1]);
    line(fig1[2][0], fig1[2][1], fig1[6][0], fig1[6][1]);
    line(fig1[3][0], fig1[3][1], fig1[7][0], fig1[7][1]);
}

void rotateX(vector<vector<double> > &fig, double angle)
{
    double y = 0, z = 0;
    int i;
    for (i = 0; i < N; i++)
    {
        y += fig[i][1];
        z += fig[i][2];
    }
    y = y / N;
    z = z / N;
    vector<vector<double> > Angle(M, vector<double>(M));
    Angle = {{1, 0, 0, 0},
             {0, cos(angle), sin(angle), 0},
             {0, -sin(angle), cos(angle), 0},
             {0, y * (1 - cos(angle)) + z * sin(angle), z * (1 - cos(angle)) - y * sin(angle), 1}};
    mult(fig, Angle);
}

void rotateY(vector<vector<double> > &fig, double angle)
{
    double x = 0, y = 0, z = 0;
    int i;
    for (i = 0; i < N; i++)
    {
        x += fig[i][0];
        y += fig[i][1];
        z += fig[i][2];
    }
    x = x / N;
    y = y / N;
    z = z / N;
    vector<vector<double> > Angle(M, vector<double>(M));
    Angle = {{cos(angle), 0, -sin(angle), 0},
             {0, 1, 0, 0},
             {sin(angle), 0, cos(angle), 0},
             {x * (1 - cos(angle)) - z * sin(angle), 0, z * (1 - cos(angle)) + x * sin(angle), 1}};
    mult(fig, Angle);
}

void rotateZ(vector<vector<double> > &fig, double angle)
{
    double x = 0, y = 0;
    int i;
    for (i = 0; i < N; i++)
    {
        x += fig[i][0];
        y += fig[i][1];
    }
    x = x / N;
    y = y / N;
    vector<vector<double> > Angle(M, vector<double>(M));
    Angle = {{cos(angle), sin(angle), 0, 0},
             {-sin(angle), cos(angle), 0, 0},
             {0, 0, 1, 0},
             {x * (1 - cos(angle)) + y * sin(angle), y * (1 - cos(angle)) - x * sin(angle), 0, 1}};
    mult(fig, Angle);
}