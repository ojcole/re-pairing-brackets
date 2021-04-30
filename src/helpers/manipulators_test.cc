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

#include "manipulators.h"

#include <gtest/gtest.h>

#include <random>
#include <string>

#include "constants.h"
#include "generate/generate_random.h"

namespace {

const int kRuns = 10000;

std::string RandomMangle(const std::string &word, std::mt19937 &randgen) {
  std::bernoulli_distribution dist(0.2);
  std::string altered;
  for (auto c : word) {
    altered += c;
    if (dist(randgen)) {
      altered += 'a';
    }
  }

  return altered;
}

TEST(CompressWordTest, MangledCharactersAreRemoved) {
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i{}; i < kRuns; i++) {
    std::string word = generate::RandomUniformWord(10);
    auto mangled = RandomMangle(word, gen);

    auto compressed = helper::CompressWord(mangled);

    for (auto c : compressed) {
      ASSERT_TRUE(c == OPENING_BRACKET || c == CLOSING_BRACKET);
    }
  }
}

TEST(CompressWordTest, IsTheSameStartingWord) {
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i{}; i < kRuns; i++) {
    std::string word = generate::RandomUniformWord(10);
    auto mangled = RandomMangle(word, gen);

    auto compressed = helper::CompressWord(mangled);

    ASSERT_EQ(compressed, word);
  }
}

TEST(SplitAtXTest, SplitsAtX) {
  std::string word = "(((X)))";
  auto result = helper::SplitAtX(word, 'X');

  EXPECT_EQ(result.first, "(((");
  EXPECT_EQ(result.second, ")))");
}

TEST(SplitAtXTest, SplitsAtXStart) {
  std::string word = "x((()))";
  auto result = helper::SplitAtX(word, 'x');

  EXPECT_EQ(result.first, "");
  EXPECT_EQ(result.second, "((()))");
}

TEST(SplitAtXTest, SplitsAtXEnd) {
  std::string word = "((()))x";
  auto result = helper::SplitAtX(word, 'x');

  EXPECT_EQ(result.first, "((()))");
  EXPECT_EQ(result.second, "");
}

TEST(StripWordTest, StripsEnds) {
  std::string word = "  (())()      x";
  auto result = helper::StripWord(word);

  EXPECT_EQ(result, "(())()");
}

TEST(StripWordTest, MaintainsMiddle) {
  std::string word = "  (()   )()      x";
  auto result = helper::StripWord(word);

  EXPECT_EQ(result, "(()   )()");
}

TEST(MirrorWordTest, MaintainsOriginalWord) {
  std::string word = "(((())))";
  std::string initial_word = word;
  helper::MirrorWord(word);

  EXPECT_EQ(word, initial_word);
}

TEST(MirrorWordTest, MirrorsWord) {
  std::string word = "(((";
  auto res = helper::MirrorWord(word);

  EXPECT_EQ(res, "((()))");

  word = "()(";
  res = helper::MirrorWord(word);

  EXPECT_EQ(res, "()()()");
}

}  // namespace
