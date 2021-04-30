#include <benchmark/benchmark.h>

#include "solve/parallel/solve_parallel.h"

static void BM_Solve14Multi8(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 8);
  }
}

static void BM_Solve14Multi7(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 7);
  }
}

static void BM_Solve14Multi6(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 6);
  }
}

static void BM_Solve14Multi5(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 5);
  }
}

static void BM_Solve14Multi4(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 4);
  }
}

static void BM_Solve14Multi2(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 2);
  }
}

static void BM_Solve14Multi1(benchmark::State& state) {
  for (auto _ : state) {
    solve::parallel::SolveMinimal(14, 1);
  }
}

BENCHMARK(BM_Solve14Multi8);
BENCHMARK(BM_Solve14Multi7);
BENCHMARK(BM_Solve14Multi6);
BENCHMARK(BM_Solve14Multi5);
BENCHMARK(BM_Solve14Multi4);
BENCHMARK(BM_Solve14Multi2);
BENCHMARK(BM_Solve14Multi1);

BENCHMARK_MAIN();
