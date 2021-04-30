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

#include "width_check.h"

#include <gtest/gtest.h>

#include "generate/generate_all.h"
#include "generate/generate_next_symmetric.h"
#include "solve/exhaustive/solve_exhaustive.h"

namespace {

TEST(RegularWordWidth, CorrectlyJudgesWidth) {
  auto words = generate::GenerateSwapping(12);

  for (auto &word : words) {
    auto solution = solve::ExhaustiveSolve(word);

    for (int i{}; i <= solution.GetWidth(); i++) {
      ASSERT_TRUE(solve::predicate::WordIsWidthAtLeastN(word, i));
    }

    ASSERT_FALSE(
        solve::predicate::WordIsWidthAtLeastN(word, solution.GetWidth() + 1));
  }
}

TEST(SymmetricHardWordWidth, CorrectlyJudgesWidth) {
  auto words = generate::GenerateSymmetric(12);

  for (auto &word : words) {
    auto full_word = "(" + word + ")" + "(" + word + ")";
    auto solution = solve::ExhaustiveSolve(full_word);

    for (int i{}; i <= solution.GetWidth(); i++) {
      ASSERT_TRUE(
          solve::predicate::SymmetricHardWordIsWidthAtLeastN(full_word, i));
    }

    ASSERT_FALSE(solve::predicate::SymmetricHardWordIsWidthAtLeastN(
        full_word, solution.GetWidth() + 1));
  }
}

}  // namespace
