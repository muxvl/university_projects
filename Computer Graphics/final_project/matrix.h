#pragma once
#include "vector.h"
class matrix
{
public:
    matrix();
    matrix(int M, int N);
    ~matrix();
    void newMatrix(int M, int N);
    void setMatrix(double Element...);
    friend vector operator*(const matrix &, const vector &a);
    friend vector operator*(const vector &a, const matrix &A);
    double &operator()(int i, int j) { return data[j][i]; };

private:
    int rows;
    int cols;
    vector *data;
};