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

#include <vector>

namespace helper {

size_t CalculateNthCatalanNumber(size_t n) {
  // Store precomputed values for efficiency
  constexpr size_t pre_computed[] = {
      1,       1,       2,        5,         14,        42,         132,
      429,     1430,    4862,     16796,     58786,     208012,     742900,
      2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420};

  if (n <= 20) return pre_computed[n];

  // Use the recurrence for Catalan numbers to calculate it exactly
  std::vector<size_t> elems{1};

  for (size_t i{1}; i <= n; i++) {
    size_t total{};

    for (size_t j{}; j < i; j++) {
      total += elems[j] * elems[i - 1 - j];
    }

    elems.push_back(total);
  }

  return elems.back();
}

}  // namespace helper
