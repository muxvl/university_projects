#include "figure.h"
#include <cmath>
#include <iostream>

figure::figure(BitMap *bmp, size_t numVer, size_t numFace)
{
    Ver = new vector[numVer];
    VerPR = new vector[numVer];
    VerSHDW = new vector[numVer];
    e.resize(figure::dim);
    result.resize(figure::dim);
    e.setVector(0.0, 0.0, 1.0, 0.0);

    for (size_t i = 0; i < numVer; ++i)
    {
        Ver[i].resize(figure::dim);
        VerPR[i].resize(figure::dim);
        VerSHDW[i].resize(figure::dim);
    }

    ROTATE.newMatrix(figure::dim, figure::dim);
    ZOOM.newMatrix(figure::dim, figure::dim);
    PR.newMatrix(figure::dim, figure::dim);
    V.newMatrix(figure::dim, numFace);

    double a1 = cos(PI / 6);
    double a2 = sin(PI / 6);
    double b1 = cos(PI / 6);
    double b2 = sin(PI / 6);

    PR.setMatrix(
        a1, -a2, 0.0, 0.0,
        a2 * b1, a1 * b1, -b2, 0.0,
        a2 * b2, a1 * b2, b1, 0.0,
        0.0, 0.0, 0.0, 1.0);
    matrix PR_(4, 4);

    PR_.setMatrix(
        a1, a2 * b1, a2 * b2, 0.0,
        -a2, a1 * b1, a1 * b2, 0.0,
        0.0, -b2, b1, 0.0,
        0.0, 0.0, 0.0, 1.0);
    e = PR_ * e;

    center.resize(figure::dim);
    sinAlpha = sin(ANGLE);
    cosAlpha = cos(ANGLE);
    this->numVer = numVer;
    this->numFace = numFace;
    this->bmp = bmp;
}

figure::~figure()
{
    delete[] Ver;
    delete[] VerPR;
    delete[] VerSHDW;
}

void figure::rotate(char ch, char pn)
{
    size_t i;
    ClrFigure();
    switch (ch)
    {
    case 'x':
        switch (pn)
        {
        case '+':
            ROTATE.setMatrix(
                1.0, 0.0, 0.0, 0.0,
                0.0, cosAlpha, sinAlpha, -cosAlpha * center[1] + center[1] - sinAlpha * center[2],
                0.0, -sinAlpha, cosAlpha, sinAlpha * center[1] + center[2] - cosAlpha * center[2],
                0.0, 0.0, 0.0, 1.0);
            break;
        case '-':
            ROTATE.setMatrix(
                1.0, 0.0, 0.0, 0.0,
                0.0, cosAlpha, -sinAlpha, -cosAlpha * center[1] + center[1] + sinAlpha * center[2],
                0.0, sinAlpha, cosAlpha, -sinAlpha * center[1] + center[2] - cosAlpha * center[2],
                0.0, 0.0, 0.0, 1.0 14);
            break;
        }
        break;
    case 'y':
        switch (pn)
        {
        case '+':
            ROTATE.setMatrix(
                cosAlpha, 0.0, -sinAlpha, -cosAlpha * center[0] + center[0] + sinAlpha * center[2],
                0.0, 1.0, 0.0, 0.0,
                sinAlpha, 0.0, cosAlpha, -sinAlpha * center[0] + center[2] - cosAlpha * center[2],
                0.0, 0.0, 0.0, 1.0);
            break;
        case '-':
            ROTATE.setMatrix(
                cosAlpha, 0.0, sinAlpha, -cosAlpha * center[0] + center[0] - sinAlpha * center[2],
                0.0, 1.0, 0.0, 0.0,
                -sinAlpha, 0.0, cosAlpha, sinAlpha * center[0] + center[2] - cosAlpha * center[2],
                0.0, 0.0, 0.0, 1.0);
            break;
        }
        break;
    case 'z':
        switch (pn)
        {
        case '+':
            ROTATE.setMatrix(
                cosAlpha, sinAlpha, 0.0, -cosAlpha * center[0] + center[0] - sinAlpha * center[1],
                -sinAlpha, cosAlpha, 0.0, sinAlpha * center[0] + center[1] - cosAlpha * center[1],
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
            break;
        case '-':
            ROTATE.setMatrix(
                cosAlpha, -sinAlpha, 0.0, -cosAlpha * center[0] + center[0] + sinAlpha * center[1],
                sinAlpha, cosAlpha, 0.0, -sinAlpha * center[0] + center[1] - cosAlpha * center[1],
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
            break;
        }
        break;
    default:
        return;
    }
    for (i = 0; i < numVer; ++i)
    {
        Ver[i] = ROTATE * Ver[i];
    }
    Body();
    Test();
    result = e * V;
}
void figure::move(char ch, char pn)
{
    size_t i, f = (ch == 'x') ? f = 0 : (ch == 'y') ? f = 1
                                                    : f = 2;
    15 int step;
    ClrFigure();
    if (pn == '+')
        step = STEP;
    else
        step = -STEP;
    for (i = 0; i < numVer; ++i)
    {
        Ver[i][f] += step;
    }
    center[f] += step;
}
void figure::zoom(char ch)
{
    size_t i;
    ClrFigure();
    if (ch == '+')
    {
        ZOOM.setMatrix(
            ZOOM_PLUS, 0.0, 0.0, -ZOOM_PLUS * center[0] + center[0],
            0.0, ZOOM_PLUS, 0.0, -ZOOM_PLUS * center[1] + center[1],
            0.0, 0.0, ZOOM_PLUS, -ZOOM_PLUS * center[2] + center[2],
            0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        ZOOM.setMatrix(
            ZOOM_MINUS, 0.0, 0.0, -ZOOM_MINUS * center[0] + center[0],
            0.0, ZOOM_MINUS, 0.0, -ZOOM_MINUS * center[1] + center[1],
            0.0, 0.0, ZOOM_MINUS, -ZOOM_MINUS * center[2] + center[2],
            0.0, 0.0, 0.0, 1.0);
    }
    for (i = 0; i < numVer; ++i)
    {
        Ver[i] = ZOOM * Ver[i];
    }
}
void figure::SetCenter()
{
    center[0] = 0.0;
    center[1] = 0.0;
    center[2] = 0.0;
    center[3] = 1.0;
    for (size_t i = 0; i < numVer; ++i)
    {
        center[0] += Ver[i][0];
        center[1] += Ver[i][1];
        center[2] += Ver[i][2];
    }
    center[0] /= double(numVer);
    center[1] /= double(numVer);
    center[2] /= double(numVer);
}
void figure::print()
{
    bmp->DrawBitmap();
}
void figure::SetShadow()
{
    for (size_t i = 0; i < numVer; ++i)
    {
        VerSHDW[i] = Ver[i];
        VerSHDW[i][1] = double(LIGHT::offset_Y);
    }
}
void figure::SetPR()
{
    for (size_t i = 0; i < numVer; ++i)
    {
        VerPR[i] = PR * Ver[i];
        VerSHDW[i] = PR * VerSHDW[i];
    }
}
void figure::SetBitMap()
{
    16 SetShadow();
    SetPR();
    SetFigure();
}
void figure::Test()
{
    int i;
    vector result(numFace);
    result = center * V;
    for (size_t j = 0; j < numFace; ++j)
        if (result[j] > 0)
        {
            for (i = 0; i < figure::dim; ++i)
                V(i, j) *= -1.0;
        }
}