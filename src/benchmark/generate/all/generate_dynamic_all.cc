#include <benchmark/benchmark.h>
#include "generate/generate_all.h"
static void BM_GenerateDynamicAll1(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(1);
  }
}
static void BM_GenerateDynamicAll2(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(2);
  }
}
static void BM_GenerateDynamicAll3(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(3);
  }
}
static void BM_GenerateDynamicAll4(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(4);
  }
}
static void BM_GenerateDynamicAll5(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(5);
  }
}
static void BM_GenerateDynamicAll6(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(6);
  }
}
static void BM_GenerateDynamicAll7(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(7);
  }
}
static void BM_GenerateDynamicAll8(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(8);
  }
}
static void BM_GenerateDynamicAll9(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(9);
  }
}
static void BM_GenerateDynamicAll10(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(10);
  }
}
static void BM_GenerateDynamicAll11(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(11);
  }
}
static void BM_GenerateDynamicAll12(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(12);
  }
}
static void BM_GenerateDynamicAll13(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(13);
  }
}
static void BM_GenerateDynamicAll14(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(14);
  }
}
static void BM_GenerateDynamicAll15(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(15);
  }
}
static void BM_GenerateDynamicAll16(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic(16);
  }
}
BENCHMARK(BM_GenerateDynamicAll1);
BENCHMARK(BM_GenerateDynamicAll2);
BENCHMARK(BM_GenerateDynamicAll3);
BENCHMARK(BM_GenerateDynamicAll4);
BENCHMARK(BM_GenerateDynamicAll5);
BENCHMARK(BM_GenerateDynamicAll6);
BENCHMARK(BM_GenerateDynamicAll7);
BENCHMARK(BM_GenerateDynamicAll8);
BENCHMARK(BM_GenerateDynamicAll9);
BENCHMARK(BM_GenerateDynamicAll10);
BENCHMARK(BM_GenerateDynamicAll11);
BENCHMARK(BM_GenerateDynamicAll12)->Iterations(50);
BENCHMARK(BM_GenerateDynamicAll13)->Iterations(50);
BENCHMARK(BM_GenerateDynamicAll14)->Iterations(50);
BENCHMARK(BM_GenerateDynamicAll15)->Iterations(50);
BENCHMARK(BM_GenerateDynamicAll16);
BENCHMARK_MAIN();
