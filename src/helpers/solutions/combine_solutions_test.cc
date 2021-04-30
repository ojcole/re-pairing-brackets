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

#include "combine_solutions.h"

#include <gtest/gtest.h>

#include <vector>

#include "solve/solution.h"

namespace {

TEST(CombineSolutions, ReturnsASolution) {
  solve::Solution solution1("");
  solution1.AddWidth(1);
  solve::Solution solution2("");
  solution2.AddWidth(2);
  solve::Solution solution3("");
  solution3.AddWidth(3);
  solve::Solution solution4("");
  solution4.AddWidth(4);

  std::vector<solve::Solution> solutions;

  solutions.push_back(solution1);
  solutions.push_back(solution2);
  solutions.push_back(solution3);
  solutions.push_back(solution4);

  auto best = helper::BestSol({solution1, solution2, solution3, solution4});

  auto it = std::find(solutions.begin(), solutions.end(), best);
  ASSERT_NE(it, solutions.end());
}

TEST(CombineSolutions, ReturnsTheLowestWidth) {
  solve::Solution solution1("");
  solution1.AddWidth(1);
  solve::Solution solution2("");
  solution2.AddWidth(2);
  solve::Solution solution3("");
  solution3.AddWidth(3);
  solve::Solution solution4("");
  solution4.AddWidth(4);

  std::vector<solve::Solution> solutions;

  solutions.push_back(solution1);
  solutions.push_back(solution2);
  solutions.push_back(solution3);
  solutions.push_back(solution4);

  auto best = helper::BestSol({solution1, solution2, solution3, solution4});

  ASSERT_EQ(best, solution1);
}

}  // namespace
