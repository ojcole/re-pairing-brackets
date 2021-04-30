#include <benchmark/benchmark.h>
#include "generate/generate_all.h"
static void BM_GenerateNextAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(1);
  }
}
static void BM_GenerateNextAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(2);
  }
}
static void BM_GenerateNextAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(3);
  }
}
static void BM_GenerateNextAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(4);
  }
}
static void BM_GenerateNextAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(5);
  }
}
static void BM_GenerateNextAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(6);
  }
}
static void BM_GenerateNextAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(7);
  }
}
static void BM_GenerateNextAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(8);
  }
}
static void BM_GenerateNextAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(9);
  }
}
static void BM_GenerateNextAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(10);
  }
}
static void BM_GenerateNextAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(11);
  }
}
static void BM_GenerateNextAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(12);
  }
}
static void BM_GenerateNextAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(13);
  }
}
static void BM_GenerateNextAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(14);
  }
}
static void BM_GenerateNextAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(15);
  }
}
static void BM_GenerateNextAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateConstant(16);
  }
}
BENCHMARK(BM_GenerateNextAll1);
BENCHMARK(BM_GenerateNextAll2);
BENCHMARK(BM_GenerateNextAll3);
BENCHMARK(BM_GenerateNextAll4);
BENCHMARK(BM_GenerateNextAll5);
BENCHMARK(BM_GenerateNextAll6);
BENCHMARK(BM_GenerateNextAll7);
BENCHMARK(BM_GenerateNextAll8);
BENCHMARK(BM_GenerateNextAll9);
BENCHMARK(BM_GenerateNextAll10);
BENCHMARK(BM_GenerateNextAll11);
BENCHMARK(BM_GenerateNextAll12)->Iterations(50);
BENCHMARK(BM_GenerateNextAll13)->Iterations(50);
BENCHMARK(BM_GenerateNextAll14)->Iterations(50);
BENCHMARK(BM_GenerateNextAll15)->Iterations(50);
BENCHMARK(BM_GenerateNextAll16)->Iterations(50);
BENCHMARK_MAIN();
