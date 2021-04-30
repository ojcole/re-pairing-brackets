#include <benchmark/benchmark.h>
#include "generate/generate_all.h"
static void BM_GenerateMemoedAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(1);
  }
}
static void BM_GenerateMemoedAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(2);
  }
}
static void BM_GenerateMemoedAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(3);
  }
}
static void BM_GenerateMemoedAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(4);
  }
}
static void BM_GenerateMemoedAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(5);
  }
}
static void BM_GenerateMemoedAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(6);
  }
}
static void BM_GenerateMemoedAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(7);
  }
}
static void BM_GenerateMemoedAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(8);
  }
}
static void BM_GenerateMemoedAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(9);
  }
}
static void BM_GenerateMemoedAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(10);
  }
}
static void BM_GenerateMemoedAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(11);
  }
}
static void BM_GenerateMemoedAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(12);
  }
}
static void BM_GenerateMemoedAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(13);
  }
}
static void BM_GenerateMemoedAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(14);
  }
}
static void BM_GenerateMemoedAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(15);
  }
}
static void BM_GenerateMemoedAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed(16);
  }
}
BENCHMARK(BM_GenerateMemoedAll1);
BENCHMARK(BM_GenerateMemoedAll2);
BENCHMARK(BM_GenerateMemoedAll3);
BENCHMARK(BM_GenerateMemoedAll4);
BENCHMARK(BM_GenerateMemoedAll5);
BENCHMARK(BM_GenerateMemoedAll6);
BENCHMARK(BM_GenerateMemoedAll7);
BENCHMARK(BM_GenerateMemoedAll8);
BENCHMARK(BM_GenerateMemoedAll9);
BENCHMARK(BM_GenerateMemoedAll10);
BENCHMARK(BM_GenerateMemoedAll11);
BENCHMARK(BM_GenerateMemoedAll12)->Iterations(50);
BENCHMARK(BM_GenerateMemoedAll13)->Iterations(50);
BENCHMARK(BM_GenerateMemoedAll14)->Iterations(50);
BENCHMARK(BM_GenerateMemoedAll15)->Iterations(50);
BENCHMARK(BM_GenerateMemoedAll16)->Iterations(50);
BENCHMARK_MAIN();
