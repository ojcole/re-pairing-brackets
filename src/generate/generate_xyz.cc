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

#include <cassert>
#include <cmath>

#include "solve/solution.h"

namespace generate {

// Separate recursive call to ensure that a copy is only made once
std::string GenerateXR(std::vector<int> &xs) {
  std::string begin(xs.back(), OPENING_BRACKET);
  std::string end(xs.back(), CLOSING_BRACKET);

  // Base case
  if (xs.size() == 1) {
    return begin + end;
  }

  // Set the value as defined by https://dl.acm.org/doi/10.1145/3373718.3394752
  xs.pop_back();
  std::string recursed = GenerateX(xs);

  return begin + recursed + recursed + end;
}

std::string GenerateX(std::vector<int> xs) {
  assert(xs.size() > 0);

  return GenerateXR(xs);
}

std::string GenerateZ(int n) { return GenerateY(1, n); }

std::string GenerateY(int l) {
  return GenerateY(static_cast<int>(floor(l * log2(l))), l);
}

std::string GenerateY(int m, int l) {
  std::vector<int> nums;

  // Construct the vector of values
  // https://dl.acm.org/doi/10.1145/3373718.3394752
  for (int i{}; i < m * l; i++) {
    auto ai = static_cast<int>(pow(2, floor(i / l)));

    nums.push_back(ai);
  }

  return GenerateX(nums);
}

}  // namespace generate
