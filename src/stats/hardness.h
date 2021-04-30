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

#ifndef PROJECT_HARDNESS_HARDNESS_H_
#define PROJECT_HARDNESS_HARDNESS_H_

#include <string>

namespace stats {

// Result of calculating the hardness
struct Hardness {
  // The word hardness has been calculated for
  std::string word;
  // The width of the word
  int width;
  // The number of re-pairings of the significant length specified
  long hardness;
};

// h1 < h2 if the width of h1 is less than h2 or the number of re-pairings of h2
// is greater than the number by h1
bool operator<(const Hardness &h1, const Hardness &h2);
// Defined as h2 < h1
bool operator>(const Hardness &h1, const Hardness &h2);
// Defined as !(h1 > h2)
bool operator<=(const Hardness &h1, const Hardness &h2);
// Defined as !(h1 < h2)
bool operator>=(const Hardness &h1, const Hardness &h2);
// Defined as !(h1 > h2 || h1 < h2)
bool operator==(const Hardness &h1, const Hardness &h2);
// Defined as !(h1 == h2)
bool operator!=(const Hardness &h1, const Hardness &h2);

// Calculate the hardness of the passed word up to the significant length d
Hardness ComputeHardness(const std::string &word, int d);

}  // namespace stats

#endif
