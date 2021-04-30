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

#include "solve_greedy.h"

#include <algorithm>
#include <string>
#include <utility>

#include "greedy_strategy_1.h"
#include "greedy_strategy_2.h"
#include "solve/solution.h"

namespace solve {

using OpenStrategy = int (*)(const std::string &, int, int);
using CloseStrategy = int (*)(const std::string &, int, int, int);

// Using an opening strategy and a closing strategy, choose a pair of open and
// close brackets greedily to pair off in the solution
std::pair<int, int> GreedyPair(const Solution &solution,
                               OpenStrategy &ScoreOpen,
                               CloseStrategy &ScoreClose) {
  std::string word = solution.GetWord();
  const int kMinDepth = 0;
  const int kWordSize = static_cast<int>(word.size());

  // Look at all possible opening brackets and score them choosing the best one.
  // Then perform the same thing using the chosen opening bracket for the
  // closing bracket
  int depth[kWordSize];
  int component[kWordSize];
  int running_component{0};
  int running_depth{kMinDepth - 1};
  int best_open_score{-1};
  int best_open_i{-1};
  for (int i = 0; i < kWordSize; i++) {
    if (word[i] == OPENING_BRACKET) {
      component[i] = running_component;
      depth[i] = ++running_depth;

      int score = ScoreOpen(word, i, depth[i]);

      if (score > best_open_score) {
        best_open_score = score;
        best_open_i = i;
      }
    } else if (word[i] == CLOSING_BRACKET) {
      depth[i] = running_depth--;
      if (depth[i] == kMinDepth) {
        component[i] = running_component++;
      } else {
        component[i] = running_component;
      }
    } else {
      depth[i] = running_depth;
      component[i] = -1;
    }
  }

  int best_close_score{-1};
  int best_close_i{-1};
  for (int i = best_open_i + 1; i < kWordSize; i++) {
    if (word[i] == CLOSING_BRACKET && component[best_open_i] == component[i]) {
      int score = ScoreClose(word, best_open_i, i, depth[i]);

      if (score > best_close_score) {
        best_close_score = score;
        best_close_i = i;
      }
    }
  }

  return {best_open_i, best_close_i};
}

// Repeatedly choose brackets until the entire word is gone
Solution SolveGreedyStrategy(const std::string &word, OpenStrategy &ScoreOpen,
                             CloseStrategy &ScoreClose) {
  const int kLength = static_cast<int>(word.size() / 2);

  Solution solution(word);

  for (int i = 0; i < kLength; i++) {
    std::pair<int, int> matching = GreedyPair(solution, ScoreOpen, ScoreClose);

    solution.PairOff(matching.first, matching.second);
  }

  return solution;
}

Solution SolveGreedy(const std::string &word) {
  // Enumerate all strategies to try, then try them returning the best short
  // circuiting if any return a score of <= 2 which must be optimal
  std::vector<std::pair<OpenStrategy, CloseStrategy>> strategies = {
      {&greedy1::ScoreOpenIndex, &greedy1::ScoreCloseIndex},
      {&greedy2::ScoreOpenIndex, &greedy2::ScoreCloseIndex}};

  Solution best_sol =
      SolveGreedyStrategy(word, strategies[0].first, strategies[0].second);

  if (best_sol.GetWidth() <= 2) return best_sol;

  for (size_t i{1}; i < strategies.size(); i++) {
    Solution sol =
        SolveGreedyStrategy(word, strategies[i].first, strategies[i].second);

    if (sol.GetWidth() < best_sol.GetWidth()) {
      best_sol = sol;

      if (best_sol.GetWidth() <= 2) return best_sol;
    }
  }

  return best_sol;
}

}  // namespace solve
