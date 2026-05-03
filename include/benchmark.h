#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "matrix.h"
#include <random>

double measureMedian(int n, int reps, bool useStrassen, std::mt19937 &rng);

#endif // BENCHMARK_H
