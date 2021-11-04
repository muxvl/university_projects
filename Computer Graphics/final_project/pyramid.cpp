#include "pyramid.h"

pyramid::pyramid(BitMap *bmp, size_t numVer, size_t numFace)
    : figure(bmp, numVer, numFace)
{
    Ver[0].setVector(290.0, 90.0, 90.0, 1.0);
    Ver[1].setVector(390.0, 90.0, 90.0, 1.0);
    Ver[2].setVector(295.0, 190.0, 90.0, 1.0);
    Ver[3].setVector(320.0, 110.0, 190.0, 1.0);
    SetCenter();
    Body();
    Test();
    result = e * V;
    SetBitMap();
}
void pyramid::Body()
{
    int i;
    int step = 0;
    double a, b, c, d;
    double t;
    for (i = 0; i < 2; ++i)
    {
        d = 0;
        a = Ver[i + 1][1] - Ver[i][1];
        a *= (Ver[i + 2][2] - Ver[i][2]);
        t = Ver[i + 1][2] - Ver[i][2];
        t *= (Ver[i + 2][1] - Ver[i][1]);
        a -= t;
        d -= (a * Ver[i][0]);
        b = Ver[i + 1][0] - Ver[i][0];
        b *= (Ver[i + 2][2] - Ver[i][2]);
        t = Ver[i + 1][2] - Ver[i][2];
        t *= (Ver[i + 2][0] - Ver[i][0]);
        b = t - b;
        d -= (b * Ver[i][1]);
        c = Ver[i + 1][0] - Ver[i][0];
        c *= (Ver[i + 2][1] - Ver[i][1]);
        t = Ver[i + 1][1] - Ver[i][1];
        t *= (Ver[i + 2][0] - Ver[i][0]);
        c -= t;
        d -= (c * Ver[i][2]);
        V(0, i) = a;
        V(1, i) = b;
        V(2, i) = c;
        V(3, i) = d;
    }
    for (i = 0; i < 2; ++i)
    {
        d = 0;
        19 a = Ver[i + 1][1] - Ver[0][1];
        a *= (Ver[3][2] - Ver[0][2]);
        t = Ver[i + 1][2] - Ver[0][2];
        t *= (Ver[3][1] - Ver[0][1]);
        a -= t;
        d -= (a * Ver[0][0]);
        b = Ver[i + 1][0] - Ver[0][0];
        b *= (Ver[3][2] - Ver[0][2]);
        t = Ver[i + 1][2] - Ver[0][2];
        t *= (Ver[3][0] - Ver[0][0]);
        b = t - b;
        d -= (b * Ver[0][1]);
        c = Ver[i + 1][0] - Ver[0][0];
        c *= (Ver[3][1] - Ver[0][1]);
        t = Ver[i + 1][1] - Ver[0][1];
        t *= (Ver[3][0] - Ver[0][0]);
        c -= t;
        d -= (c * Ver[0][2]);
        V(0, i + 2) = a;
        V(1, i + 2) = b;
        V(2, i + 2) = c;
        V(3, i + 2) = d;
    }
}
void pyramid::ClrFigure()
{
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[3], COLORREF(COL_BMP::clear));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::clear));
    if (result[0] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[2], COLORREF(COL_BMP::clear));
    }
    if (result[1] > 0)
    {
        paintTRIN(bmp, VerPR[1], VerPR[2], VerPR[3], COLORREF(COL_BMP::clear));
    }
    if (result[2] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[3], COLORREF(COL_BMP::clear));
    }
    if (result[3] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[2], VerPR[3], COLORREF(COL_BMP::clear));
    }
}
void pyramid::SetFigure()
{
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[3], COLORREF(COL_BMP::shadow));
    paintTRIN(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[3], COLORREF(COL_BMP::shadow));
    if (result[0] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[2], COLORREF(PYR::zero));
    }
    if (result[1] > 0)
    {
        paintTRIN(bmp, VerPR[1], VerPR[2], VerPR[3], COLORREF(PYR::one));
    }
    if (result[2] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[1], VerPR[3], COLORREF(PYR::two));
    }
    if (result[3] > 0)
    {
        paintTRIN(bmp, VerPR[0], VerPR[2], VerPR[3], COLORREF(PYR::three));
    }
}