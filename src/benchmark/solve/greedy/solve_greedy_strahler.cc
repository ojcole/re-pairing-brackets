#include <benchmark/benchmark.h>

#include "generate/generate_next.h"
#include "generate/generate_random.h"
#include "solve/greedy/calculate_strahler.h"

static void BM_SolveStrahler10(benchmark::State &state) {
  generate::Generator generator(10);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::CalculateWordStrahler(dyck);
    }
  }
}

static void BM_SolveStrahler11(benchmark::State &state) {
  generate::Generator generator(11);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::CalculateWordStrahler(dyck);
    }
  }
}

static void BM_SolveStrahler12(benchmark::State &state) {
  generate::Generator generator(12);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::CalculateWordStrahler(dyck);
    }
  }
}

static void BM_SolveStrahler13(benchmark::State &state) {
  generate::Generator generator(13);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::CalculateWordStrahler(dyck);
    }
  }
}

static void BM_SolveStrahlerRandom200(benchmark::State &state) {
  auto word = generate::RandomUniformWord(200);
  for (auto _ : state) {
    solve::CalculateWordStrahler(word);
  }
}

static void BM_SolveStrahlerRandom400(benchmark::State &state) {
  auto word = generate::RandomUniformWord(400);
  for (auto _ : state) {
    solve::CalculateWordStrahler(word);
  }
}

BENCHMARK(BM_SolveStrahler10)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveStrahler11)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveStrahler12)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveStrahler13)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SolveStrahlerRandom200)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_SolveStrahlerRandom400)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
