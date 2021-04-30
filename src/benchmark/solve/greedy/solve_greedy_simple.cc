#include <benchmark/benchmark.h>

#include "generate/generate_next.h"
#include "generate/generate_random.h"
#include "solve/greedy/solve_simple_greedy.h"

static void BM_SolveSimplyGreedy10(benchmark::State &state) {
  generate::Generator generator(10);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::SolveSimpleGreedy(dyck);
    }
  }
}

static void BM_SolveSimplyGreedy11(benchmark::State &state) {
  generate::Generator generator(11);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::SolveSimpleGreedy(dyck);
    }
  }
}

static void BM_SolveSimplyGreedy12(benchmark::State &state) {
  generate::Generator generator(12);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::SolveSimpleGreedy(dyck);
    }
  }
}

static void BM_SolveSimplyGreedy13(benchmark::State &state) {
  generate::Generator generator(13);
  for (auto _ : state) {
    for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
         word = generator.GenerateNext()) {
      std::string dyck = generator.WordToDyck(word);

      solve::SolveSimpleGreedy(dyck);
    }
  }
}

static void BM_SolveSimplyGreedyRandom200(benchmark::State &state) {
  auto word = generate::RandomUniformWord(200);
  for (auto _ : state) {
    solve::SolveSimpleGreedy(word);
  }
}

static void BM_SolveSimplyGreedyRandom400(benchmark::State &state) {
  auto word = generate::RandomUniformWord(400);
  for (auto _ : state) {
    solve::SolveSimpleGreedy(word);
  }
}

BENCHMARK(BM_SolveSimplyGreedy10)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveSimplyGreedy11)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveSimplyGreedy12)->Unit(benchmark::kNanosecond);
BENCHMARK(BM_SolveSimplyGreedy13)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SolveSimplyGreedyRandom200)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_SolveSimplyGreedyRandom400)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
