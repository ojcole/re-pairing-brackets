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

#include "all_repairings.h"

#include <gtest/gtest.h>

#include "generate/generate_all.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/solve_test_helpers.h"

namespace {

TEST(AllRepairings, AllValidRepairings) {
  auto words = generate::GenerateSwapping(8);

  for (auto &word : words) {
    auto res = solve::repairings::AllOptimalRepairings(word, 1000000);
    auto sol = solve::ExhaustiveSolve(word);

    ASSERT_EQ(res.width, sol.GetWidth());

    for (auto &repairing : res.repairings) {
      auto tested = ValidRepairing(repairing, word);

      ASSERT_FALSE(tested.has_value()) << *tested;
    }
  }
}

TEST(AllRepairings, CorrectForHardest3) {
  std::string word1{"(((())((()))(())))(((())(((())))(())))"};
  std::string word2{"(((())(((())))(())))(((())((()))(())))"};

  auto res1 = solve::repairings::AllOptimalRepairings(word1, 100000, 7);
  auto res2 = solve::repairings::AllOptimalRepairings(word2, 100000, 7);

  ASSERT_EQ(res1.repairings.size(), 1);
  ASSERT_EQ(res2.repairings.size(), 1);
  ASSERT_EQ(res1.width, 2);
  ASSERT_EQ(res2.width, 2);
}

}  // namespace
