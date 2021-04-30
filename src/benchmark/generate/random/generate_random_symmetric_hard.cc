#include <benchmark/benchmark.h>

#include "generate/generate_random_hard.h"

const int kRuns{100000};
const int kIterations{1};

static void BM_GenerateRandomSymmetricHard20(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(20);
    }
  }
}

static void BM_GenerateRandomSymmetricHard24(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(24);
    }
  }
}

static void BM_GenerateRandomSymmetricHard30(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(30);
    }
  }
}

static void BM_GenerateRandomSymmetricHard34(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(34);
    }
  }
}

static void BM_GenerateRandomSymmetricHard40(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(40);
    }
  }
}

static void BM_GenerateRandomSymmetricHard44(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(44);
    }
  }
}

static void BM_GenerateRandomSymmetricHard50(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(50);
    }
  }
}

static void BM_GenerateRandomSymmetricHard54(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(54);
    }
  }
}

static void BM_GenerateRandomSymmetricHard60(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricHardWord(60);
    }
  }
}

BENCHMARK(BM_GenerateRandomSymmetricHard20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard24)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard34)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard44)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard54)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetricHard60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
