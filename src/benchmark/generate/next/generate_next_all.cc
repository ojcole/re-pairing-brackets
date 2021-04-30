#include <benchmark/benchmark.h>

#include "generate/generate_next.h"
static void BM_GenerateNextAll1(benchmark::State &state) {
  generate::Generator generator(1);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll2(benchmark::State &state) {
  generate::Generator generator(2);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll3(benchmark::State &state) {
  generate::Generator generator(3);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll4(benchmark::State &state) {
  generate::Generator generator(4);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll5(benchmark::State &state) {
  generate::Generator generator(5);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll6(benchmark::State &state) {
  generate::Generator generator(6);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll7(benchmark::State &state) {
  generate::Generator generator(7);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll8(benchmark::State &state) {
  generate::Generator generator(8);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll9(benchmark::State &state) {
  generate::Generator generator(9);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll10(benchmark::State &state) {
  generate::Generator generator(10);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll11(benchmark::State &state) {
  generate::Generator generator(11);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll12(benchmark::State &state) {
  generate::Generator generator(12);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll13(benchmark::State &state) {
  generate::Generator generator(13);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll14(benchmark::State &state) {
  generate::Generator generator(14);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll15(benchmark::State &state) {
  generate::Generator generator(15);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll16(benchmark::State &state) {
  generate::Generator generator(16);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll17(benchmark::State &state) {
  generate::Generator generator(17);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll18(benchmark::State &state) {
  generate::Generator generator(18);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll19(benchmark::State &state) {
  generate::Generator generator(19);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}
static void BM_GenerateNextAll20(benchmark::State &state) {
  generate::Generator generator(20);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
         num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
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
BENCHMARK(BM_GenerateNextAll12);
BENCHMARK(BM_GenerateNextAll13);
BENCHMARK(BM_GenerateNextAll14);
BENCHMARK(BM_GenerateNextAll15);
BENCHMARK(BM_GenerateNextAll16);
BENCHMARK(BM_GenerateNextAll17)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateNextAll18)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateNextAll19)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_GenerateNextAll20)->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
