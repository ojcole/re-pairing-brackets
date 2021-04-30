#include <benchmark/benchmark.h>

#include "search/random_walk.h"

static void BM_RandomWalk182(benchmark::State &state) {
  std::string word =
      "((((())((((())(((((())))(())(((())))(((())))))((((())(((((())(())((()))("
      "(()))(())(((())))))(((((())))(())((()))((()))(())(())))))(()))))(((((())"
      "))(((())))(())(((())))))(()))))(()))))((((())((((())(((((())))(())(((())"
      "))(((())))))((((())(((((())(())((()))((()))(())(((())))))(((((())))(())("
      "(()))((()))(())(())))))(()))))(((((())))(((())))(())(((())))))(()))))(()"
      "))))";
  for (auto _ : state) {
    search::SymmetricHardRandomWalkShorterWord(word, 4, 40, 10000, 4);
  }
}

BENCHMARK(BM_RandomWalk182)
    ->Unit(benchmark::kMillisecond)
    ->MeasureProcessCPUTime();

BENCHMARK_MAIN();
