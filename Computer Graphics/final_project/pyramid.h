#pragma once
#include "figure.h"
class pyramid : public figure
{
public:
    pyramid(BitMap *bmp, size_t numVer, size_t numFace);

private:
    void SetFigure();
    void ClrFigure();
    void Body();
};