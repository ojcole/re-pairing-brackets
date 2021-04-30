#include <benchmark/benchmark.h>

#include <vector>

#include "generate/generate_random.h"
#include "solve/exhaustive/solve_exhaustive.h"

const int kRuns{100000};
const int kIterations{1};

static void BM_SolveExhaustiveRandomUniform20(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(20);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform25(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(25);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform30(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(30);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform35(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(35);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform40(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(40);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform45(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(45);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform50(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(50);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform55(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(55);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

static void BM_SolveExhaustiveRandomUniform60(benchmark::State &state) {
  std::vector<std::string> words;

  words.resize(kRuns);

  for (int i{}; i < kRuns; i++) {
    words[i] = generate::RandomUniformWord(60);
  }

  for (auto _ : state) {
    for (auto &w : words) {
      auto sol = solve::Solution::BadSolution(w);
      solve::ExhaustiveSolve(sol);
    }
  }
}

BENCHMARK(BM_SolveExhaustiveRandomUniform20)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform25)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform30)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform35)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform40)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform45)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform50)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform55)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SolveExhaustiveRandomUniform60)
    ->Iterations(kIterations)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
