#include <benchmark/benchmark.h>

#include "generate/generate_random.h"

const int kRuns{1000000};
const int kIterations{1};

static void BM_GenerateRandomUniform20(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(20);
    }
  }
}

static void BM_GenerateRandomUniform25(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(25);
    }
  }
}

static void BM_GenerateRandomUniform30(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(30);
    }
  }
}

static void BM_GenerateRandomUniform35(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(35);
    }
  }
}

static void BM_GenerateRandomUniform40(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(40);
    }
  }
}

static void BM_GenerateRandomUniform45(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(45);
    }
  }
}

static void BM_GenerateRandomUniform50(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(50);
    }
  }
}

static void BM_GenerateRandomUniform55(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(55);
    }
  }
}

static void BM_GenerateRandomUniform60(benchmark::State &state) {
  for (auto _ : state) {
    for (int i{}; i < kRuns; i++) {
      generate::RandomUniformWord(60);
    }
  }
}

BENCHMARK(BM_GenerateRandomUniform20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform25)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform35)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform45)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform55)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateRandomUniform60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
