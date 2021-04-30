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

#include "reducers.h"

#include <gtest/gtest.h>

#include <random>
#include <vector>

namespace {

const int kRuns = 10000;

TEST(VectorReducerTest, CombinesVectors) {
  std::vector<int> vec1{1, 67, 8, 9, 3};
  std::vector<int> vec2{6, 7, 8, 8, 3};

  std::vector<int> expected{1, 67, 8, 9, 3, 6, 7, 8, 8, 3};

  EXPECT_EQ(helper::parallel::VectorReducer(vec1, vec2), expected);
}

TEST(VectorReducerTest, EmptyVectorRetainsSameVector) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist;
  std::vector<int> empty;

  for (int i{}; i < kRuns; i++) {
    std::vector<int> vec;

    for (int j{}; j < 100; j++) {
      auto val = dist(gen);

      vec.push_back(val);
    }

    empty.clear();
    ASSERT_EQ(helper::parallel::VectorReducer(vec, empty), vec);

    empty.clear();
    ASSERT_EQ(helper::parallel::VectorReducer(empty, vec), vec);
  }
}

TEST(FirstNonEmpty, BothEmptyStaysEmpty) {
  std::string empty{""};
  EXPECT_EQ(helper::parallel::FirstNonEmpty(empty, empty), empty);
}

TEST(FirstNonEmpty, NonEmptyMaintained) {
  std::string non_empty{"awdjhfhasdjf"};
  std::string other{"ahsdfhj"};

  EXPECT_EQ(helper::parallel::FirstNonEmpty(non_empty, other), non_empty);
}

TEST(FirstNonEmpty, ReplacedIfEmpty) {
  std::string empty{""};
  std::string other{"ahsdfhj"};

  EXPECT_EQ(helper::parallel::FirstNonEmpty(empty, other), other);
}

}  // namespace
