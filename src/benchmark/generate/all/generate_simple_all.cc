#include <benchmark/benchmark.h>
#include "generate/generate_all.h"
static void BM_GenerateSimpleAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(1);
  }
}
static void BM_GenerateSimpleAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(2);
  }
}
static void BM_GenerateSimpleAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(3);
  }
}
static void BM_GenerateSimpleAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(4);
  }
}
static void BM_GenerateSimpleAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(5);
  }
}
static void BM_GenerateSimpleAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(6);
  }
}
static void BM_GenerateSimpleAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(7);
  }
}
static void BM_GenerateSimpleAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(8);
  }
}
static void BM_GenerateSimpleAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(9);
  }
}
static void BM_GenerateSimpleAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(10);
  }
}
static void BM_GenerateSimpleAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(11);
  }
}
static void BM_GenerateSimpleAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(12);
  }
}
static void BM_GenerateSimpleAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(13);
  }
}
static void BM_GenerateSimpleAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(14);
  }
}
static void BM_GenerateSimpleAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(15);
  }
}
static void BM_GenerateSimpleAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSimple(16);
  }
}
BENCHMARK(BM_GenerateSimpleAll1);
BENCHMARK(BM_GenerateSimpleAll2);
BENCHMARK(BM_GenerateSimpleAll3);
BENCHMARK(BM_GenerateSimpleAll4);
BENCHMARK(BM_GenerateSimpleAll5);
BENCHMARK(BM_GenerateSimpleAll6);
BENCHMARK(BM_GenerateSimpleAll7);
BENCHMARK(BM_GenerateSimpleAll8);
BENCHMARK(BM_GenerateSimpleAll9);
BENCHMARK(BM_GenerateSimpleAll10);
BENCHMARK(BM_GenerateSimpleAll11);
BENCHMARK(BM_GenerateSimpleAll12)->Iterations(50);
BENCHMARK(BM_GenerateSimpleAll13)->Iterations(50);
BENCHMARK(BM_GenerateSimpleAll14)->Iterations(50);
BENCHMARK(BM_GenerateSimpleAll15)->Iterations(50);
BENCHMARK(BM_GenerateSimpleAll16)->Iterations(50);
BENCHMARK_MAIN();
