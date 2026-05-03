
#include "../include/benchmark.h"
#include "../include/multiply.h"
#include <algorithm>
#include <chrono>
#include <vector>

double measureMedian(int n, int reps, bool useStrassen, std::mt19937 &rng) {
  std::vector<double> times(reps);

  for (int r = 0; r < reps; r++) {
    Matrix A = generateMatrix(n, rng);
    Matrix B = generateMatrix(n, rng);

    auto start = std::chrono::high_resolution_clock::now();
    if (useStrassen)
      strassenMul(A, B);
    else
      standardMul(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    times[r] = std::chrono::duration<double, std::milli>(end - start).count();
  }

  std::sort(times.begin(), times.end());

  if (reps % 2 == 0)
    return (times[reps / 2 - 1] + times[reps / 2]) / 2.0;
  else
    return times[reps / 2];
}
