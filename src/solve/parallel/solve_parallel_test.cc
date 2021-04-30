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

#include "solve_parallel.h"

#include <gtest/gtest.h>

#include "helpers/catalan.h"

namespace {

// https://oeis.org/A001519
size_t CalculateOneCount(size_t n) {
  size_t dp[n + 1];

  dp[0] = 1;
  dp[1] = 1;

  for (size_t i{2}; i <= n; i++) {
    dp[i] = 3 * dp[i - 1] - dp[i - 2];
  }

  return dp[n];
}

TEST(SolveLazy, CorrectTotal) {
  auto res = solve::parallel::SolveLazy(13, 4);
  auto catalan = helper::CalculateNthCatalanNumber(13);

  ASSERT_EQ(res.one_count + res.two_count, catalan);
  ASSERT_EQ(res.other.size(), 0);
}

TEST(SolveLazy, CorrectOneCount) {
  auto res = solve::parallel::SolveLazy(13, 4);
  auto one_count = CalculateOneCount(13);

  ASSERT_EQ(res.one_count, one_count);
}

TEST(SolveMinimal, CorrectTotal) {
  auto res = solve::parallel::SolveMinimal(12, 4);
  auto catalan = helper::CalculateNthCatalanNumber(5);

  ASSERT_EQ(res.one_count + res.two_count, catalan * catalan);
  ASSERT_EQ(res.other.size(), 0);
}

TEST(SolveMinimal, CorrectOneCount) {
  auto res = solve::parallel::SolveMinimal(12, 4);

  ASSERT_EQ(res.one_count, 0);
}

TEST(SolveCollect, CorrectTotal) {
  auto res = solve::parallel::SolveCollect(13, 4);
  auto catalan = helper::CalculateNthCatalanNumber(13);

  ASSERT_EQ(res.size(), catalan);
}

TEST(SolveCollect, CorrectOneCount) {
  auto res = solve::parallel::SolveCollect(13, 4);

  int one{};
  for (auto &word : res) {
    ASSERT_TRUE(word.GetWidth() == 1 || word.GetWidth() == 2);

    if (word.GetWidth() == 1) {
      one++;
    }
  }

  auto one_count = CalculateOneCount(13);

  ASSERT_EQ(one_count, one);
}

}  // namespace
