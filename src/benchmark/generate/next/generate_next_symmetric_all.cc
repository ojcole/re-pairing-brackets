#include <benchmark/benchmark.h>
#include "generate/generate_next_symmetric.h"
static void BM_GenerateNextSymmetricAll2(benchmark::State &state) {
  generate::SymmetricGenerator generator(2);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll4(benchmark::State &state) {
  generate::SymmetricGenerator generator(4);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll6(benchmark::State &state) {
  generate::SymmetricGenerator generator(6);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll8(benchmark::State &state) {
  generate::SymmetricGenerator generator(8);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll10(benchmark::State &state) {
  generate::SymmetricGenerator generator(10);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll12(benchmark::State &state) {
  generate::SymmetricGenerator generator(12);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll14(benchmark::State &state) {
  generate::SymmetricGenerator generator(14);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll16(benchmark::State &state) {
  generate::SymmetricGenerator generator(16);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll18(benchmark::State &state) {
  generate::SymmetricGenerator generator(18);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll20(benchmark::State &state) {
  generate::SymmetricGenerator generator(20);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll22(benchmark::State &state) {
  generate::SymmetricGenerator generator(22);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll24(benchmark::State &state) {
  generate::SymmetricGenerator generator(24);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll26(benchmark::State &state) {
  generate::SymmetricGenerator generator(26);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll28(benchmark::State &state) {
  generate::SymmetricGenerator generator(28);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextSymmetricAll30(benchmark::State &state) {
  generate::SymmetricGenerator generator(30);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
BENCHMARK(BM_GenerateNextSymmetricAll2);
BENCHMARK(BM_GenerateNextSymmetricAll4);
BENCHMARK(BM_GenerateNextSymmetricAll6);
BENCHMARK(BM_GenerateNextSymmetricAll8);
BENCHMARK(BM_GenerateNextSymmetricAll10);
BENCHMARK(BM_GenerateNextSymmetricAll12);
BENCHMARK(BM_GenerateNextSymmetricAll14);
BENCHMARK(BM_GenerateNextSymmetricAll16);
BENCHMARK(BM_GenerateNextSymmetricAll18);
BENCHMARK(BM_GenerateNextSymmetricAll20);
BENCHMARK(BM_GenerateNextSymmetricAll22);
BENCHMARK(BM_GenerateNextSymmetricAll24);
BENCHMARK(BM_GenerateNextSymmetricAll26);
BENCHMARK(BM_GenerateNextSymmetricAll28);
BENCHMARK(BM_GenerateNextSymmetricAll30);
BENCHMARK_MAIN();
