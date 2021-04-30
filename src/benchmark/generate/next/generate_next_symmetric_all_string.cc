#include <benchmark/benchmark.h>

#include "generate/generate_all.h"
static void BM_GenerateNextSymmetricAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(1);
  }
}
static void BM_GenerateNextSymmetricAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(2);
  }
}
static void BM_GenerateNextSymmetricAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(3);
  }
}
static void BM_GenerateNextSymmetricAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(4);
  }
}
static void BM_GenerateNextSymmetricAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(5);
  }
}
static void BM_GenerateNextSymmetricAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(6);
  }
}
static void BM_GenerateNextSymmetricAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(7);
  }
}
static void BM_GenerateNextSymmetricAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(8);
  }
}
static void BM_GenerateNextSymmetricAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(9);
  }
}
static void BM_GenerateNextSymmetricAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(10);
  }
}
static void BM_GenerateNextSymmetricAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(11);
  }
}
static void BM_GenerateNextSymmetricAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(12);
  }
}
static void BM_GenerateNextSymmetricAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(13);
  }
}
static void BM_GenerateNextSymmetricAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(14);
  }
}
static void BM_GenerateNextSymmetricAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(15);
  }
}
static void BM_GenerateNextSymmetricAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSymmetric(16);
  }
}
BENCHMARK(BM_GenerateNextSymmetricAll1);
BENCHMARK(BM_GenerateNextSymmetricAll2);
BENCHMARK(BM_GenerateNextSymmetricAll3);
BENCHMARK(BM_GenerateNextSymmetricAll4);
BENCHMARK(BM_GenerateNextSymmetricAll5);
BENCHMARK(BM_GenerateNextSymmetricAll6);
BENCHMARK(BM_GenerateNextSymmetricAll7);
BENCHMARK(BM_GenerateNextSymmetricAll8);
BENCHMARK(BM_GenerateNextSymmetricAll9);
BENCHMARK(BM_GenerateNextSymmetricAll10);
BENCHMARK(BM_GenerateNextSymmetricAll11);
BENCHMARK(BM_GenerateNextSymmetricAll12);
BENCHMARK(BM_GenerateNextSymmetricAll13);
BENCHMARK(BM_GenerateNextSymmetricAll14);
BENCHMARK(BM_GenerateNextSymmetricAll15);
BENCHMARK(BM_GenerateNextSymmetricAll16);
BENCHMARK_MAIN();
