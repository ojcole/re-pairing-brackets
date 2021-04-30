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

#include "n_choose_k.h"

#include <gtest/gtest.h>

namespace {

TEST(NChooseK, NChooseZero) {
  for (int i{}; i < 50; i++) {
    ASSERT_EQ(helper::NChooseK(i, 0), 1);
  }
}

TEST(NChooseK, NChooseN) {
  for (int i{}; i < 50; i++) {
    ASSERT_EQ(helper::NChooseK(i, i), 1);
  }
}

TEST(NChooseK, N2ChooseN) {
  std::vector<long> results{1,    2,     3,     6,     10,    20,    35,
                            70,   126,   252,   462,   924,   1716,  3432,
                            6435, 12870, 24310, 48620, 92378, 184756};
  int size = static_cast<int>(results.size());

  for (int i{1}; i <= size; i++) {
    ASSERT_EQ(helper::NChooseK(i, i / 2), results[i - 1]);
  }
}

}  // namespace
