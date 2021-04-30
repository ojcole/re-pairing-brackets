#include <benchmark/benchmark.h>

#include "generate/generate_random_hard.h"
#include "search/width_search.h"

static void BM_WidthSearch20(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 20, 1000, 1);
  }
}

static void BM_WidthSearch40(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 40, 1000, 1);
  }
}

static void BM_WidthSearch60(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 60, 1000, 1);
  }
}

static void BM_WidthSearch80(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 80, 1000, 1);
  }
}

static void BM_WidthSearch100(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 100, 1000, 1);
  }
}

static void BM_WidthSearch150(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 150, 1000, 1);
  }
}

static void BM_WidthSearch200(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 200, 1000, 1);
  }
}

static void BM_WidthSearch250(benchmark::State &state) {
  for (auto _ : state) {
    search::WidthSearch(3, generate::RandomSymmetricHardWord, 250, 1000, 1);
  }
}

BENCHMARK(BM_WidthSearch20)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch40)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch60)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch80)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch150)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch200)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_WidthSearch250)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
