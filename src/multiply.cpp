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
  Matrix A11 = getSubmatrix(A, 0, 0, half);
  Matrix A12 = getSubmatrix(A, 0, half, half);
  Matrix A21 = getSubmatrix(A, half, 0, half);
  Matrix A22 = getSubmatrix(A, half, half, half);

  Matrix B11 = getSubmatrix(B, 0, 0, half);
  Matrix B12 = getSubmatrix(B, 0, half, half);
  Matrix B21 = getSubmatrix(B, half, 0, half);
  Matrix B22 = getSubmatrix(B, half, half, half);
  // aplicacion de las 7 productos y 18 sumas
  Matrix P1 = strassenMul(A11, subMat(B12, B22));
  Matrix P2 = strassenMul(addMat(A11, A12), B22);
  Matrix P3 = strassenMul(addMat(A21, A22), B11);
  Matrix P4 = strassenMul(A22, subMat(B21, B11));
  Matrix P5 = strassenMul(addMat(A11, A22), addMat(B11, B22));
  Matrix P6 = strassenMul(subMat(A12, A22), addMat(B21, B22));
  Matrix P7 = strassenMul(subMat(A11, A21), addMat(B11, B12));

  Matrix C11 = addMat(subMat(addMat(P5, P4), P2), P6);
  Matrix C12 = addMat(P1, P2);
  Matrix C21 = addMat(P3, P4);
  Matrix C22 = subMat(subMat(addMat(P5, P1), P3), P7);

  Matrix C(n, std::vector<double>(n, 0.0));

  setSubmatrix(C, C11, 0, 0);
  setSubmatrix(C, C12, 0, half);
  setSubmatrix(C, C21, half, 0);
  setSubmatrix(C, C22, half, half);
  return C;
}
