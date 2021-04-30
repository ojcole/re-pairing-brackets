#include <benchmark/benchmark.h>

#include <vector>

#include "generate/generate_random_hard.h"
#include "solve/exhaustive/solve_exhaustive.h"

const int kRuns{100000};
const int kIterations{1};

static void BM_SolveExhaustiveRandomHard20(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(20);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard24(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(24);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard30(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(30);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard34(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(34);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard40(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(40);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard44(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(44);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard50(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(50);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard54(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(54);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

static void BM_SolveExhaustiveRandomHard60(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomHardWord(60);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      solve::ExhaustiveSolve(w);
    }
  }
}

BENCHMARK(BM_SolveExhaustiveRandomHard20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard24)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard34)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard44)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard54)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomHard60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
