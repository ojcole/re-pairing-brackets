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

#include <gtest/gtest.h>

#include "generate/generate_all.h"
#include "solve/solve_test_helpers.h"

namespace {

TEST(SolveExhaustive, ValidRePairings) {
  auto words = generate::GenerateSwapping(13);

  for (auto &word : words) {
    auto solution = solve::ExhaustiveSolve(word);
    auto valid = ValidSolution(solution);

    ASSERT_FALSE(valid.has_value())
        << *valid << " " << solution << " " << solution.GetInitialWord();
  }
}

TEST(SolveExhaustive, AllMemoSettingsSameResults) {
  auto words = generate::GenerateSwapping(13);

  for (auto &word : words) {
    auto solution1 = solve::ExhaustiveSolve(word);
    auto solution2 = solve::ExhaustiveSolveLimitedMemo(word);
    auto solution3 = solve::ExhaustiveSolvePeriodMemo(word);

    ASSERT_EQ(solution1, solution2);
    ASSERT_EQ(solution2, solution3);
  }
}

TEST(SolveExhaustive, CorrectWidth) {
  auto words = generate::GenerateSwapping(13);
  auto words2 = generate::GenerateSwapping(13);

  words.insert(words.end(), words2.begin(), words2.end());

  for (auto &word : words) {
    auto solution = solve::ExhaustiveSolve(word);

    ASSERT_LE(solution.GetWidth(), 3);
  }
}

}  // namespace
