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

#include "generate_test_helpers.h"

#include <vector>

#include "helpers/constants.h"

namespace generate {
namespace test {

std::optional<std::string> ValidWordOfLengthN(const std::string &word, int n) {
  int size = static_cast<int>(word.size());

  // Checks the length is correct
  if (size % 2 != 0) return "Odd length word is invalid";
  if (size / 2 != n) return "Word is not of length n";

  int depth{};

  // Ensure that the characters are correct and that depth remains positive
  for (int i{}; i < size; i++) {
    if (word[i] != OPENING_BRACKET && word[i] != CLOSING_BRACKET) {
      return "Invalid character " + word[i];
    }

    if (word[i] == OPENING_BRACKET) {
      depth++;
    } else {
      depth--;

      if (depth < 0) {
        return "Word contains negative depth";
      }
    }
  }

  // Ensure the final depth is 0
  if (depth != 0) {
    return "Final word depth is non-zero";
  }

  return std::nullopt;
}

}  // namespace test
}  // namespace generate
