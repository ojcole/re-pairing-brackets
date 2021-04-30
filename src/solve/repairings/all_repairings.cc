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

#include "all_repairings.h"

#include "helpers/constants.h"
#include "solve/exhaustive/solve_exhaustive.h"

namespace solve {
namespace repairings {

// Worker for searching for all re-pairings
struct ExhaustiveRepairingsWorker {
  // Current result of the progress
  RepairingsResult &result;
  // The current working solution
  Solution &sol;
  // The total number of re-pairings to include
  size_t max;
  // The significant length of re-pairings to include
  size_t significant;
};

RepairingsResult AllOptimalRepairings(const std::string &word, size_t max) {
  return AllOptimalRepairings(word, max, word.size() / 2);
}

void ExhaustiveSearch(ExhaustiveRepairingsWorker &worker, int begin, int end) {
  if (worker.result.repairings.size() >= worker.max) {
    return;
  }

  // If we have already looked at this re-pairing, check if it reached the end
  // and if so then just return
  if (worker.sol.GetRepairingVectorSize() / 2 >= worker.significant) {
    auto repairing = worker.sol.GetRepairing();
    repairing.resize(worker.significant);

    if (worker.result.repairings.find(repairing) !=
        worker.result.repairings.end()) {
      return;
    }
  }

  // If the current width is greater than the actual width then it cannot
  // successfully complete
  if (worker.sol.GetWidth() > worker.result.width) {
    return;
  }

  // If the solution is complete then store a copy of it in the set
  if (worker.sol.IsComplete()) {
    auto repairing = worker.sol.GetRepairing();

    repairing.resize(std::min(repairing.size(), worker.significant));
    worker.result.repairings.insert(std::move(repairing));

    return;
  }

  auto &solution = worker.sol;
  const auto &word = solution.GetWord();

  // Move endpoint
  while (word[begin] == STRING_GAP) begin++;
  while (word[end] == STRING_GAP) end--;

  int depth{};
  std::vector<int> component_opening;

  int curr_width = solution.GetCurrentWidth();
  int curr_max = worker.sol.GetWidth();

  // Generate all possible moves that don't exceed the width limit and test them
  for (int i{begin}; i <= end; i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
      component_opening.push_back(i);
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      for (auto &x : component_opening) {
        int score = RecalculateWidthRemoval(word, x, i);
        if (worker.result.width >= curr_width + score) {
          solution.PairOffWithDiff(x, i, score);
          ExhaustiveSearch(worker, begin, end);
          solution.Undo(curr_width, curr_max);
        }
      }

      if (depth == 0) {
        component_opening.clear();
      }
    }
  }
}

RepairingsResult AllOptimalRepairings(const std::string &word, size_t max,
                                      size_t significant) {
  // Get actual best to guide the search
  auto actual_solution = ExhaustiveSolve(word);

  RepairingsResult result;

  result.width = actual_solution.GetWidth();

  Solution sol(word);
  ExhaustiveRepairingsWorker worker = {result, sol, max, significant};

  ExhaustiveSearch(worker, 0, static_cast<int>(word.size()) - 1);

  return result;
}

}  // namespace repairings
}  // namespace solve
