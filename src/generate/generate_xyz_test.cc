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

#include "generate_xyz.h"

#include <gtest/gtest.h>

#include <cmath>
#include <random>
#include <vector>

#include "helpers/verifiers.h"

namespace {

TEST(RelationshipConstraints, Z_nWithY_1_n) {
  const int kN = 30;

  for (int n{1}; n < kN; n++) {
    auto z = generate::GenerateZ(n);
    auto y = generate::GenerateY(1, n);
    ASSERT_EQ(z, y) << "n: " << n;
  }
}

TEST(RelationshipConstraints, Y_m_lWithX_a0_aml) {
  const int kM = 4;
  const int kL = 10;

  for (int m{1}; m < kM; m++) {
    for (int l{1}; l < kL; l++) {
      auto y = generate::GenerateY(m, l);

      std::vector<int> xs;

      for (int a{}; a <= m * l - 1; a++) {
        auto ai = pow(2, a / l);

        xs.push_back(ai);
      }

      auto x = generate::GenerateX(xs);

      ASSERT_EQ(x, y) << "m: " << m << " l:" << l;
    }
  }
}

TEST(RelationshipConstraints, Y_lWithY_m_l) {
  const int kL = 4;

  for (int l{2}; l < kL; l++) {
    int llog_l = static_cast<int>(floor(l * log2(l)));

    auto y1 = generate::GenerateY(l);
    auto y2 = generate::GenerateY(llog_l, l);

    ASSERT_EQ(y1, y2) << "l: " << l;
  }
}

TEST(GenerateX, ValidWord) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 3);
  for (int i{}; i < 1000; i++) {
    std::vector<int> xs;
    auto len = i % 25 + 1;

    for (int j{}; j < len; j++) {
      xs.push_back(dist(gen));
    }

    auto word = generate::GenerateX(xs);
    ASSERT_TRUE(helper::VerifyWord(word));
  }
}

}  // namespace
