
#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "matrix.h"

Matrix standardMul(const Matrix &A, const Matrix &B);
Matrix strassenMul(const Matrix &A, const Matrix &B);

#endif // MULTIPLY_H
