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

#include "solve_simple_greedy.h"

#include <cassert>
#include <list>
#include <string>
#include <unordered_map>

#include "solve/solution.h"

namespace solve {

using Relations = int *;

Solution SolveSimpleGreedy_prime(const std::string &word, Relations relations,
                                 int start, int end);

// Solve the inner part of a word
inline void SolveInner(const std::string &word, Relations relations,
                       Solution &solution, int start, int inner, int end) {
  // Solve each of the components
  std::vector<Solution> solutions;

  while (inner < end) {
    int next{relations[inner]};
    solutions.push_back(SolveSimpleGreedy_prime(word, relations, inner, next));

    solutions.back().SetOffset(inner - start);

    inner = next + 1;
  }

  int sols{static_cast<int>(solutions.size())};

  // While there are still solutions, pair them off until they are all gone.
  // They are chosen by which has the smallest width
  int i{};
  int j{sols - 1};

  while (i != j) {
    auto &f = solutions[i];
    auto &b = solutions[j];

    if (f.GetWidth() > b.GetWidth() ||
        (f.GetWidth() == b.GetWidth() &&
         f.GetWord().size() > b.GetWord().size())) {
      solution.PairOffSolution(b);
      j--;
    } else {
      solution.PairOffSolution(f);
      i++;
    }
  }

  solution.PairOffSolution(solutions[i]);
}

// Recursive call for the simply greedy algorithm which pairs off each end then
// solves the inner components of the word returning the created solution
Solution SolveSimpleGreedy_prime(const std::string &word, Relations relations,
                                 int start, int end) {
  int len{end - start};
  Solution solution(word.substr(start, len + 1));

  solution.PairOff(0, len);

  if (len == 1) {
    return solution;
  }

  SolveInner(word, relations, solution, start, start + 1, end);

  return solution;
}

Solution SolveSimpleGreedy(const std::string &word) {
  assert(word.size() >= 2);
  int size = static_cast<int>(word.size());
  int relations[size - 1];
  int stack[size / 2];
  int head{};

  // Calculate which opening bracket each closing bracket is associated with
  for (int i{}; i < size; i++) {
    if (word[i] == OPENING_BRACKET) {
      stack[head++] = i;
    } else {
      relations[stack[--head]] = i;
    }
  }

  Solution solution(word);

  SolveInner(word, relations, solution, 0, 0, size);

  return solution;
}

}  // namespace solve
