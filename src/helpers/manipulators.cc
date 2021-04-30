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

#include "manipulators.h"

#include <cassert>
#include <vector>

#include "constants.h"

namespace helper {

std::string CompressWord(const std::string &word) {
  std::string out;

  // Simply remove any character that isn't an open or close bracket
  for (auto c : word) {
    if (c == OPENING_BRACKET || c == CLOSING_BRACKET) {
      out += c;
    }
  }

  return out;
}

std::pair<std::string, std::string> SplitAtX(const std::string &word, char x) {
  auto s = word.find(x);

  // Split and compress at the first instance of the character x
  std::string first = CompressWord(word.substr(0, s));
  std::string second = CompressWord(word.substr(s + 1));

  return {first, second};
}

std::string StripWord(const std::string &word) {
  std::string out;
  std::string part;
  bool start{true};

  // Remove any trailing characters from both ends of the word retaining any
  // chars in the middle of the string
  for (auto c : word) {
    if (c == OPENING_BRACKET || c == CLOSING_BRACKET) {
      out += part;
      out += c;
      start = false;
      part.clear();
    } else {
      if (!start) {
        part += c;
      }
    }
  }

  return out;
}

std::string MirrorWord(std::string word) {
  auto size = word.size();
  word.resize(size * 2);

  // Set the reflected for each index assuming that all chars are correct.
  // Invalid chars will lead to an invalid word
  for (size_t i{}; i < size; i++) {
    char c = OPENING_BRACKET;
    if (word[i] == OPENING_BRACKET) {
      c = CLOSING_BRACKET;
    }

    word[word.size() - 1 - i] = c;
  }

  return word;
}

}  // namespace helper
