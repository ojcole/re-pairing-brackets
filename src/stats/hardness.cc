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

#include "hardness.h"

#include <string>
#include <unordered_map>
#include <utility>

#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/solution.h"
#include "solve/solve_approximate.h"

namespace stats {

bool operator<(const Hardness &h1, const Hardness &h2) {
  if (h1.width != h2.width) return h1.width < h2.width;

  // Less hardness is backwards so less hardness means harder
  return h1.hardness > h2.hardness;
}
bool operator>(const Hardness &h1, const Hardness &h2) { return h2 < h1; }

bool operator<=(const Hardness &h1, const Hardness &h2) { return !(h1 > h2); }

bool operator>=(const Hardness &h1, const Hardness &h2) { return !(h1 < h2); }

bool operator==(const Hardness &h1, const Hardness &h2) {
  return !(h1 > h2 || h1 < h2);
}

bool operator!=(const Hardness &h1, const Hardness &h2) { return !(h1 == h2); }

struct HardnessWorker {
  // The worker solution
  solve::Solution &sol;
  // The width of the word
  int width;
  // Current depth of the search
  int depth;
  // How many different paths are there from this point
  std::unordered_map<std::string, long> result_memo;
  // Keep track of the maximum width getting to this point that still permitted
  // a successful solve and the minimum width that did not
  std::unordered_map<std::string, std::pair<int, int>> width_memo;
};

// Test if, from a specific point, the word in the worker can reach a complete
// solution with width less than or equal to the width of the word
bool CanSolve(HardnessWorker &worker, int begin, int end) {
  auto &solution = worker.sol;

  // If the current width is greater it is clearly impossible
  if (solution.GetWidth() > worker.width) return false;

  const auto &word = solution.GetWord();
  int width = solution.GetWidth();
  int curr_width = solution.GetCurrentWidth();

  if (solution.IsComplete()) {
    return true;
  }

  auto it{worker.width_memo.find(word)};

  // If we have been here before and the width that we got here before using was
  // good enough to be saved then if our width is less than it then we can get
  // to the end with at least as good a width
  if (it != worker.width_memo.end()) {
    if (width <= it->second.first) return true;
    if (width >= it->second.second) return false;
  }

  while (word[begin] == STRING_GAP) begin++;

  const int kScoreOpts{5};

  // Calculate all the pairs and try all combinations that leave us under the
  // width. Order the moves by their difficulty defined by how much width they
  // contribute to prune the search space
  std::vector<std::pair<int, int>> scores[kScoreOpts];
  int depth{};
  std::vector<int> component_opening;
  int new_end{};

  for (int i{begin}; i <= end; i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
      component_opening.push_back(i);
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      for (auto x : component_opening) {
        int score = solve::RecalculateWidthRemoval(word, x, i);
        if (worker.width >= curr_width + score) {
          scores[score + 2].push_back({x, i});
        }
      }

      if (depth == 0) {
        new_end = i;
        component_opening.clear();
      }
    }
  }

  bool solvable = false;

  // Go through the words in the correct order checking at each stage if it can
  // be solved
  for (int i{}; i < kScoreOpts; i++) {
    for (auto &p : scores[i]) {
      solution.PairOffWithDiff(p.first, p.second, i - 2);
      auto solved = CanSolve(worker, begin, new_end);
      solution.Undo(curr_width, width);
      if (solved) {
        solvable = true;
        break;
      }
    }
    if (solvable) break;
  }

  // Update the memo with the newly found values for the current
  int default_min = 0;
  int default_max = worker.width + 1;

  if (it != worker.width_memo.end()) {
    default_min = it->second.first;
    default_max = it->second.second;
  }

  if (solvable) {
    worker.width_memo[word] = {width, default_max};
  } else {
    worker.width_memo[word] = {default_min, width};
  }

  return solvable;
}

// Generate possible moves and order by how much they affect width
long ComputeHardnessWorker(HardnessWorker &worker, int d, int begin, int end) {
  auto &solution = worker.sol;
  if (solution.GetWidth() > worker.width) return 0;

  const auto &word = solution.GetWord();
  int width = solution.GetWidth();

  auto it = worker.result_memo.find(word);

  // If we have already seen a node and we know there are n from this node, just
  // add that many
  if (it != worker.result_memo.end()) {
    return it->second;
  }

  long total{};

  while (word[begin] == STRING_GAP) begin++;

  // Calculate all possible moves before trying them all and recursing or
  // checking the result if we are at the significant length. We only need to
  // check moves that actually keep our width in a valid range
  std::vector<std::pair<int, int>> pairs;
  int depth{};
  std::vector<int> component_opening;
  int new_end{};

  int curr_width = solution.GetCurrentWidth();

  for (int i{begin}; i <= end; i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
      component_opening.push_back(i);
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      for (auto x : component_opening) {
        int score = solve::RecalculateWidthRemoval(word, x, i);
        if (worker.width >= curr_width + score) {
          pairs.push_back({x, i});
        }
      }

      if (depth == 0) {
        new_end = i;
        component_opening.clear();
      }
    }
  }

  if (d == worker.depth) {
    for (auto &p : pairs) {
      solution.PairOff(p.first, p.second);
      auto solved = CanSolve(worker, begin, new_end);
      solution.Undo(curr_width, width);
      if (solved) {
        return 1;
      }
    }

    return 0;
  } else {
    for (auto &p : pairs) {
      solution.PairOff(p.first, p.second);
      total += ComputeHardnessWorker(worker, d + 1, begin, new_end);
      solution.Undo(curr_width, width);
    }
  }

  worker.result_memo[word] = total;

  return total;
}

Hardness ComputeHardness(const std::string &word, int d) {
  auto solution = solve::ExhaustiveSolve(word);

  solve::Solution sol(word);
  HardnessWorker worker = {sol, solution.GetWidth(), d};

  auto result =
      ComputeHardnessWorker(worker, 0, 0, static_cast<int>(word.size()) - 1);

  return {word, solution.GetWidth(), result};
}

}  // namespace stats
