#include "../include/multiply.h"

static const int BASE = 32;

Matrix standardMul(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        C[i][j] += A[i][k] * B[k][j];
  return C;
}
