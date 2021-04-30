#include <benchmark/benchmark.h>

#include <vector>

#include "generate/generate_random.h"
#include "solve/exhaustive/solve_exhaustive.h"

const int kRuns{100000};
const int kIterations{1};

static void BM_SolveExhaustiveRandomSymmetric20(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(20);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric25(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(25);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric30(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(30);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric35(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(35);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric40(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(40);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric45(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(45);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric50(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(50);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric55(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(55);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetric60(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricWord(60);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

BENCHMARK(BM_SolveExhaustiveRandomSymmetric20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric25)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric35)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric45)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric55)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetric60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
