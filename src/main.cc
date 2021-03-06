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

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "generate/generate_all.h"
#include "generate/generate_next.h"
#include "generate/generate_random.h"
#include "generate/generate_random_hard.h"
#include "generate/generate_xyz.h"
#include "helpers/catalan.h"
#include "search/random_walk.h"
#include "search/segment_width_search.h"
#include "search/width_search.h"
#include "solve/chistikov/solve_chistikov.h"
#include "solve/derived/derived_strategy.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/greedy/calculate_strahler.h"
#include "solve/greedy/solve_greedy.h"
#include "solve/greedy/solve_simple_greedy.h"
#include "solve/minimise/minimise_width.h"
#include "solve/parallel/solve_parallel.h"
#include "solve/predicate/width_check.h"
#include "solve/repairings/all_repairings.h"
#include "stats/hardness.h"
#include "stats/random_sample_width.h"
#include "stats/results_output.h"

int main() {
  // Calculation of the average width found using the simple re-pairing strategy

  size_t total{};
  size_t count{};
  size_t iters{100000};
  size_t step{10000};
  size_t steps = iters / step;

  for (size_t i{}; i < steps; i++) {
    for (size_t j{}; j < step; j++) {
      auto word = generate::RandomHardWord(256);
      auto sol = solve::CalculateWordStrahler(word);

      total += static_cast<size_t>(sol);
      count++;
    }

    std::cout << static_cast<double>(i + 1) / steps * 100 << "%" << std::endl;
  }

  std::cout << static_cast<double>(total) / count << std::endl;
}
