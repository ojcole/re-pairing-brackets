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

#include "verifiers.h"

#include <gtest/gtest.h>

#include "generate/generate_random.h"
#include "generate/generate_random_hard.h"

namespace {

const int kRuns = 10000;

TEST(VerifySymmetricWordTest, AcceptsSymmetricWords) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomSymmetricWord(10);

    ASSERT_TRUE(helper::VerifySymmetricWord(word));
  }
}

TEST(VerifySymmetricWordTest, DeniesNonSymmetricWords) {
  EXPECT_FALSE(helper::VerifySymmetricWord("()(())"));
  EXPECT_FALSE(helper::VerifySymmetricWord("(()(())"));
  EXPECT_FALSE(helper::VerifySymmetricWord("(())((())"));
  EXPECT_FALSE(helper::VerifySymmetricWord("()()(())"));
}

TEST(VerifySymmetricHardWordTest, AcceptsSymmetricHardWords) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomSymmetricHardWord(10);

    ASSERT_TRUE(helper::VerifySymmetricHardWord(word));
  }
}

TEST(VerifySymmetricHardWordTest, RejectsNonSymmetricHardWords) {
  EXPECT_FALSE(helper::VerifySymmetricHardWord("(()())"));
  EXPECT_FALSE(helper::VerifySymmetricHardWord("(()())()"));
  EXPECT_FALSE(helper::VerifySymmetricHardWord("(()())()(()())"));
  EXPECT_FALSE(helper::VerifySymmetricHardWord("()()()"));
  EXPECT_FALSE(helper::VerifySymmetricHardWord("(())()"));
}

TEST(VerifyWordTest, AcceptsWords) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomUniformWord(10);

    ASSERT_TRUE(helper::VerifyWord(word));
  }
}

TEST(VerifyWordTest, RejectsNonWords) {
  EXPECT_FALSE(helper::VerifyWord("(()"));
  EXPECT_FALSE(helper::VerifyWord("(x())"));
  EXPECT_FALSE(helper::VerifyWord("(()))"));
  EXPECT_FALSE(helper::VerifyWord("((((())))"));
}

TEST(VerifyHardWordTest, AcceptsHardWords) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomHardWord(10);

    ASSERT_TRUE(helper::VerifyHardWord(word));
  }
}

TEST(VerifyHardWordTest, RejectsNonHardWords) {
  EXPECT_FALSE(helper::VerifyHardWord("(()())"));
  EXPECT_FALSE(helper::VerifyHardWord("(()())()(()())"));
  EXPECT_FALSE(helper::VerifyHardWord("()()()"));
  EXPECT_FALSE(helper::VerifyHardWord("(((())))(())"));
}

}  // namespace
