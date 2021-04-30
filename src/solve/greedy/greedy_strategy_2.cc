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

#include "greedy_strategy_2.h"

#include <string>

#include "helpers/constants.h"
#include "solve/solution.h"

namespace solve {
namespace greedy2 {

int ScoreOpenIndex(const std::string &word, int index, int depth) {
  const int kWordSize = static_cast<int>(word.size());
  int score{};

  if (index == 0 || word[index - 1] == STRING_GAP) {
    // If the next is a closing bracket and the previous character is a gap then
    // its the best choice
    if (word[index + 1] == CLOSING_BRACKET) {
      return 100;
    }

    score += 2;
  }

  if (word[index + 1] == STRING_GAP) {
    score++;
  }

  if (word[index + 1] == CLOSING_BRACKET &&
      (index == kWordSize - 2 || word[index + 2] == STRING_GAP)) {
    // If the next is a closing bracket and the char after that is a space then
    // it is treated as ideal
    return 100;
  }

  if (word[index + 1] == CLOSING_BRACKET) {
    score++;
  }

  return score;
}

int ScoreCloseIndex(const std::string &word, int open_index, int index,
                    int depth) {
  const int kWordSize = static_cast<int>(word.size());
  int score{};

  if (open_index + 1 == index) {
    score += 2;
  }

  if (index == kWordSize - 1 || word[index + 1] == STRING_GAP) {
    score++;
  }

  return score;
}

}  // namespace greedy2
}  // namespace solve
