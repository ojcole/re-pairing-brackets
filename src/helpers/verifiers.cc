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

#include "verifiers.h"

#include <cmath>
#include <vector>

#include "constants.h"
#include "manipulators.h"

namespace helper {

bool VerifySymmetricWord(std::string word) {
  if (!VerifyWord(word)) return false;

  auto compressed = CompressWord(word);

  for (size_t i{}; i < compressed.size() / 2; i++) {
    char c = OPENING_BRACKET;

    if (compressed[i] == OPENING_BRACKET) {
      c = CLOSING_BRACKET;
    }

    if (compressed[compressed.size() - i - 1] != c) return false;
  }

  return true;
}

bool VerifySymmetricHardWord(std::string word) {
  if (!VerifyWord(word)) return false;

  auto first_half = word.substr(0, word.size() / 2);
  auto second_half = word.substr(word.size() / 2);

  return first_half == second_half && VerifySymmetricWord(first_half);
}

bool VerifyWord(const std::string &word) {
  int depth{};

  for (auto c : word) {
    if (c == OPENING_BRACKET) {
      depth++;
    } else if (c == CLOSING_BRACKET) {
      depth--;
    } else if (c != STRING_GAP) {
      return false;
    }

    if (depth < 0) return false;
  }

  return depth == 0;
}

bool VerifyHardWord(std::string word) {
  if (!VerifyWord(word)) return false;

  word = CompressWord(word);

  std::vector<size_t> sizes{};

  int depth{};

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      depth--;
      if (depth == 0) {
        sizes.push_back(i);
      }
    }
  }

  if (sizes.size() != 2) return false;

  long mid = sizes[0] + 1;

  return abs(mid - (static_cast<long>(word.size()) - mid)) <= 2;
}

}  // namespace helper
