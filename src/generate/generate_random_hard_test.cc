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

#include "generate_random_hard.h"

#include <gtest/gtest.h>

#include <random>

#include "generate_test_helpers.h"
#include "helpers/verifiers.h"

#define TOTAL_WORDS 100000
#define MIN_SIZE 10
#define MAX_SIZE 200

namespace {

TEST(GenerateAnyRandomHard, IsValidWord) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> dist(MIN_SIZE, MAX_SIZE);

  for (int i{}; i < TOTAL_WORDS; i++) {
    int size = dist(generator);
    auto word = generate::RandomHardWord(size);
    auto res = generate::test::ValidWordOfLengthN(word, size);

    ASSERT_FALSE(res.has_value()) << *res;
  }
}

TEST(GenerateAnyRandomHard, IsHardWord) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> dist(MIN_SIZE, MAX_SIZE);

  for (int i{}; i < TOTAL_WORDS; i++) {
    int size = dist(generator);
    auto word = generate::RandomHardWord(size);

    ASSERT_TRUE(helper::VerifyHardWord(word));
  }
}

TEST(GenerateRandomSymmetric, IsValidWord) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> dist(MIN_SIZE, MAX_SIZE);

  for (int i{}; i < TOTAL_WORDS; i++) {
    int size = dist(generator);
    size += size % 2;

    auto word = generate::RandomSymmetricHardWord(size);
    auto res = generate::test::ValidWordOfLengthN(word, size);

    ASSERT_FALSE(res.has_value()) << *res;
  }
}

TEST(GenerateRandomSymmetric, IsSymmetricHardWord) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> dist(MIN_SIZE, MAX_SIZE);

  for (int i{}; i < TOTAL_WORDS; i++) {
    int size = dist(generator);
    size += size % 2;

    auto word = generate::RandomSymmetricHardWord(size);

    ASSERT_TRUE(helper::VerifySymmetricHardWord(word));
  }
}

}  // namespace
