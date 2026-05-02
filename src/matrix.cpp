#include "../include/matrix.h"

Matrix generateMatrix(int n, std::mt19937 &rng) {
  std::uniform_real_distribution<double> dist(-10, 10);
  Matrix M(n, std::vector<double>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      M[i][j] = dist(rng);
  return M;
}

Matrix getSubmatrix(const Matrix &M, int rowStart, int colStart, int size) {
  Matrix sub(size, std::vector<double>(size));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      sub[i][j] = M[rowStart + i][colStart + j];
  return sub;
}

void setSubmatrix(Matrix &dst, const Matrix &src, int rowStart, int colStart) {
  int size = src.size();
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      dst[rowStart + i][colStart + j] = src[i][j];
}
