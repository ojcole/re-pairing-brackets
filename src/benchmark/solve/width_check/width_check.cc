#include "solve/predicate/width_check.h"

#include <benchmark/benchmark.h>

#include <fstream>
#include <vector>

static void BM_CheckWord50(benchmark::State &state) {
  std::ifstream stream(
      "benchmark/solve/width_check/exhaustive_bench_set50.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 5000);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::predicate::WordIsWidthAtLeastN(word, 3);
    }
  }
}

static void BM_CheckWord100(benchmark::State &state) {
  std::ifstream stream(
      "benchmark/solve/width_check/exhaustive_bench_set100.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 100);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::predicate::WordIsWidthAtLeastN(word, 3);
    }
  }
}

static void BM_CheckWord200(benchmark::State &state) {
  std::ifstream stream(
      "benchmark/solve/width_check/exhaustive_bench_set200.txt");

  std::vector<std::string> words;
  std::string line;

  while (std::getline(stream, line)) {
    words.push_back(line);
  }

  stream.close();
  words = std::vector<std::string>(words.begin(), words.begin() + 15);

  for (auto _ : state) {
    for (auto &word : words) {
      solve::predicate::WordIsWidthAtLeastN(word, 3);
    }
  }
}

BENCHMARK(BM_CheckWord50)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_CheckWord100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_CheckWord200)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
