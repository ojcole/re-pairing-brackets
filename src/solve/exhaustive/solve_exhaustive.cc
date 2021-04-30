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

#include "solve_exhaustive.h"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "helpers/constants.h"
#include "solve/greedy/solve_simple_greedy.h"
#include "solve/solve_approximate.h"

namespace solve {

// Memo for partially solved words and the best widths
using Memo = std::unordered_map<std::string, int>;

// The config stored in the solver
struct SolverWorker {
  // The current working solution
  Solution &sol;
  // The width of the best solution found so far
  int curr_best;
  // The best solution found so far
  Solution best_solution;
  // The memo of results
  Memo memo;
};

// Generate possible moves and order by how much they affect width
// ShouldCheck is a test for if the memo should be checked for a value
// ShouldSave is a test for if the current width should be saved in the memo
template <bool (*ShouldCheck)(const SolverWorker &),
          bool (*ShouldSave)(const SolverWorker &)>
inline void ExhaustiveSolveSingle(SolverWorker &worker, int begin, int end) {
  auto &solution = worker.sol;

  // If the current working solution is worse than the currently found best one,
  // then continuing won't improve the current
  int width = solution.GetWidth();

  if (width >= worker.curr_best) return;

  const auto &word = solution.GetWord();

  if (solution.IsComplete()) {
    if (width < worker.curr_best) {
      worker.best_solution = solution;
      worker.curr_best = width;
    }

    return;
  }

  if (ShouldCheck(worker)) {
    auto it{worker.memo.find(word)};

    // If we have already reached this state, as it is a backtracking search,
    // the value of width did not permit a solution better than we currently
    // have so we don't need to continue searching
    if (it != worker.memo.end()) {
      if (it->second <= width) return;

      worker.memo[word] = width;
    } else if (ShouldSave(worker)) {
      worker.memo[word] = width;
    }
  }

  // Go to the first non space char
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
            int score = RecalculateWidthRemoval(word, x, i);
            if (curr + score < worker.curr_best) {
              moves[score + 2].push_back({x, i});
            }
          }
        }
      }
    }
  }

  // Iterate through all of the moves in order of increasing difficulty, short
  // circuiting if a better solution is found
  for (int i{}; i < kScoreOpts; i++) {
    if (worker.curr_best > curr - 2 + i) {
      for (auto &p : moves[i]) {
        solution.PairOffWithDiff(p.first, p.second, i - 2);
        ExhaustiveSolveSingle<ShouldCheck, ShouldSave>(worker, begin, new_end);

        if (worker.curr_best <= 2) return;

        solution.Undo(curr, width);

        if (width >= worker.curr_best) return;
      }
    }
  }
}

// Always returns true
inline bool TruthyCheck(const SolverWorker &_) { return true; }

// Returns true if the size of the memo is not too large and store with period
// half
inline bool HardLimit(const SolverWorker &worker) {
  return (worker.sol.GetRepairingVectorSize() / 2) % 2 == 0 &&
         worker.memo.size() < 200000;
}

// Returns true based on a period and the depth of the search
inline bool PeriodLimit(const SolverWorker &worker) {
  const size_t d_limit{70};

  size_t r_depth{(worker.sol.GetRepairingVectorSize() >> 1)};

  return (r_depth <= d_limit && r_depth % 5 != 0) ||
         (r_depth > d_limit && (r_depth % 2) == 1);
}

// Generic solver which checks a solution then runs the worker
template <bool (*ShouldCheck)(const SolverWorker &),
          bool (*ShouldSave)(const SolverWorker &)>
inline Solution GenericSolutionSolver(const Solution &solution) {
  if (solution.GetWidth() < 3) return solution;

  const auto &word = solution.GetInitialWord();
  Solution sol(word);
  SolverWorker worker{sol, solution.GetWidth(), solution};

  ExhaustiveSolveSingle<ShouldCheck, ShouldSave>(
      worker, 0, static_cast<int>(word.size()) - 1);

  return worker.best_solution;
}

Solution ExhaustiveSolve(const std::string &word) {
  auto solution = solve::SolveSimpleGreedy(word);

  return ExhaustiveSolve(solution);
}

Solution ExhaustiveSolve(const Solution &solution) {
  return GenericSolutionSolver<TruthyCheck, TruthyCheck>(solution);
}

Solution ExhaustiveSolveLimitedMemo(const std::string &word) {
  auto solution = solve::SolveSimpleGreedy(word);

  return ExhaustiveSolveLimitedMemo(solution);
}

Solution ExhaustiveSolveLimitedMemo(const Solution &solution) {
  return GenericSolutionSolver<TruthyCheck, HardLimit>(solution);
}

Solution ExhaustiveSolvePeriodMemo(const std::string &word) {
  auto solution = solve::SolveSimpleGreedy(word);

  return ExhaustiveSolvePeriodMemo(solution);
}

Solution ExhaustiveSolvePeriodMemo(const Solution &solution) {
  return GenericSolutionSolver<PeriodLimit, TruthyCheck>(solution);
}

}  // namespace solve
