#include "solve/exhaustive/solve_exhaustive.h"

#include <benchmark/benchmark.h>

#include <fstream>
#include <vector>

#include "generate/generate_random.h"
#include "solve/solve_approximate.h"

static void BM_SolveExhaustiveRandom50(benchmark::State &state) {
  std::ifstream stream("benchmark/solve/exhaustive/exhaustive_bench_set50.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 5000);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::ExhaustiveSolve(word);
    }
  }
}

static void BM_SolveExhaustiveRandom100(benchmark::State &state) {
  std::ifstream stream(
      "benchmark/solve/exhaustive/exhaustive_bench_set100.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 100);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::ExhaustiveSolve(word);
    }
  }
}

static void BM_SolveExhaustiveRandom200(benchmark::State &state) {
  std::ifstream stream(
      "benchmark/solve/exhaustive/exhaustive_bench_set200.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 15);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::ExhaustiveSolve(word);
    }
  }
}

BENCHMARK(BM_SolveExhaustiveRandom50)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandom100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandom200)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
