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

#include "minimise_width.h"

#include <algorithm>
#include <random>
#include <unordered_map>
#include <unordered_set>

#include "helpers/traversal.h"
#include "solve/derived/derived_strategy.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/predicate/width_check.h"

namespace solve {
namespace minimise {

std::string MinimiseSymmetricHardWidth(const std::string &word, int width) {
  return MinimiseSymmetricHardWidth(word, width, 0);
}

std::string MinimiseSymmetricHardWidth(const std::string &word, int width,
                                       size_t begin) {
  std::vector<size_t> indicies;

  for (size_t i{begin}; i < word.size() / 4; i++) {
    indicies.push_back(i);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  // Shuffle the indices
  std::shuffle(indicies.begin(), indicies.end(), gen);

  return MinimiseSymmetricHardWidth(word, width, 0, indicies);
}

std::string MinimiseSymmetricHardWidth(const std::string &word, int width,
                                       size_t begin,
                                       std::vector<size_t> &indicies) {
  std::string half_word = word.substr(1, word.size() / 2 - 2);
  std::string first_half = half_word.substr(0, half_word.size() / 2);
  std::unordered_set<std::string> memo;

  for (size_t x{begin}; x < indicies.size(); x++) {
    size_t i = indicies[x];
    if (i >= first_half.size()) continue;

    std::string cpy = first_half;

    // If its in the first half, erase it from the copy. Otherwise just erase
    // the first one
    if (first_half[i] == OPENING_BRACKET) {
      auto closing = helper::ClosingBracket(first_half, i);

      if (closing < first_half.size()) {
        cpy.erase(closing - 1, 1);
      }
    }
    cpy.erase(i, 1);

    // If cpy has already been checked, don't check it again
    if (memo.find(cpy) != memo.end()) {
      continue;
    }

    memo.insert(cpy);

    std::string result{cpy};

    // Mirror and duplicate the word
    result.resize(cpy.size() * 2);

    for (size_t i{}; i < cpy.size(); i++) {
      auto c = OPENING_BRACKET;
      if (result[i] == OPENING_BRACKET) {
        c = CLOSING_BRACKET;
      }

      result[cpy.size() * 2 - 1 - i] = c;
    }

    std::string full = "(" + result + ")(" + result + ")";

    // Test
    auto res = predicate::SymmetricHardWordIsWidthAtLeastN(full, width);

    if (res) {
      memo.clear();
      return MinimiseSymmetricHardWidth(full, width, x, indicies);
    }
  }

  // If we have made changes, start again to ensure none were missed
  if (indicies.size() != word.size() / 4) {
    indicies.clear();
    return MinimiseSymmetricHardWidth(word, width);
  }

  return word;
}

std::string MinimiseWidth(const std::string &word, int width) {
  // Enumerate every pair
  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      auto close = helper::ClosingBracket(word, i);
      std::string cpy = word;

      cpy.erase(i, 1);
      cpy.erase(close - 1, 1);

      auto solution = ExhaustiveSolvePeriodMemo(cpy);

      if (solution.GetWidth() >= width) {
        return MinimiseWidth(cpy, width);
      }
    }
  }

  return word;
}

}  // namespace minimise
}  // namespace solve
