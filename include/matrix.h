#ifndef MATRIX_H
#define MATRIX_H

#include <random>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix generateMatrix(int n, std::mt19937 &rng);

Matrix addMat(const Matrix &A, const Matrix &B);
Matrix subMat(const Matrix &A, const Matrix &B);

Matrix getSubmatrix(const Matrix &M, int rowStart, int colStart, int size);
void setSubmatrix(Matrix &dst, const Matrix &src, int rowStart, int colStart);

Matrix padMatrix(const Matrix &M, int m);
Matrix unpadMatrix(const Matrix &M, int n);
#endif // MATRIX_H
