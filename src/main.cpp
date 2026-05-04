
#include "../include/benchmark.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::vector<int> sizes = {4,   8,   12,  16,  20,  24,  28,  32,
                            36,  40,  48,  56,  64,  80,  96,  112,
                            128, 160, 192, 224, 256, 320, 384, 512};
  int reps = 10;
  std::mt19937 rng(42);

  std::cout << std::fixed << std::setprecision(6);
  std::cout << "# n  t_standard_ms  t_strassen_ms\n";

  for (int n : sizes) {
    double tStd = measureMedian(n, reps, false, rng);
    double tStrassen = measureMedian(n, reps, true, rng);

    std::cout << n << "  " << tStd << "  " << tStrassen << "\n";
    std::cerr << "n=" << std::setw(4) << n << "  std=" << std::setw(10) << tStd
              << " ms"
              << "  strassen=" << std::setw(10) << tStrassen << " ms\n";
  }

  return 0;
}
