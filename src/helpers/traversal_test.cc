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

#include "traversal.h"

#include <gtest/gtest.h>

namespace {

TEST(Traversal, ClosingBracket) {
  std::string word{"((()()(())))"};

  ASSERT_EQ(helper::ClosingBracket(word, 0), 11);
  ASSERT_EQ(helper::ClosingBracket(word, 1), 10);
  ASSERT_EQ(helper::ClosingBracket(word, 2), 3);
  ASSERT_EQ(helper::ClosingBracket(word, 4), 5);
  ASSERT_EQ(helper::ClosingBracket(word, 6), 9);
  ASSERT_EQ(helper::ClosingBracket(word, 7), 8);
}

TEST(Traversal, NextChar) {
  std::string word{"((  (  ))  )  )"};

  ASSERT_EQ(helper::NextChar(word, 0), 1);
  ASSERT_EQ(helper::NextChar(word, 1), 4);
  ASSERT_EQ(helper::NextChar(word, 4), 7);
  ASSERT_EQ(helper::NextChar(word, 7), 8);
  ASSERT_EQ(helper::NextChar(word, 8), 11);
  ASSERT_EQ(helper::NextChar(word, 11), 14);
  ASSERT_EQ(helper::NextChar(word, 14), 15);
}

TEST(Traversal, PrevChar) {
  std::string word{"((  (  ))  )  )"};

  ASSERT_EQ(helper::PrevChar(word, 0), -1);
  ASSERT_EQ(helper::PrevChar(word, 1), 0);
  ASSERT_EQ(helper::PrevChar(word, 4), 1);
  ASSERT_EQ(helper::PrevChar(word, 7), 4);
  ASSERT_EQ(helper::PrevChar(word, 8), 7);
  ASSERT_EQ(helper::PrevChar(word, 11), 8);
  ASSERT_EQ(helper::PrevChar(word, 14), 11);
}

}  // namespace
