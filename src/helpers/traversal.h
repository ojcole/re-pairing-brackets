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

#ifndef PROJECT_HELPERS_TRAVERSAL_H_
#define PROJECT_HELPERS_TRAVERSAL_H_

#include <string>

#include "constants.h"

namespace helper {

// Gets the closing bracket associated with the opening bracket at the location
// passed
inline size_t ClosingBracket(const std::string &word, size_t opening) {
  int depth{};
  for (; opening < word.size(); opening++) {
    if (word[opening] == OPENING_BRACKET) {
      depth++;
    } else if (word[opening] == CLOSING_BRACKET) {
      depth--;
      if (depth == 0) return opening;
    }
  }

  return opening;
}

// Get the previous non space char
inline int PrevChar(const std::string &word, size_t c_char) {
  int prev = c_char - 1;
  for (; prev >= 0; prev--) {
    if (word[prev] != STRING_GAP) return prev;
  }

  return -1;
}

// Gets the next non space char location
inline size_t NextChar(const std::string &word, size_t c_char) {
  c_char++;
  for (; c_char < word.size(); c_char++) {
    if (word[c_char] != STRING_GAP) break;
  }

  return c_char;
}

}  // namespace helper

#endif
