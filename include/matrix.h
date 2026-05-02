
#ifndef MATRIX_H
#define MATRIX_H

#include <random>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix generateMatrix(int n, std::mt19937 &rng);

Matrix getSubmatrix(const Matrix &M, int rowStart, int colStart, int size);
void setSubmatrix(Matrix &dst, const Matrix &src, int rowStart, int colStart);

#endif // MATRIX_H
