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

#include "catalan.h"

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(CatalanNumbers, StaticAmount) {
  // Expected
  // Credit to OEIS A000108

  std::vector<size_t> expected{1,
                               1,
                               2,
                               5,
                               14,
                               42,
                               132,
                               429,
                               1430,
                               4862,
                               16796,
                               58786,
                               208012,
                               742900,
                               2674440,
                               9694845,
                               35357670,
                               129644790,
                               477638700,
                               1767263190,
                               6564120420,
                               24466267020,
                               91482563640,
                               343059613650,
                               1289904147324,
                               4861946401452,
                               18367353072152,
                               69533550916004,
                               263747951750360,
                               1002242216651368,
                               3814986502092304};

  for (size_t i{}; i < expected.size(); i++) {
    ASSERT_EQ(helper::CalculateNthCatalanNumber(i), expected[i]);
  }
}

}  // namespace
