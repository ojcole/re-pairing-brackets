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

#include "hardness.h"

#include <gtest/gtest.h>

#include <random>

#include "generate/generate_random.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/repairings/all_repairings.h"

namespace stats {

std::ostream &operator<<(std::ostream &stream, const Hardness &h) {
  return stream << "{ Word: \"" << h.word << "\", Width: " << h.width
                << ", Hardness: " << h.hardness << " }";
}

}  // namespace stats

namespace {

TEST(HardnessWidth, HardnessWidthIsCorrect) {
  const int runs = 50000;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> len_dist(8, 15);

  for (int i{}; i < runs; i++) {
    auto len = len_dist(gen);
    auto word = generate::RandomUniformWord(len);
    auto expected = solve::ExhaustiveSolvePeriodMemo(word);
    auto actual = stats::ComputeHardness(word, 0);

    ASSERT_EQ(expected.GetWidth(), actual.width);
  }
}

TEST(HardnessWidth, ValueCount) {
  const int runs = 100;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> len_dist(8, 15);
  std::uniform_int_distribution<int> sig_dist(0, 6);

  for (int i{}; i < runs; i++) {
    auto len = len_dist(gen);
    auto sig = sig_dist(gen);
    auto word = generate::RandomUniformWord(len);
    auto expected = solve::repairings::AllOptimalRepairings(word, 1000000, sig);
    auto actual = stats::ComputeHardness(word, sig);

    ASSERT_EQ(expected.repairings.size(), actual.hardness);
  }
}

TEST(HardnessComparisons, LessThan) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"", 2, 12};
  stats::Hardness hard3 = {"", 2, 8};
  stats::Hardness hard4 = {"", 1, 10};
  stats::Hardness hard5 = {"", 3, 10};

  ASSERT_LT(hard2, hard1);
  ASSERT_LT(hard1, hard3);
  ASSERT_LT(hard4, hard1);
  ASSERT_LT(hard1, hard5);
}

TEST(HardnessComparisons, LessThanOrEqual) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"", 2, 12};
  stats::Hardness hard3 = {"", 2, 8};
  stats::Hardness hard4 = {"", 1, 10};
  stats::Hardness hard5 = {"", 3, 10};

  ASSERT_LE(hard1, hard1);
  ASSERT_LE(hard2, hard1);
  ASSERT_LE(hard1, hard3);
  ASSERT_LE(hard4, hard1);
  ASSERT_LE(hard1, hard5);
}

TEST(HardnessComparisons, GreaterThan) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"", 2, 12};
  stats::Hardness hard3 = {"", 2, 8};
  stats::Hardness hard4 = {"", 1, 10};
  stats::Hardness hard5 = {"", 3, 10};

  ASSERT_GT(hard1, hard2);
  ASSERT_GT(hard3, hard1);
  ASSERT_GT(hard1, hard4);
  ASSERT_GT(hard5, hard1);
}

TEST(HardnessComparisons, GreaterThanOrEqual) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"", 2, 12};
  stats::Hardness hard3 = {"", 2, 8};
  stats::Hardness hard4 = {"", 1, 10};
  stats::Hardness hard5 = {"", 3, 10};

  ASSERT_GE(hard1, hard1);
  ASSERT_GE(hard1, hard2);
  ASSERT_GE(hard3, hard1);
  ASSERT_GE(hard1, hard4);
  ASSERT_GE(hard5, hard1);
}

TEST(HardnessComparisons, Equal) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"t", 2, 10};

  ASSERT_TRUE(hard1 == hard1);
  ASSERT_TRUE(hard1 == hard2);
}

TEST(HardnessComparisons, NotEqual) {
  stats::Hardness hard1 = {"", 2, 10};
  stats::Hardness hard2 = {"", 2, 12};
  stats::Hardness hard3 = {"", 2, 8};
  stats::Hardness hard4 = {"", 1, 10};
  stats::Hardness hard5 = {"", 3, 10};

  std::vector<stats::Hardness> hards = {hard2, hard3, hard4, hard5};

  for (auto &hard : hards) {
    ASSERT_NE(hard1, hard);
  }
}

}  // namespace
