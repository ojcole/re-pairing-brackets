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

#include "generate_all.h"

#include <gtest/gtest.h>

#include "generate_test_helpers.h"
#include "helpers/catalan.h"
#include "helpers/n_choose_k.h"

#define WORD_SIZE_LIMIT 15

namespace {

// Tests for dynamic generation

TEST(GenerateAllDynamicTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateDynamic(i);
    auto expected = helper::CalculateNthCatalanNumber(i);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllDynamicTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateDynamic(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

// Tests for constant next generation

TEST(GenerateAllConstantTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateConstant(i);
    auto expected = helper::CalculateNthCatalanNumber(i);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllConstantTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateConstant(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

// Tests for swapping generation

TEST(GenerateAllSwappingTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSwapping(i);
    auto expected = helper::CalculateNthCatalanNumber(i);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllSwappingTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSwapping(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

// Tests for simple generation

TEST(GenerateAllSimpleTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSimple(i);
    auto expected = helper::CalculateNthCatalanNumber(i);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllSimpleTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSimple(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

TEST(GenerateAllSimpleTest, WordsAreInLexicographicOrder) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSimple(i);

    for (size_t j{1}; j < words.size(); j++) {
      ASSERT_GT(words[j - 1], words[j]);
    }
  }
}

// Tests for simple memoed generation

TEST(GenerateAllSimpleMemoTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateMemoed(i);
    auto expected = helper::CalculateNthCatalanNumber(i);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllSimpleMemoTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateMemoed(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

// Tests for symmetric generation

TEST(GenerateAllSymmetricTest, GeneratesCorrectNumberOfWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSymmetric(i);
    auto expected = helper::NChooseK(i, i / 2);
    ASSERT_EQ(words.size(), expected)
        << "Incorrect number of words for i = " << i;
  }
}

TEST(GenerateAllSymmetricTest, GeneratesOnlyValidWords) {
  for (size_t i{}; i < WORD_SIZE_LIMIT; i++) {
    auto words = generate::GenerateSymmetric(i);

    for (auto word : words) {
      auto res = generate::test::ValidWordOfLengthN(word, i);

      ASSERT_FALSE(res.has_value()) << *res;
    }
  }
}

}  // namespace
