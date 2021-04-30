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

#include "solution.h"

#include <gtest/gtest.h>

namespace {

int CalculateWidth(const std::string &word) {
  bool new_comp = true;
  int width = 0;

  for (auto ch : word) {
    if (ch != STRING_GAP && new_comp) {
      new_comp = false;
      width++;
    } else if (ch == STRING_GAP) {
      new_comp = true;
    }
  }

  return width;
}

TEST(SolutionTest, RecalculateWidthTest) {
  const char kLeft = 'L';
  const char kRight = 'R';

  std::vector<std::string> cases;

  // together cases e.g. xLRx
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      std::string cs;

      if (i < 2) cs += i == 0 ? STRING_GAP : 'x';

      cs += kLeft;
      cs += kRight;

      if (j < 2) cs += j == 0 ? STRING_GAP : 'x';

      cases.push_back(cs);
    }
  }

  // separate cases e.g. xLxRx
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 1; j++) {
      for (int k = 0; k <= 1; k++) {
        for (int l = 0; l <= 2; l++) {
          std::string cs;

          if (i < 2) cs += i == 0 ? STRING_GAP : 'x';
          cs += kLeft;
          cs += j == 0 ? STRING_GAP : 'x';
          cs += k == 0 ? STRING_GAP : 'x';
          cs += kRight;
          if (l < 2) cs += l == 0 ? STRING_GAP : 'x';

          cases.push_back(cs);
        }
      }
    }
  }

  for (auto word : cases) {
    std::string output_word(word);

    std::replace(output_word.begin(), output_word.end(), ' ', '_');

    auto first = word.find('L');
    auto second = word.find('R');

    int width = CalculateWidth(word);

    std::string chars = "()";

    assert(first != std::string::npos);
    assert(second != std::string::npos);

    word[first] = STRING_GAP;
    word[second] = STRING_GAP;

    int width_diff = CalculateWidth(word) - width;

    EXPECT_EQ(width_diff, solve::RecalculateWidthRemoval(word, first, second))
        << output_word << " (" << first << ", " << second << ")";
  }
}

TEST(SolutionTest, UndoMove) {
  std::string word{"(())"};

  solve::Solution sol(word);
  auto cpy = sol;

  sol.PairOff(0, 3);
  sol.Undo(1, 1);

  ASSERT_EQ(cpy, sol);
}

}  // namespace
