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

#include "manual_search.h"

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "generate/generate_random.h"
#include "generate/generate_random_hard.h"
#include "helpers/manipulators.h"

namespace {

const int kRuns = 1000;
const std::string kDir = "manual/test_files/";
const std::string kTempFileLocation = kDir + "tmp_file.txt";
const std::string kLoadWord1Location = kDir + "load_word_1.txt";
const std::string kLoadWords1Location = kDir + "load_words_1.txt";
const std::string kLoadHalfWord1Location = kDir + "load_half_word_1.txt";
const std::string kLoadHalfSpreadWord1Location =
    kDir + "load_half_spread_word_1.txt";
const std::string kLoadSpreadWord1Location = kDir + "load_spread_word_1.txt";
const std::string kSpreadHalfHardWord = kDir + "spread_hard_half_word.txt";

TEST(SaveWordTest, WordIsSaved) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomUniformWord(10);

    manual::SaveWord(word, kTempFileLocation);

    auto retrieved = manual::LoadWord(kTempFileLocation);

    ASSERT_EQ(word, retrieved);
  }
}

TEST(SaveWordsTest, WordsAreAllSaved) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> word_count_dist(0, 200);

  for (int i{}; i < kRuns; i++) {
    auto word_count = word_count_dist(gen);
    std::vector<std::string> words;

    for (int j{}; j < word_count; j++) {
      auto word = generate::RandomUniformWord(10);

      words.push_back(word);
    }

    manual::SaveWords(words, kTempFileLocation);

    auto retrieved = manual::LoadWords(kTempFileLocation);

    ASSERT_EQ(words, retrieved);
  }
}

TEST(LoadWordTest, WordIsCorrectlyLoaded) {
  auto word = manual::LoadWord(kLoadWord1Location);

  EXPECT_EQ(word, "(((())))");
}

TEST(LoadWordsTest, WordsAreCorrectlyLoaded) {
  auto words = manual::LoadWords(kLoadWords1Location);
  std::vector<std::string> expected = {"(((())))", "()", "(())", "(())()",
                                       "(((())(((())))(())))"};

  EXPECT_EQ(words, expected);
}

TEST(LoadHalfWordTest, WordIsCorrectlyLoaded) {
  auto word = manual::LoadHalfWord(kLoadHalfWord1Location);

  EXPECT_EQ(word, "(())(())()(())(())()");
}

TEST(LoadHalfSpreadWordTest, WordIsCorrectlyLoaded) {
  auto word = manual::LoadSpreadHalfWord(kLoadHalfSpreadWord1Location);

  EXPECT_EQ(word, "(((()()))())(((()()))())");
}

TEST(LoadSpreadWordTest, WordIsCorrectlyLoaded) {
  auto word = manual::LoadSpreadWord(kLoadSpreadWord1Location);

  EXPECT_EQ(word, "(((()()))())");
}

TEST(SpreadWordTest, CompressingTheSpreadWordResultsInTheOriginalWord) {
  for (int i{}; i < kRuns; i++) {
    auto word = generate::RandomSymmetricHardWord(20);
    auto spread_word = manual::SpreadSymmetricHardWord(word);
    auto actual = helper::CompressWord(spread_word);
    actual = actual + actual;

    ASSERT_EQ(word, actual);
  }
}

TEST(SpreadWordTest, WordIsCorrectlySpread) {
  std::string word = "(((()()())(()()())))(((()()())(()()())))";
  auto spread = manual::SpreadSymmetricHardWord(word);
  std::string expected = R"(((
  (
    ()
    ()
    ()
  )
  (
    ()
    ()
    ()
  )
)))";

  EXPECT_EQ(spread, expected);
}

TEST(SymmetricHardWordWidthAtLeastNTest, WidthIsCorrectlyIdentified) {
  EXPECT_TRUE(manual::SymmetricHardWordWidthAtLeastN(kSpreadHalfHardWord, 2));
  EXPECT_FALSE(manual::SymmetricHardWordWidthAtLeastN(kSpreadHalfHardWord, 4));
  EXPECT_TRUE(manual::SymmetricHardWordWidthAtLeastN(kSpreadHalfHardWord, 3));
}

}  // namespace
