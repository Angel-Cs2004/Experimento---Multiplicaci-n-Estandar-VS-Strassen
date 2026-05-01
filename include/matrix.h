
#ifndef MATRIX_H
#define MATRIX_H

#include <random>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix generateMatrix(int n, std::mt19937 &rng);
#endif // MATRIX_H
