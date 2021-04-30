#include <benchmark/benchmark.h>

#include "generate/generate_random.h"

const int kRuns{1000000};
const int kIterations{1};

static void BM_GenerateRandomSymmetric20(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(20);
    }
  }
}

static void BM_GenerateRandomSymmetric25(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(25);
    }
  }
}

static void BM_GenerateRandomSymmetric30(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(30);
    }
  }
}

static void BM_GenerateRandomSymmetric35(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(35);
    }
  }
}

static void BM_GenerateRandomSymmetric40(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(40);
    }
  }
}

static void BM_GenerateRandomSymmetric45(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(45);
    }
  }
}

static void BM_GenerateRandomSymmetric50(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(50);
    }
  }
}

static void BM_GenerateRandomSymmetric55(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(55);
    }
  }
}

static void BM_GenerateRandomSymmetric60(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomSymmetricWord(60);
    }
  }
}

BENCHMARK(BM_GenerateRandomSymmetric20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric25)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric35)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric45)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric55)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomSymmetric60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
