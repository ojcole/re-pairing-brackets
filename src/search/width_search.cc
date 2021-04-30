// MIT License

// Copyright (c) 2020-2021 Oliver Cole

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "width_search.h"

#include <memory>
#include <thread>
#include <vector>

#include "generate/generate_random.h"
#include "generate/generate_random_hard.h"
#include "helpers/parallel/compute_parallel.h"
#include "helpers/parallel/reducers.h"
#include "solve/derived/derived_strategy.h"
#include "solve/predicate/width_check.h"

namespace search {

struct Config {
  generate::RandomGenerator Generator;
  PredicateSolver Solver;
  int size;
  int iterations;
  int width;
  bool &complete;
};

using Result = std::string;

void WidthSearchWorker(std::shared_ptr<Config> config,
                       std::shared_ptr<Result> result, int workers, int index) {
  for (int i{}; i < config->iterations; i++) {
    if (config->complete) return;

    auto word = config->Generator(config->size);
    auto approx = solve::derived::Solve(word);

    if (approx.GetWidth() < config->width) continue;

    bool res{true};

    for (int i{3}; i <= config->width; i++) {
      std::unordered_map<std::string, int> memo;

      res = res && config->Solver(word, i, memo, config->complete);

      if (!res) break;
    }

    if (res && !config->complete) {
      config->complete = true;
      *result = word;
      break;
    }
  }
}

std::string HardSymmetricWidthSearch(int width, int size, int iterations,
                                     int workers) {
  return WidthSearch(width, generate::RandomSymmetricHardWord, size, iterations,
                     workers,
                     solve::predicate::SymmetricHardWordIsWidthAtLeastN);
}

std::string WidthSearch(int width, generate::RandomGenerator Generator,
                        int size, int iterations, int workers) {
  return WidthSearch(width, Generator, size, iterations, workers,
                     solve::predicate::WordIsWidthAtLeastN);
}

std::string WidthSearch(int width, generate::RandomGenerator Generator,
                        int size, int iterations, int workers,
                        PredicateSolver Solver) {
  bool complete = false;
  int leftover{iterations % workers};

  auto config_gen = [&complete, width, size, iterations, Generator, Solver,
                     workers, &leftover](int i) -> Config {
    int work = iterations / workers;

    if (leftover > 0) {
      work++;
      leftover--;
    }

    return {Generator, Solver, size, work, width, complete};
  };

  return helper::parallel::GenericParallelRunner<Result, Config>(
      WidthSearchWorker, config_gen,
      helper::parallel::FirstNonEmpty<std::string>, workers);
}

}  // namespace search
