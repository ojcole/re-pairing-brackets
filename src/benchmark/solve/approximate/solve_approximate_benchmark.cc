#include <benchmark/benchmark.h>

#include "generate/generate_all.h"
#include "solve/solve_approximate.h"

static void BM_SolveApproximate13(benchmark::State &state) {
  auto words = generate::GenerateDynamic(13);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::SolveApproximate(word);
    }
  }
}

BENCHMARK(BM_SolveApproximate13)->Unit(benchmark::kMillisecond)->Iterations(10);

BENCHMARK_MAIN();
