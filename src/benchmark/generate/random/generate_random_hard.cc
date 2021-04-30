#include "generate/generate_random_hard.h"

#include <benchmark/benchmark.h>

const int kRuns{100000};
const int kIterations{1};

static void BM_GenerateRandomHard20(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(20);
    }
  }
}

static void BM_GenerateRandomHard24(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(24);
    }
  }
}

static void BM_GenerateRandomHard30(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(30);
    }
  }
}

static void BM_GenerateRandomHard34(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(34);
    }
  }
}

static void BM_GenerateRandomHard40(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(40);
    }
  }
}

static void BM_GenerateRandomHard44(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(44);
    }
  }
}

static void BM_GenerateRandomHard50(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(50);
    }
  }
}

static void BM_GenerateRandomHard54(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(54);
    }
  }
}

static void BM_GenerateRandomHard60(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomHardWord(60);
    }
  }
}

BENCHMARK(BM_GenerateRandomHard20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard24)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard34)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard44)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard54)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomHard60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
