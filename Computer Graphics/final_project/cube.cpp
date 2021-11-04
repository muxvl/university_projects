#include "cube.h"

cube::cube(BitMap *bmp, size_t numVer, size_t numFace)
    : figure(bmp, numVer, numFace)
{
    Ver[0].setVector(290.0, 90.0, 90.0, 1.0);
    Ver[1].setVector(340.0, 90.0, 90.0, 1.0);
    Ver[2].setVector(340.0, 190.0, 90.0, 1.0);
    Ver[3].setVector(290.0, 190.0, 90.0, 1.0);
    Ver[4].setVector(290.0, 90.0, 140.0, 1.0);
    Ver[5].setVector(340.0, 90.0, 140.0, 1.0);
    Ver[6].setVector(340.0, 190.0, 140.0, 1.0);
    Ver[7].setVector(290.0, 190.0, 140.0, 1.0);
    SetCenter();
    Body();
    Test();
    result = e * V;
    SetBitMap();
}
void cube::Body()
{
    int i;
    int step = 0;
    double a, b, c, d;
    double t;
    for (i = 0; i < 3; ++i)
    {
        d = 0;
        a = Ver[i + 1][1] - Ver[i][1];
        a *= (Ver[i + 4][2] - Ver[i][2]);
        t = Ver[i + 1][2] - Ver[i][2];
        t *= (Ver[i + 4][1] - Ver[i][1]);
        a -= t;
        d -= (a * Ver[i][0]);
        b = Ver[i + 1][0] - Ver[i][0];
        b *= (Ver[i + 4][2] - Ver[i][2]);
        t = Ver[i + 1][2] - Ver[i][2];
        t *= (Ver[i + 4][0] - Ver[i][0]);
        b = t - b;
        d -= (b * Ver[i][1]);
        c = Ver[i + 1][0] - Ver[i][0];
        c *= (Ver[i + 4][1] - Ver[i][1]);
        t = Ver[i + 1][1] - Ver[i][1];
        t *= (Ver[i + 4][0] - Ver[i][0]);
        c -= t;
        d -= (c * Ver[i][2]);
        V(0, i) = a;
        V(1, i) = b;
        V(2, i) = c;
        V(3, i) = d;
    }

    d = 0;
    a = Ver[i + 1][1] - Ver[0][1];
    a *= (Ver[i + 4][2] - Ver[0][2]);
    t = Ver[i + 1][2] - Ver[0][2];
    t *= (Ver[i + 4][1] - Ver[0][1]);
    a -= t;
    d -= (a * Ver[0][0]);
    b = Ver[i + 1][0] - Ver[0][0];
    b *= (Ver[i + 4][2] - Ver[0][2]);
    t = Ver[i + 1][2] - Ver[0][2];
    t *= (Ver[i + 4][0] - Ver[0][0]);
    b = t - b;
    d -= (b * Ver[0][1]);
    c = Ver[i + 1][0] - Ver[0][0];
    c *= (Ver[i + 4][1] - Ver[0][1]);
    t = Ver[i + 1][1] - Ver[0][1];
    11 t *= (Ver[i + 4][0] - Ver[0][0]);
    c -= t;
    d -= (c * Ver[0][2]);
    V(0, i) = a;
    V(1, i) = b;
    V(2, i) = c;
    V(3, i++) = d;

    do
    {
        d = 0;
        a = Ver[i + 1 - step][1] - Ver[i - step][1];
        a *= (Ver[i - step + 2][2] - Ver[i - step][2]);
        t = Ver[i - step + 1][2] - Ver[i - step][2];
        t *= (Ver[i - step + 2][1] - Ver[i - step][1]);
        a -= t;
        d -= (a * Ver[i - step][0]);
        b = Ver[i - step + 1][0] - Ver[i - step][0];
        b *= (Ver[i - step + 2][2] - Ver[i - step][2]);
        t = Ver[i - step + 1][2] - Ver[i - step][2];
        t *= (Ver[i - step + 2][0] - Ver[i - step][0]);
        b = t - b;
        d -= (b * Ver[i - step][1]);
        c = Ver[i - step + 1][0] - Ver[i - step][0];
        c *= (Ver[i - step + 2][1] - Ver[i - step][1]);
        t = Ver[i - step + 1][1] - Ver[i - step][1];
        t *= (Ver[i - step + 2][0] - Ver[i - step][0]);
        c -= t;
        d -= (c * Ver[i - step][2]);
        V(0, i) = a;
        V(1, i) = b;
        V(2, i) = c;
        V(3, i) = d;
        step = 5;
    } while (++i < 6);
}
void cube::ClrFigure()
{
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[4], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[2], VerSHDW[5], VerSHDW[6], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[2], VerSHDW[3], VerSHDW[6], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[3], VerSHDW[6], VerSHDW[7], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[3], VerSHDW[4], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[3], VerSHDW[4], VerSHDW[7], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[4], VerSHDW[5], VerSHDW[6], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[4], VerSHDW[6], VerSHDW[7], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::clear));
    if (result[0] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[4], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[1], VerPR[4], VerPR[5], COLORREF(COL_BMP::clear));
    }
    if (result[1] > 0)
    {
        paintTRIN(bmp, VerPR[1], VerPR[2], VerPR[5], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[2], VerPR[5], VerPR[6], COLORREF(COL_BMP::clear));
    }
    if (result[2] > 0)
    {
        paintTRIN(bmp, VerPR[2], VerPR[3], VerPR[6], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[3], VerPR[6], VerPR[7], COLORREF(COL_BMP::clear));
        12
    }
    if (result[3] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[3], VerPR[4], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[3], VerPR[4], VerPR[7], COLORREF(COL_BMP::clear));
    }
    if (result[4] > 0)
    {
        paintTRIN(bmp, VerPR[4], VerPR[5], VerPR[6], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[4], VerPR[6], VerPR[7], COLORREF(COL_BMP::clear));
    }
    if (result[5] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[2], COLORREF(COL_BMP::clear));
        paintTRIN(bmp, VerPR[0], VerPR[2], VerPR[3], COLORREF(COL_BMP::clear));
    }
}
void cube::SetFigure()
{
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[4], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[2], VerSHDW[5], VerSHDW[6], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[2], VerSHDW[3], VerSHDW[6], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[3], VerSHDW[6], VerSHDW[7], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[3], VerSHDW[4], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[3], VerSHDW[4], VerSHDW[7], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[4], VerSHDW[5], VerSHDW[6], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[4], VerSHDW[6], VerSHDW[7], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::shadow));
    if (result[0] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[4], COLORREF(CUBE::zero));
        paintTRIN(bmp, VerPR[1], VerPR[4], VerPR[5], COLORREF(CUBE::zero));
    }
    if (result[1] > 0)
    {
        paintTRIN(bmp, VerPR[1], VerPR[2], VerPR[5], COLORREF(CUBE::one));
        paintTRIN(bmp, VerPR[2], VerPR[5], VerPR[6], COLORREF(CUBE::one));
    }
    if (result[2] > 0)
    {
        paintTRIN(bmp, VerPR[2], VerPR[3], VerPR[6], COLORREF(CUBE::two));
        paintTRIN(bmp, VerPR[3], VerPR[6], VerPR[7], COLORREF(CUBE::two));
    }
    if (result[3] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[3], VerPR[4], COLORREF(CUBE::three));
        paintTRIN(bmp, VerPR[3], VerPR[4], VerPR[7], COLORREF(CUBE::three));
    }
    if (result[4] > 0)
    {
        paintTRIN(bmp, VerPR[4], VerPR[5], VerPR[6], COLORREF(CUBE::four));
        paintTRIN(bmp, VerPR[4], VerPR[6], VerPR[7], COLORREF(CUBE::four));
    }
    if (result[5] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[2], COLORREF(CUBE::five));
        paintTRIN(bmp, VerPR[0], VerPR[2], VerPR[3], COLORREF(CUBE::five));
    }
}