#include <benchmark/benchmark.h>
#include "generate/generate_all.h"
static void BM_GenerateSwappingAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(1);
  }
}
static void BM_GenerateSwappingAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(2);
  }
}
static void BM_GenerateSwappingAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(3);
  }
}
static void BM_GenerateSwappingAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(4);
  }
}
static void BM_GenerateSwappingAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(5);
  }
}
static void BM_GenerateSwappingAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(6);
  }
}
static void BM_GenerateSwappingAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(7);
  }
}
static void BM_GenerateSwappingAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(8);
  }
}
static void BM_GenerateSwappingAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(9);
  }
}
static void BM_GenerateSwappingAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(10);
  }
}
static void BM_GenerateSwappingAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(11);
  }
}
static void BM_GenerateSwappingAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(12);
  }
}
static void BM_GenerateSwappingAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(13);
  }
}
static void BM_GenerateSwappingAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(14);
  }
}
static void BM_GenerateSwappingAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(15);
  }
}
static void BM_GenerateSwappingAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateSwapping(16);
  }
}
BENCHMARK(BM_GenerateSwappingAll1);
BENCHMARK(BM_GenerateSwappingAll2);
BENCHMARK(BM_GenerateSwappingAll3);
BENCHMARK(BM_GenerateSwappingAll4);
BENCHMARK(BM_GenerateSwappingAll5);
BENCHMARK(BM_GenerateSwappingAll6);
BENCHMARK(BM_GenerateSwappingAll7);
BENCHMARK(BM_GenerateSwappingAll8);
BENCHMARK(BM_GenerateSwappingAll9);
BENCHMARK(BM_GenerateSwappingAll10);
BENCHMARK(BM_GenerateSwappingAll11);
BENCHMARK(BM_GenerateSwappingAll12)->Iterations(50);
BENCHMARK(BM_GenerateSwappingAll13)->Iterations(50);
BENCHMARK(BM_GenerateSwappingAll14)->Iterations(50);
BENCHMARK(BM_GenerateSwappingAll15)->Iterations(50);
BENCHMARK(BM_GenerateSwappingAll16)->Iterations(50);
BENCHMARK_MAIN();
