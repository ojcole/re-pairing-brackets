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

#include "width_check.h"

#include <cassert>
#include <map>
#include <unordered_map>
#include <vector>

#include "helpers/constants.h"
#include "helpers/verifiers.h"
#include "solve/solution.h"

namespace solve {
namespace predicate {

bool WordIsWidthAtLeastN(const std::string &word, int n) {
  bool exit{false};
  std::unordered_map<std::string, int> memo;
  return WordIsWidthAtLeastN(word, n, memo, exit);
}

bool SymmetricHardWordIsWidthAtLeastN(const std::string &word, int n) {
  bool exit{false};
  std::unordered_map<std::string, int> memo;
  return SymmetricHardWordIsWidthAtLeastN(word, n, memo, exit);
}

// Worker for searching through the search space
struct SolverWorker {
  // The current worker solution
  Solution &sol;
  // The current best width found
  int curr_best;
  // The memo to track widths reached from a particular length
  std::unordered_map<std::string, int> &memo;
  // Flag to short circuit execution
  bool &exit;
};

// Calculate the width change by removing the left and right characters using a
// half to test for edges contributing to width
template <bool half>
inline int CalculateWidthRemoval(const std::string &word, int left, int right) {
  int score = 2;

  // Before left is gap removes one
  if (left == 0 || word[left - 1] == STRING_GAP) {
    score--;
  }

  // Next to each other removes another width from the total
  if (left + 1 == right) {
    score--;
  } else {
    // Next is a gap removes another width in each case from the total
    if (word[left + 1] == STRING_GAP) {
      score--;
    }
    if (word[right - 1] == STRING_GAP) {
      score--;
    }
  }

  // If at the end and not half then subtract or if next is a gap
  if (right == static_cast<int>(word.size()) - 1) {
    if (!half) score--;
  } else if (word[right + 1] == STRING_GAP) {
    score--;
  }

  return score;
}

// Generate possible moves and order by how much they affect width
template <bool half>
void LimitedSolveSingle(SolverWorker &worker, int begin, int end) {
  // Check exit condition
  if (worker.exit) return;

  auto &solution = worker.sol;
  int width = solution.GetWidth();

  // If the current is at least the current best then it cannot improve so exit
  if (width >= worker.curr_best) return;

  // Record the best width as a negative number to propagate back to the top of
  // recursion as if we find a single one better than the width then it is not
  // at least n
  if (solution.IsComplete()) {
    worker.curr_best = -1;
    return;
  }

  const auto &word = solution.GetWord();

  // If we have a saved solution that is better than where we currently are,
  // don't continue
  auto it{worker.memo.find(word)};

  if (it != worker.memo.end() && it->second <= width) {
    return;
  }

  worker.memo[word] = width;

  // Prune extra space at the beginning
  while (word[begin] == STRING_GAP) begin++;

  int new_end{end};
  int depth{};

  int c_open{};
  bool active{true};
  std::map<int, std::vector<std::pair<int, int>>> components;
  int size{};
  bool full_active{false};

  // Calculate the components of the words by indices only storing active ones
  // to prune the search space
  for (int i{begin}; i <= end; i++) {
    if (word[i] == OPENING_BRACKET) {
      size++;
      if (depth == 0) {
        c_open = i;
      }
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      size++;
      if (depth == 0) {
        bool new_active = i == end || word[i + 1] == STRING_GAP;
        if (full_active || (active && new_active)) {
          components[size].push_back({c_open, i});
        } else if (active || new_active) {
          components[size + 1].push_back({c_open, i});
        }
        new_end = i;
        active = new_active;
        size = 0;
        full_active = false;
      }
    } else if (depth != 0) {
      full_active = true;
      active = true;
    }
  }

  const int kScoreOpts{5};
  std::vector<std::pair<int, int>> moves[kScoreOpts];

  int curr = solution.GetCurrentWidth();

  // Store the indices of possible valid moves and store them in order of how
  // much they contribute to width
  for (auto &p : components) {
    for (auto &c : p.second) {
      std::vector<int> opening;
      for (int i{c.first}; i <= c.second; i++) {
        if (word[i] == OPENING_BRACKET) {
          opening.push_back(i);
        } else if (word[i] == CLOSING_BRACKET) {
          for (auto &x : opening) {
            int score = CalculateWidthRemoval<half>(word, x, i);
            if (curr + score < worker.curr_best) {
              moves[score + 2].push_back({x, i});
            }
          }
        }
      }
    }
  }

  // Test all of the found valid moves
  for (int i{}; i < kScoreOpts; i++) {
    for (auto &p : moves[i]) {
      solution.PairOffWithDiff(p.first, p.second, i - 2);
      LimitedSolveSingle<half>(worker, begin, new_end);

      if (worker.exit) return;
      if (worker.curr_best <= 2) return;

      solution.Undo(curr, width);

      if (width >= worker.curr_best) return;
    }
  }
}

bool SymmetricHardWordIsWidthAtLeastN(
    const std::string &word, int n, std::unordered_map<std::string, int> &memo,
    bool &exit) {
  if (n <= 1) return true;
  assert(helper::VerifySymmetricHardWord(word));

  // If the first half with right side is of the correct width, because its hard
  // symmetric, we can conclude the entire word is the same width
  auto half_word = word.substr(0, word.size() / 2);

  Solution sol(half_word);
  SolverWorker worker{sol, n, memo, exit};
  LimitedSolveSingle<true>(worker, 0, static_cast<int>(half_word.size()) - 1);

  // If we find a better solution then its updated to -1
  return worker.curr_best != -1;
}

bool WordIsWidthAtLeastN(const std::string &word, int n,
                         std::unordered_map<std::string, int> &memo,
                         bool &exit) {
  if (n <= 1) return true;

  Solution sol(word);
  SolverWorker worker{sol, n, memo, exit};

  // If we find a better solution then its updated to -1
  LimitedSolveSingle<false>(worker, 0, static_cast<int>(word.size()) - 1);

  return worker.curr_best != -1;
}

}  // namespace predicate
}  // namespace solve
