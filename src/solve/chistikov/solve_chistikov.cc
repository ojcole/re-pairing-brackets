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

#include "solve_chistikov.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "solve/solution.h"

namespace solve {

// Algorithm Sketch:
//
// Check if any sigma_j in the word has length > N/2
//
// If it doesn't, return the current begin and end
//
// If it does, select this component and recurse, setting the begin to lower
// bound + 1, end to upper bound
std::pair<int, int> CalculateSigmaF(const std::string &word, int begin, int end,
                                    const int kNby2) {
  int begin_index{begin};
  int depth{};

  for (int i{begin}; i < end; i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      if (depth == 0) {
        int len = (i + 1) - begin_index;

        if (len > kNby2) {
          return CalculateSigmaF(word, begin_index + 1, i + 1, kNby2);
        }

        begin_index = i;
      }
    }
  }

  return {begin, end};
}

// Algorithm Sketch:
//
// Base case: () can be repaired using 0, 1
//
// For each component in turn, split the word in the middle by calculating
// sigma_f
//
// Split the word into both sigma_f and Lf and Rf
//
// Recurse to solve sigma_f
//
// Repair the original word from the result of sigma_f
//
// Recurse to solve LfRf
//
// Repair the original word from the result of LfRf
Solution ChistikovSolvesComponent(std::string word, int offset,
                                  SolutionMemo &memo) {
  // If we have already solved this word, use the already known solution
  auto sol_it = memo.find(word);
  if (sol_it != memo.end()) {
    auto sol = sol_it->second;

    sol.SetOffset(offset);

    return sol;
  }

  Solution solution(word, offset);

  // Base case
  if (word == "()") {
    solution.PairOff(0, 1);

    memo.insert({"()", solution});

    return solution;
  }

  const int kNby2 = word.size();

  // Calculate sigma f and re-pair it
  std::pair<int, int> sigma_f_indices =
      CalculateSigmaF(word, 0, word.size(), kNby2);

  std::string sigma_f =
      word.substr(sigma_f_indices.first + 1,
                  sigma_f_indices.second - sigma_f_indices.first - 2);

  Solution sigma_f_solution = SolveChistikovMemo(sigma_f, memo);
  sigma_f_solution.SetOffset(sigma_f_indices.first + 1);
  solution.PairOffSolution(sigma_f_solution);
  solution.PairOff(sigma_f_indices.first, sigma_f_indices.second - 1);

  // Remove sigma f from the word
  word.erase(word.begin() + sigma_f_indices.first,
             word.begin() + sigma_f_indices.second);

  // Solve LfRf and then pair off
  Solution lfrf_solution = SolveChistikovMemo(word, memo);

  for (auto &pair : lfrf_solution.GetRepairing()) {
    // Pair off the lfrf solution picking the correct indices by checking
    // whether they fall before or after where sigma_f existed in the original
    // word
    int first = pair.first > sigma_f_indices.first
                    ? pair.first
                    : pair.first + sigma_f_indices.first;
    int second = pair.second > sigma_f_indices.first
                     ? pair.second
                     : pair.second + sigma_f_indices.first;

    solution.PairOff(first, second);
  }

  // Save the result
  memo.insert({word, solution});

  return solution;
}

// Solve each of the components of a word independently of each other and
// combine into solving the whole word
Solution SolveComponents(const std::string &word, SolutionMemo &memo) {
  Solution solution(word);
  int depth{};
  int begin_index{};

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;

      if (depth == 0) {
        // If the depth is 0 then the component is complete so solve it
        // combining into the full sol
        auto w = word.substr(begin_index, i - begin_index + 1);
        auto &&sol = ChistikovSolvesComponent(w, begin_index, memo);

        solution.PairOffSolution(sol);
        begin_index = i + 1;
      }
    }
  }

  return solution;
}

Solution SolveChistikov(const std::string &word) {
  SolutionMemo memo;

  return SolveChistikovMemo(word, memo);
}

Solution SolveChistikovMemo(const std::string &word, SolutionMemo &memo) {
  // Check the memo for the full word
  auto sol_it = memo.find(word);

  if (sol_it != memo.end()) {
    auto sol = sol_it->second;

    sol.SetOffset(0);

    return sol;
  }

  // Solve each component of the word
  Solution solution = SolveComponents(word, memo);

  memo.insert({word, solution});

  return solution;
}

}  // namespace solve
