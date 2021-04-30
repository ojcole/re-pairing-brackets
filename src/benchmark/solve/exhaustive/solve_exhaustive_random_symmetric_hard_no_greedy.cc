#include <benchmark/benchmark.h>

#include <vector>

#include "generate/generate_random_hard.h"
#include "solve/exhaustive/solve_exhaustive.h"

const int kRuns{100000};
const int kIterations{1};

static void BM_SolveExhaustiveRandomSymmetricHard20(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(20);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard24(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(24);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard30(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(30);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard34(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(34);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard40(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(40);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard44(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(44);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard50(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(50);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard54(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(54);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomSymmetricHard60(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomSymmetricHardWord(60);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard24)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard34)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard44)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard54)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomSymmetricHard60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
