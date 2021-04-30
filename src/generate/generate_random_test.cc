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

#include "generate_random.h"

#include <gtest/gtest.h>

#include <unordered_map>

#include "helpers/verifiers.h"

namespace {

TEST(RandomGenerateTest, UniformRandomTest) {
  for (int i{}; i < 100000; i++) {
    std::string word = generate::RandomUniformWord(1000);

    ASSERT_EQ(word.size(), 2000) << word;
    ASSERT_TRUE(helper::VerifyWord(word)) << word;
  }
}

TEST(RandomGenerateTest, UniformRandomUniformityTest) {
  std::unordered_map<std::string, int> counts;
  for (int i{}; i < 1000000; i++) {
    std::string word = generate::RandomUniformWord(100);

    ASSERT_EQ(word.size(), 200) << word;
    ASSERT_LT(counts[word], 3) << i;
    counts[word]++;
  }
}

TEST(RandomGenerateTest, SymmetricRandomTest) {
  for (int i{}; i < 100000; i++) {
    std::string word = generate::RandomSymmetricWord(1000);

    ASSERT_EQ(word.size(), 2000) << word;
    ASSERT_TRUE(helper::VerifyWord(word)) << word;
    ASSERT_TRUE(helper::VerifySymmetricWord(word)) << word;
  }
}

}  // namespace
