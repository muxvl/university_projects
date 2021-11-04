#include <iostream>
#include <graphics.h>
#include <locale.h>
#include <math.h>
#define N 8
#define M 4
#define MAXARR 300
#define MAXLST 300

using namespace std;

double *Py;
double *Px;
static int KOD, NWER;
static double *pt_X;
static double *pt_Y;
static int ntek;
static int idlspi;
static int IYREB[MAXLST];
static float RXREB[MAXLST];
static float RPRIR[MAXLST];
void FILSTR(int kod, int iy, double ixn, double ixk);
void SORT(int n, double *iarr);
static void OBRREB(int isd);
void V_FP0(int pixel, int kol, double *Px, double *Py);
const int DX = 5, DY = 5, color = 11;
const double S1 = 1.1;
const double S2 = 0.95;
const double ALPHA = 0.087;
void mult(double fig[N][M], double mass[M][M]);
void offset(double fig[N][M], double dx, double dy);
void scale(double fig[N][M], double S);
void rotateZ(double fig[N][M], double angle);
void rotateY(double fig[N][M], double angle);
void rotateX(double fig[N][M], double angle);
void draw(double fig1[N][M]);
double aver(double range[N][M], int a);
void painter(double fig[N][M]);

int main()
{
    setlocale(LC_ALL, "Russian");
    initwindow(1000, 600, "", 100, 100);
    double figure[N][M] = {{200, 400, 100, 1},
                           {200, 200, 100, 1},
                           {400, 200, 100, 1},
                           {400, 400, 100, 1},
                           {200, 400, 300, 1},
                           {200, 200, 300, 1},
                           {400, 200, 300, 1},
                           {400, 400, 300, 1}};
    double pro[M][M] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
    mult(figure, pro);
    setcolor(4);
    draw(figure);
    cout << " Î‡‚Ë¯Ë ÛÔ‡‚ÎÂÌËˇ:\n W - ‚‚Âı, S - ‚ÌËÁ, ¿ - ‚ÎÂ‚Ó, D - ‚Ô‡‚Ó \n Q -
    Û‚ÂÎË˜ËÚ¸, E - ÛÏÂÌ¸¯ËÚ¸\n Z - ÔÓ Z, X - Ôo X, C - ÔÓ Y\n Space - ‚˚ıÓ‰";
    cout << "-----------------------------------------\nВыход - esc." << endl;
    do
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            break;
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
            offset(figure, 0, -DY), draw(figure);
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
            offset(figure, 0, DY), draw(figure);
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            offset(figure, -DX, 0), draw(figure);
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            offset(figure, DX, 0), draw(figure);
        if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
            scale(figure, S1), draw(figure);
        if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
            scale(figure, S2), draw(figure);
        if (GetAsyncKeyState((unsigned short)'Z') & 0x8000)
            rotateY(figure, -ALPHA), draw(figure);
        if (GetAsyncKeyState((unsigned short)'X') & 0x8000)
            rotateY(figure, ALPHA), draw(figure);
        if (GetAsyncKeyState((unsigned short)'C') & 0x8000)
            rotateX(figure, -ALPHA), draw(figure);
        if (GetAsyncKeyState((unsigned short)'V') & 0x8000)
            rotateX(figure, ALPHA), draw(figure);
        if (GetAsyncKeyState((unsigned short)'B') & 0x8000)
            rotateZ(figure, -ALPHA), draw(figure);
        if (GetAsyncKeyState((unsigned short)'N') & 0x8000)
            rotateZ(figure, ALPHA), draw(figure);
        delay(10);
    } while (true);
    closegraph();
    return 0;
}

void mult(double fig[N][M], double mass[M][M])
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

void offset(double fig[N][M], double dx, double dy)
{
    double dz = 5;
    double DX_DY[M][M] = {{1, 0, 0, 0},
                          {0, 1, 0, 0},
                          {0, 0, 1, 0},
                          {dx, dy, dz, 1}};
    mult(fig, DX_DY);
}

void scale(double fig[N][M], double S)
{
    double x = 0, y = 0, z = 0;
    x = aver(fig, 0);
    y = aver(fig, 1);
    z = aver(fig, 2);
    double Sx_Sy[M][M] = {{S, 0, 0, 0},
                          {0, S, 0, 0},
                          {0, 0, S, 0},
                          {x * (1 - S), y * (1 - S), z * (1 - S), 1}};
    mult(fig, Sx_Sy);
}

void draw(double fig1[N][M])
{
    clearviewport();
    setcolor(color);
    line(fig1[0][0], fig1[0][1], fig1[1][0], fig1[1][1]);
    line(fig1[1][0], fig1[1][1], fig1[2][0], fig1[2][1]);
    line(fig1[2][0], fig1[2][1], fig1[3][0], fig1[3][1]);
    line(fig1[3][0], fig1[3][1], fig1[0][0], fig1[0][1]);
    setcolor(color + 2);
    line(fig1[4][0], fig1[4][1], fig1[5][0], fig1[5][1]);
    line(fig1[5][0], fig1[5][1], fig1[6][0], fig1[6][1]);
    line(fig1[6][0], fig1[6][1], fig1[7][0], fig1[7][1]);
    line(fig1[7][0], fig1[7][1], fig1[4][0], fig1[4][1]);
    setcolor(color + 3);
    line(fig1[0][0], fig1[0][1], fig1[4][0], fig1[4][1]);
    line(fig1[1][0], fig1[1][1], fig1[5][0], fig1[5][1]);
    line(fig1[2][0], fig1[2][1], fig1[6][0], fig1[6][1]);
    line(fig1[3][0], fig1[3][1], fig1[7][0], fig1[7][1]);
    painter(fig1);
}

void rotateX(double fig[N][M], double angle)
{
    double y = 0, z = 0;
    y = aver(fig, 1);
    z = aver(fig, 2);
    double Angle[M][M] = {{1, 0, 0, 0},
                          {0, cos(angle), sin(angle), 0},
                          {0, -sin(angle), cos(angle), 0},
                          {0, y * (1 - cos(angle)) + z * sin(angle), z * (1 - cos(angle)) - y * sin(angle), 1}};
    mult(fig, Angle);
}

void rotateY(double fig[N][M], double angle)
{
    double x = 0, y = 0, z = 0;
    x = aver(fig, 0);
    z = aver(fig, 2);
    double Angle[M][M] = {{cos(angle), 0, -sin(angle), 0},
                          {0, 1, 0, 0},
                          {sin(angle), 0, cos(angle), 0},
                          {x * (1 - cos(angle)) - z * sin(angle), 0, z * (1 - cos(angle)) + x * sin(angle), 1}};
    mult(fig, Angle);
}

void rotateZ(double fig[N][M], double angle)
{
    double x = 0, y = 0;
    x = aver(fig, 0);
    y = aver(fig, 1);
    double Angle[M][M] = {{cos(angle), sin(angle), 0, 0},
                          {-sin(angle), cos(angle), 0, 0},
                          {0, 0, 1, 0},
                          {x * (1 - cos(angle)) + y * sin(angle), y * (1 - cos(angle)) - x * sin(angle), 0, 1}};
    mult(fig, Angle);
}

double aver(double fig[N][M], int cnt)
{
    double average = 0;
    for (int i = 0; i < N; i++)
    {
        average += fig[i][cnt];
    }
    return average / N;
}

void V_FP0(int pixel, int kol, double *Px, double *Py)
{
    int ii, jj, kk;
    int iymin;
    int iymax;
    int iysled;
    int iytek;
    int ikledg;
    int ibgind;
    int iedg[MAXARR];
    int inom[MAXARR];
    double irabx[MAXLST];
    KOD = pixel;
    NWER = kol;
    pt_X = Px;
    pt_Y = Py;
    for (int i = 1; i <= kol; ++i)
    {
        iedg[i] = Py[i];
        inom[i] = i;
    }
    for (int i = 1; i <= kol; ++i)
    {
        iymin = iedg[i];
        ntek = i;
        for (int j = i + 1; j <= kol; ++j)
            if (iedg[j] < iymin)
            {
                iymin = iedg[j];
                ntek = j;
            }
        if (ntek != i)
        {
            iedg[ntek] = iedg[i];
            iedg[i] = iymin;
            iymin = inom[ntek];
            inom[ntek] = inom[i];
            inom[i] = iymin;
        }
    }
    idlspi = 0;
    ibgind = 1;
    iytek = iedg[1];
    iymax = iedg[kol];
    for (;;)
    {
        ikledg = 0;
        for (int i = ibgind; i <= kol; ++i)
            if (iedg[i] != iytek)
                break;
            else
                ikledg++;
        for (int i = 1; i <= ikledg; ++i)
        {
            ntek = inom[ibgind + i - 1];
            OBRREB(-1);
            OBRREB(+1);
        }
        if (!idlspi)
            break;
        ii = ibgind + ikledg;
        iysled = iymax;
        if (ii < kol)
            iysled = iedg[ii];
        for (double i = iytek; i <= iysled; ++i)
        {
            for (int j = 1; j <= idlspi; ++j)
                irabx[j] = RXREB[j];
            SORT(idlspi, irabx + 1);
            for (int j = 1; j <= idlspi - 1; j += 2)
                FILSTR(pixel, i, round(irabx[j]), round(irabx[j + 1]));
            if (i == iysled)
                continue;
            for (int j = 1; j <= idlspi; ++j)
                RXREB[j] = RXREB[j] + RPRIR[j];
        }
        if (iysled == iymax)
            break;
        for (ii = 0; ii <= idlspi; ii++)
        {
            if (IYREB[ii] != iysled)
                continue;
            --idlspi;
            for (jj = ii; jj <= idlspi; ++jj)
            {
                IYREB[jj] = IYREB[kk = jj + 1];
                RXREB[jj] = RXREB[kk];
                RPRIR[jj] = RPRIR[kk];
            }
        }
        ibgind += ikledg;
        iytek = iysled;
    }
}

static void OBRREB(int isd)
{
    int inext, iyt, ixt;
    double xt, xnext, dy;
    inext = ntek + isd;
    if (inext < 1)
        inext = NWER;
    if (inext > NWER)
        inext = 1;
    dy = pt_Y[inext] - pt_Y[ntek];
    if (dy >= 0)
    {
        xnext = pt_X[inext];
        xt = pt_X[ntek];
        if (dy != 0)
        {
            idlspi++;
            IYREB[idlspi] = pt_Y[inext];
            RXREB[idlspi] = xt;
            RPRIR[idlspi] = (xnext - xt) / dy;
        }
        else
        {
            iyt = pt_Y[ntek];
            inext = xnext;
            ixt = xt;
            FILSTR(KOD, iyt, round(inext), round(ixt));
        }
    }
}

void SORT(int n, double *iarr)
{
    int l;
    double k, min;
    for (int i = 0; i < n; ++i)
    {
        min = iarr[l = i];
        for (int j = i + 1; j < n; ++j)
            if ((k = iarr[j]) < min)
            {
                l = j;
                min = k;
            }
        if (l != i)
        {
            iarr[l] = iarr[i];
            iarr[i] = min;
        }
    }
}

void FILSTR(int kod, int iy, double ixn, double ixk)
{
    while (ixn <= ixk)
        putpixel(ixn++, iy, kod);
}

void painter(double fig[N][M])
{
    double Pol[6] = {}, Pol1[7] = {}, min = 0;
    int ntek, inom[7] = {};
    //среднее значение глубины
    Pol[0] = (fig[0][2] + fig[1][2] + fig[2][2] + fig[3][2]) / 4; //ABCD
    Pol[1] = (fig[4][2] + fig[5][2] + fig[6][2] + fig[7][2]) / 4; //A1B1C1D1
    Pol[2] = (fig[0][2] + fig[4][2] + fig[3][2] + fig[7][2]) / 4; //AA1DD1
    Pol[3] = (fig[7][2] + fig[3][2] + fig[2][2] + fig[6][2]) / 4; //CC1DD1
    Pol[4] = (fig[1][2] + fig[5][2] + fig[2][2] + fig[6][2]) / 4; //BB1CC1
    Pol[5] = (fig[1][2] + fig[4][2] + fig[0][2] + fig[5][2]) / 4; //AA1BB1
    for (int i = 1; i <= 6; ++i)
    {
        Pol1[i] = Pol[i - 1];
        inom[i] = i;
    }
    for (int i = 1; i <= 6; ++i)
    {
        min = Pol1[i];
        ntek = i;
        for (int j = i + 1; j <= 6; ++j)
            if (Pol1[j] <= min)
            {
                min = Pol1[j];
                ntek = j;
            }
        if (ntek != i)
        {
            Pol1[ntek] = Pol1[i];
            Pol1[i] = min;
            min = inom[ntek];
            inom[ntek] = inom[i];
            inom[i] = min;
        }
    }
    int num;
    for (int i = 1; i <= 7; i++)
    {
        Px = new double[4 + 1];
        Py = new double[4 + 1];
        num = inom[i];
        switch (num)
        {
        case 1:
            Px[1] = fig[0][0];
            Py[1] = fig[0][1];
            Px[2] = fig[1][0];
            Py[2] = fig[1][1];
            Px[3] = fig[2][0];
            Py[3] = fig[2][1];
            Px[4] = fig[3][0];
            Py[4] = fig[3][1];
            V_FP0(11, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        case 2:
            Px[1] = fig[4][0];
            Py[1] = fig[4][1];
            Px[2] = fig[5][0];
            Py[2] = fig[5][1];
            Px[3] = fig[6][0];
            Py[3] = fig[6][1];
            Px[4] = fig[7][0];
            Py[4] = fig[7][1];
            V_FP0(12, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        case 3:
            Px[1] = fig[0][0];
            Py[1] = fig[0][1];
            Px[2] = fig[3][0];
            Py[2] = fig[3][1];
            Px[3] = fig[7][0];
            Py[3] = fig[7][1];
            Px[4] = fig[4][0];
            Py[4] = fig[4][1];
            V_FP0(13, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        case 4:
            Px[1] = fig[7][0];
            Py[1] = fig[7][1];
            Px[2] = fig[3][0];
            Py[2] = fig[3][1];
            Px[3] = fig[2][0];
            Py[3] = fig[2][1];
            Px[4] = fig[6][0];
            Py[4] = fig[6][1];
            V_FP0(14, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        case 5:
            Px[1] = fig[1][0];
            Py[1] = fig[1][1];
            Px[2] = fig[5][0];
            Py[2] = fig[5][1];
            Px[3] = fig[6][0];
            Py[3] = fig[6][1];
            Px[4] = fig[2][0];
            Py[4] = fig[2][1];
            V_FP0(15, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        case 6:
            Px[1] = fig[0][0];
            Py[1] = fig[0][1];
            Px[2] = fig[4][0];
            Py[2] = fig[4][1];
            Px[3] = fig[5][0];
            Py[3] = fig[5][1];
            Px[4] = fig[1][0];
            Py[4] = fig[1][1];
            V_FP0(16, 4, Px, Py);
            delete[] Px;
            delete[] Py;
            break;
        }
    }
}