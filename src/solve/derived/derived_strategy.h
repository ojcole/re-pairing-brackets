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

#ifndef PROJECT_SOLVE_DERIVED_DERIVED_STRATEGY_H_
#define PROJECT_SOLVE_DERIVED_DERIVED_STRATEGY_H_

#include <string>

#include "solve/solution.h"

namespace solve {
namespace derived {

// Purely derived solving
Solution MultiComponentStrategy(const std::string &word);

// Solve a specified word using a derived strategy mixed with greedy
Solution Solve(const std::string &word);

// Solve from a beginning iterator to an end all words using a purely derived
// strategy
template <typename Iter>
Solutions DerivedSolves(Iter begin, Iter end) {
  Solutions result;

  for (; begin != end; begin++) {
    auto solution = MultiComponentStrategy(*begin);
    result.push_back(solution);
  }

  return result;
}

// Solve from a beginning iterator to an end all words using a mix of the
// derived strategy and greedy moves
template <typename Iter>
Solutions Solve(Iter begin, Iter end) {
  Solutions result;

  for (; begin != end; begin++) {
    auto solution = Solve(*begin);
    result.push_back(solution);
  }

  return result;
}

}  // namespace derived
}  // namespace solve

#endif
