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

#include "derived_strategy.h"

#include <algorithm>
#include <deque>
#include <string>
#include <utility>

#include "free_moves.h"
#include "helpers/constants.h"
#include "helpers/solutions/combine_solutions.h"
#include "helpers/traversal.h"
#include "obvious_moves.h"
#include "solve/greedy/greedy.h"

namespace solve {
namespace derived {

// Interface for choosing pairs
using PairChooser = std::pair<int, int> (*)(const std::string &);

// Make all obvious moves in the correct order
inline void MakeObviousMoves(Solution &solution) {
  MakeObviousMovesForward(solution);
  MakeObviousMovesBackward(solution);
  MakeObviousBlockMoves(solution);
}

// Tests if a word consists of a single contiguous block of brackets e.g. words
// of the form:
// _*(())*_*
inline bool SingleBlock(const std::string &word) {
  bool reached_block{false};
  bool after_block{false};

  for (auto &ch : word) {
    if (ch != STRING_GAP) {
      if (after_block) return false;

      reached_block = true;
    } else {
      if (reached_block) after_block = true;
    }
  }

  return true;
}

// Tests of a word consists of a single component or whether there are multiple
// components
inline bool SingleComponent(const std::string &word) {
  size_t i{};
  int depth{};

  for (; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      if (depth == 1) {
        break;
      }
      depth--;
    }
  }

  return helper::NextChar(word, i) == word.size();
}

// Calculate the depths of characters increased by one for multiple surrounding
// brackets. For example: ((())) correlates to 111111 (()()) correlates to
// 122221
inline std::vector<int> ShrunkDepths(const std::string &word) {
  int depth{};
  std::vector<int> result;
  result.resize(word.size());

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      auto prev = helper::PrevChar(word, i);
      auto c_closing = helper::ClosingBracket(word, i);
      // If its the first opening bracket we increase depth
      if (prev < 0) {
        if (c_closing != word.size() - 1) {
          depth++;
        }
      } else if (word[prev] == CLOSING_BRACKET) {
        // If the previous was a closing and this was an opening, then the depth
        // is simply the same as the previous
        depth = result[prev];
      } else {
        // If the closing bracket of the previous opening bracket directly
        // surrounds our current position then we do not increase depth e.g.,
        // (()) moving to the inner does not increase depth
        auto prev_closing = helper::ClosingBracket(word, prev);
        auto c_closing_next = helper::NextChar(word, c_closing);
        if (prev_closing != c_closing_next) {
          depth++;
        }
      }

      // We can set the closing and opening as they must be the same for all
      result[i] = depth;
      result[c_closing] = depth;
    } else if (word[i] == CLOSING_BRACKET) {
      // The depth of the closing will be set so we update to move down in depth
      depth = result[i];
    } else if (word[i] == STRING_GAP) {
      // For spaces, depth is considered the same
      result[i] = depth;
    }
  }

  return result;
}

// We choose the location which is at maximum depth at the left most location
inline std::pair<int, int> ChooseLeftMostDeepest(const std::string &word) {
  int depth{-1};
  std::pair<int, int> result{-1, -1};
  auto &&depths = ShrunkDepths(word);

  for (size_t i{}; i < word.size(); i++) {
    // > will find the first occurrence
    if (word[i] == OPENING_BRACKET && depths[i] > depth &&
        word[i + 1] == CLOSING_BRACKET) {
      depth = std::move(depths[i]);
      result = {i, i + 1};
    }
  }

  return result;
}

// We choose the location which is at maximum depth at the right most location
inline std::pair<int, int> ChooseRightMostDeepest(const std::string &word) {
  int depth{-1};
  std::pair<int, int> result{-1, -1};
  auto &&depths = ShrunkDepths(word);

  for (size_t i{}; i < word.size(); i++) {
    // >= will find the last occurrence
    if (word[i] == OPENING_BRACKET && depths[i] >= depth &&
        word[i + 1] == CLOSING_BRACKET) {
      depth = std::move(depths[i]);
      result = {i, i + 1};
    }
  }

  return result;
}

// Choose a rightmost left leaning currency pair to remove based on the currency
// rules
inline std::pair<int, int> ChooseLeftCurrency(const std::string &word) {
  std::pair<int, int> result{-1, -1};

  // Choose the last closing bracket that is not on the outside of the word
  // which has a space directly following it
  for (size_t i{}; i + 1 < word.size(); i++) {
    if (word[i] == CLOSING_BRACKET && word[i + 1] == STRING_GAP) {
      result.second = i;
    }
  }

  // If no such can be found, fail
  if (result.second == -1) {
    return result;
  }

  // Choose the last opening bracket that is to the left of the closing bracket
  // which has a space before it allowing for the use of the first character
  for (int i{}; i < result.second; i++) {
    if (word[i] == OPENING_BRACKET && (i == 0 || word[i - 1] == STRING_GAP)) {
      result.first = i;
    }
  }

  return result;
}

// Choose a leftmost right leaning currency pair to remove based on the currency
// rules
inline std::pair<int, int> ChooseRightCurrency(const std::string &word) {
  std::pair<int, int> result{-1, -1};

  // Find the first opening bracket not at the start of the word which has a
  // space before it
  for (size_t i{1}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET && word[i - 1] == STRING_GAP) {
      result.first = i;
      break;
    }
  }

  // If none found, return
  if (result.first == -1) {
    return result;
  }

  // Find the first closing bracket after the opening bracket which has a space
  // after it
  int word_size = static_cast<int>(word.size());
  for (int i{result.first}; i < word_size; i++) {
    if (word[i] == CLOSING_BRACKET &&
        (i == word_size - 1 || word[i + 1] == STRING_GAP)) {
      result.second = i;
      break;
    }
  }

  return result;
}

// Get blocks of components. The result is a list of pairs correpsonding to
// isolated groups of components with spaces on either side which are joined at
// depth 0
inline std::vector<std::pair<int, int>> GetGroupedComponents(
    const std::string &word) {
  std::vector<std::pair<int, int>> result;

  int start{-1};
  bool in_group{false};
  int depth{};

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      if (depth == 0 && !in_group) {
        start = depth;
        in_group = true;
      }

      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      // Ensure there is a space before pushing
      if (depth == 1 && (i + 1 == word.size() || word[i + 1] == STRING_GAP)) {
        result.push_back({start, i});
        in_group = false;
      }

      depth--;
    }
  }

  return result;
}

// Get the indexes of the ranges of the different components of the word.
// Components are subwords which start and end at depth 0 in the original word
inline std::vector<std::pair<int, int>> GetComponents(const std::string &word) {
  std::vector<std::pair<int, int>> result;
  int comp_start{};
  int depth{};

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      if (depth == 0) {
        comp_start = i;
      }

      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      if (depth == 1) {
        result.push_back({comp_start, i});
      }

      depth--;
    }
  }

  return result;
}

// Attempt to find a solution using the width one strategy which, if one exists,
// will always find a re-pairing of width 1
inline Solution WidthOneStrategy(const std::string &word) {
  Solution solution(word);

  MakeObviousMoves(solution);

  const auto &w = solution.GetWord();

  size_t last_opening = 0;
  size_t last_closing = solution.GetWord().size() - 1;

  // Repeatedly remove an outer pair then make all obvious moves. If at any
  // point there are multiple components after making all obvious moves then the
  // word cannot be re-paired using width 1
  while (!solution.IsComplete() && SingleComponent(solution.GetWord())) {
    const auto &word = solution.GetWord();
    int opening{-1};
    int closing{-1};

    // Find outer pair
    for (; last_opening < word.size(); last_opening++) {
      if (word[last_opening] == OPENING_BRACKET) {
        opening = last_opening;
        break;
      }
    }

    for (; last_closing > 0; last_closing--) {
      if (word[last_closing] == CLOSING_BRACKET) {
        closing = last_closing;
        break;
      }
    }

    // Pair off outer and make obvious moves
    solution.PairOff(opening, closing);
    MakeObviousMoves(solution);
  }

  return solution;
}

// General approach to re-pairing a single component which has a pair chooser
// and currency chooser to use when performing the algorithm.
inline Solution SingleComponentStrategyGeneral(const std::string &word,
                                               PairChooser PairChoosing,
                                               PairChooser CurrencyChoosing) {
  // Re-pairing with width 1 is optimal
  auto sol = WidthOneStrategy(word);
  if (sol.IsComplete()) return sol;

  Solution solution(word);

  // Repeat the following process:
  // - Make any free moves
  // - If the word is no longer a single component recurse to multiple
  // components
  // - If the word is still a single then remove a currency if possible
  // - If no currency can be removed pair off the deepest most pair
  while (!solution.IsComplete()) {
    MakeFreeMoves(solution);

    if (!SingleComponent(solution.GetWord())) {
      auto multi_sol = MultiComponentStrategy(solution.GetWord());
      solution.PairOffSolution(multi_sol);

      break;
    }

    auto currency = CurrencyChoosing(solution.GetWord());
    if (currency.first != currency.second) {
      solution.PairOff(currency.first, currency.second);
    } else {
      auto deepest_most = PairChoosing(solution.GetWord());
      solution.PairOff(deepest_most.first, deepest_most.second);
    }
  }

  return solution;
}

// Helper for repairing a single component which appears on the left side of a
// block
inline Solution SingleComponentStrategyLeft(const std::string &word) {
  return SingleComponentStrategyGeneral(word, ChooseRightMostDeepest,
                                        ChooseLeftCurrency);
}

// Helper for repairing a single component which appears on the right side of a
// block
inline Solution SingleComponentStrategyRight(const std::string &word) {
  return SingleComponentStrategyGeneral(word, ChooseLeftMostDeepest,
                                        ChooseRightCurrency);
}

// Algorithm for where there are multiple blocks of multiple components
inline Solution MultiComponentStrategyMultiGroups(
    const std::string &word, const std::vector<std::pair<int, int>> &groups) {
  Solution solution(word);

  std::vector<Solution> solutions;
  solutions.reserve(groups.size());

  // For each group pair it off then pair off in the order of increasing width
  // which is optimal
  for (auto &group : groups) {
    auto sol = MultiComponentStrategy(
        word.substr(group.first, group.second - group.first + 1));
    sol.SetOffset(group.first);
    solutions.push_back(std::move(sol));
  }

  std::sort(solutions.begin(), solutions.end(),
            [](const Solution &a, const Solution &b) {
              return a.GetActualWidth() < b.GetActualWidth();
            });

  for (auto &sol : solutions) {
    solution.PairOffSolution(sol);
  }

  return solution;
}

// Algorithm for where there are single blocks of multiple components
inline Solution MultiComponentStrategySingleGroup(const std::string &word) {
  Solution solution(word);
  auto &&components = GetComponents(word);
  std::deque<std::pair<Solution, Solution>> solutions;

  // Solve each component
  for (auto &component : components) {
    auto sub_word =
        word.substr(component.first, component.second - component.first + 1);
    auto sol_one = WidthOneStrategy(sub_word);

    if (sol_one.IsComplete()) {
      auto bad = solve::Solution::BadSolution(std::move(sub_word));
      sol_one.SetOffset(component.first);
      solutions.push_back({std::move(sol_one), std::move(bad)});
      continue;
    }

    auto sol_left = SingleComponentStrategyLeft(sub_word);
    auto sol_right = SingleComponentStrategyRight(std::move(sub_word));

    sol_left.SetOffset(component.first);
    sol_right.SetOffset(component.first);

    solutions.push_back({std::move(sol_left), std::move(sol_right)});
  }

  // Pair off each solution from the outside in making the move that increases
  // width the least at each step
  while (solutions.size() > 1) {
    auto &front = solutions.front();
    auto &back = solutions.back();

    auto &f_sol =
        front.first.GetActualWidth() > front.second.GetActualWidth() + 1
            ? front.second
            : front.first;
    auto &b_sol = back.second.GetActualWidth() > back.first.GetActualWidth() + 1
                      ? back.first
                      : back.second;

    if (f_sol.GetActualWidth() < b_sol.GetActualWidth()) {
      solution.PairOffSolution(std::move(f_sol));
      solutions.pop_front();
    } else {
      solution.PairOffSolution(std::move(b_sol));
      solutions.pop_back();
    }
  }

  // Pair off the final remaining single block, single component
  auto &front = solutions.front();
  const std::string &front_word = front.first.GetInitialWord();
  if (SingleBlock(front_word)) {
    auto approx = CombinedGreedy(front_word);
    approx.SetOffset(front.first.GetOffset());

    auto &&best_sol = helper::BestSol(
        {std::move(front.first), std::move(front.second), std::move(approx)});
    solution.PairOffSolution(best_sol);
  } else {
    auto best_sol =
        helper::BestSol({std::move(front.first), std::move(front.second)});

    solution.PairOffSolution(best_sol);
  }

  return solution;
}

Solution MultiComponentStrategy(const std::string &word) {
  Solution solution(word);

  if (solution.IsComplete()) return solution;

  // Attempt all strategies using the best
  if (SingleComponent(word)) {
    Solution left_strategy = SingleComponentStrategyLeft(word);
    Solution right_strategy = SingleComponentStrategyRight(word);

    if (SingleBlock(word)) {
      Solution approx = CombinedGreedy(word);

      return helper::BestSol({std::move(left_strategy),
                              std::move(right_strategy), std::move(approx)});
    }

    return helper::BestSol(
        {std::move(left_strategy), std::move(right_strategy)});
  }

  // Make all obvious moves then pass to the respective solver based on the form
  // of the word
  MakeObviousMoves(solution);
  if (solution.IsComplete()) return solution;

  auto groups = GetGroupedComponents(solution.GetWord());

  if (groups.size() > 1) {
    Solution sol =
        MultiComponentStrategyMultiGroups(solution.GetWord(), groups);
    solution.PairOffSolution(sol);

    return solution;
  }

  Solution sol = MultiComponentStrategySingleGroup(solution.GetWord());
  solution.PairOffSolution(sol);

  return solution;
}

Solution Solve(const std::string &word) {
  auto approx = CombinedGreedy(word);
  if (approx.GetWidth() <= 2) return approx;
  auto multi = MultiComponentStrategy(word);

  if (approx.GetWidth() < multi.GetWidth()) return approx;
  return multi;
}

}  // namespace derived
}  // namespace solve
