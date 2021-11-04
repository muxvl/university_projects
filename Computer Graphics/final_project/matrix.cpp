#include "matrix.h"

matrix::matrix() : data(nullptr), rows(0), cols(0) {}
matrix::matrix(int N, int M)
{
    data = nullptr;
    newMatrix(N, M);
}
matrix::~matrix()
{
    newMatrix(0, 0);
}
void matrix::newMatrix(int N, int M)
{
    int i;
    delete[] data;
    if (N && M)
    {
        data = new vector[M];
        for (i = 0; i < M; ++i)
            data[i].resize(N);
        rows = N;
        cols = M;
    }
    else
    {
        data = nullptr;
        rows = cols = 0;
    }
}
void matrix::setMatrix(double Element...)
{
    int i, j;
    va_list ap;
    va_start(ap, Element);
    data[0][0] = Element;
    for (j = 1; j < cols; j++)
    {
        data[j][0] = (double)va_arg(ap, double);
    }
    for (i = 1; i < rows; ++i)
        for (j = 0; j < cols; j++)
        {
            data[j][i] = (double)va_arg(ap, double);
        }
    va_end(ap);
}
vector operator*(const matrix &A, const vector &a)
{
    int i, j;
    vector resVector;
    resVector.resize(a.size());
    for (i = 0; i < A.rows; ++i)
    {
        resVector[i] = 0;
        for (j = 0; j < A.cols; ++j)
        {
            resVector[i] += A.data[j][i] * a[j];
        }
    }
    18 return resVector;
}
vector operator*(const vector &a, const matrix &A)
{
    int i, j;
    vector resVector;
    resVector.resize(A.cols);
    for (i = 0; i < A.cols; ++i)
    {
        resVector[i] = 0.0;
        for (j = 0; j < A.rows; ++j)
            resVector[i] += a[j] * A.data[i][j];
    }
    return resVector;
}