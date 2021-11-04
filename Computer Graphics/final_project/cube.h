#pragma once
#include "figure.h"
class cube : public figure
{
public:
    cube(BitMap *bmp, size_t numVer, size_t numFace);

private:
    void SetFigure();
    void ClrFigure();
    void Body();
};