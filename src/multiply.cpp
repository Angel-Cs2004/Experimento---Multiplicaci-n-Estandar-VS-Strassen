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
Matrix strassenMul(const Matrix &A, const Matrix &B) {
  int n = A.size();

  if (n <= BASE)
    return standardMul(A, B);

  int half = n / 2;
  // futura implementacion de la separacion de cuadrantes

  // aplicacion de las 7 productos y 18 sumas
  Matrix C(n, std::vector<double>(n, 0.0));

  return C;
}
