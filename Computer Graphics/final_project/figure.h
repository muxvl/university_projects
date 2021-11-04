#pragma once
#include <windows.h>
#include "matrix.h"
#include "bitmap.h"
#include "function.h"
#define PI 3.141592
enum class DIM_BMP_ONE
{
    left_margin = 10,
    top_margin = 10,
    width = 600,
    height = 610
};
enum class DIM_BMP_TWO
{
    left_margin = 616,
    top_margin = 10,
    width = 600,
    height = 610
};
enum class COL_BMP
{
    clear = RGB_BMP(255, 255, 255),
    shadow = RGB_BMP(30, 30, 30)
};
enum class PYR
{
    zero = RGB_BMP(200, 50, 200),
    one = RGB_BMP(50, 200, 200),
    two = RGB_BMP(123, 104, 238),
    three = RGB_BMP(255, 165, 31)
};
enum class CUBE
{
    zero = RGB_BMP(200, 50, 200),
    one = RGB_BMP(50, 200, 200),
    two = RGB_BMP(123, 104, 238),
    three = RGB_BMP(255, 165, 31),
    four = RGB_BMP(244, 66, 140),
    five = RGB_BMP(77, 244, 123)
};
enum class NUM_VER
{
    pyr = 4,
    cube = 8
};
enum class NUM_FACE
{
    pyr = 4,
    cube = 6
};
enum class LIGHT
{
    offset_Y = 450
};
const double ANGLE = 0.05;
const int STEP = 6;
const double ZOOM_PLUS = 1.25;
const double ZOOM_MINUS = 1 / ZOOM_PLUS;
class figure
{
public:
    enum
    {
        dim = 4
    };
    figure(BitMap *bmp, size_t numVer, size_t numFace);
    ~figure();
    void rotate(char, char);
    void move(char, char);
    void zoom(char);
    void print();
    void SetBitMap();

protected:
    virtual void SetFigure() = 0;
    virtual void ClrFigure() = 0;
    virtual void Body() = 0;
    void Test();
    matrix V;
    size_t numFace;
    vector e;
    vector *VerPR;
    void SetPR();
    double sinAlpha;
    double cosAlpha;
    vector center;
    void SetCenter();
    vector *Ver;
    size_t numVer;
    matrix ROTATE;
    matrix ZOOM;
    vector result;
    matrix PR;
    BitMap *bmp;
    vector *VerSHDW;
    void SetShadow();
};