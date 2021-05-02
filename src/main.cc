
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
