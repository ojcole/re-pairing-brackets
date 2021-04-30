#include <benchmark/benchmark.h>

#include "generate/generate_next.h"

static void BM_Convert14(benchmark::State &state) {
  generate::Generator generator(14);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext(); num != generator.kErrorWord;
         num = generator.GenerateNext()) {
      generator.WordToDyck(num);
    }
  }
}

BENCHMARK(BM_Convert14);

BENCHMARK_MAIN();
