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

#include "random_sample_width.h"

#include <gtest/gtest.h>

namespace {

const int kSamples = 10003;
const int kSize = 15;
const int kWorkers = 4;

TEST(RandomUniformSampleWidths, CorrectNumberOfWords) {
  auto result = stats::RandomUniformSampleWidths(kSamples, kSize, 4);

  ASSERT_EQ(result.size(), 2);

  long total{};

  for (auto &res : result) {
    total += res;
  }

  ASSERT_EQ(total, kSamples);
}

TEST(RandomHardSampleWidths, CorrectNumberOfWords) {
  auto result = stats::RandomHardSampleWidths(kSamples, kSize, 4);

  ASSERT_EQ(result.size(), 2);

  long total{};

  for (auto &res : result) {
    total += res;
  }

  ASSERT_EQ(result[0], 0);
  ASSERT_EQ(total, kSamples);
}

TEST(RandomSymmetricSampleWidths, CorrectNumberOfWords) {
  auto result = stats::RandomSymmetricSampleWidths(kSamples, kSize, 4);

  ASSERT_EQ(result.size(), 2);

  long total{};

  for (auto &res : result) {
    total += res;
  }

  ASSERT_EQ(total, kSamples);
}

TEST(RandomSymmetricHardSampleWidths, CorrectNumberOfWords) {
  auto result =
      stats::RandomSymmetricHardSampleWidths(kSamples, kSize + (kSize % 2), 4);

  ASSERT_EQ(result.size(), 2);

  long total{};

  for (auto &res : result) {
    total += res;
  }

  ASSERT_EQ(result[0], 0);
  ASSERT_EQ(total, kSamples);
}

}  // namespace
