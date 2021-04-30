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

#include "obvious_moves.h"

#include "helpers/constants.h"

namespace solve {
namespace derived {

void MakeObviousMovesForward(Solution &solution) {
  // Case 1: ...(_)...
  // Case 2: ..._()...
  // Case 3: ...()_...
  int depth{};
  int open{};
  bool case1{false};
  bool case2{false};
  bool case3{false};

  for (size_t i{}; i < solution.GetWord().size(); i++) {
    const auto &word = solution.GetWord();
    if (word[i] == OPENING_BRACKET) {
      // Cases 1,3
      if (depth == 0) {
        // Case 2
        if (i == 0 || word[i - 1] == STRING_GAP) {
          case2 = true;
          open = i;
        } else {
          case2 = false;
        }

        case1 = true;
        case3 = true;
        open = i;
      } else {
        case1 = false;
        case2 = false;
        case3 = false;
      }
      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      if (depth == 1) {
        bool should_move{
            (case1 && word[i - 1] == STRING_GAP) ||
            (case3 && (i == word.size() - 1 || word[i + 1] == STRING_GAP)) ||
            case2};
        if (should_move) solution.PairOff(open, i);
      }

      depth--;
    }
  }
}

void MakeObviousMovesBackward(Solution &solution) {
  // Case 1: ...)_(...
  // Case 2: ..._)(...
  // Case 3: ...)(_...
  int depth{};
  int close{};
  bool case1{false};
  bool case2{false};
  bool case3{false};
  int last_index = static_cast<int>(solution.GetWord().size()) - 1;

  for (int i = last_index; i >= 0; i--) {
    const auto &word = solution.GetWord();
    if (word[i] == CLOSING_BRACKET) {
      // Cases 1,3
      if (depth == 0) {
        // Case 2
        if (i == last_index || word[i + 1] == STRING_GAP) {
          case2 = true;
          close = i;
        } else {
          case2 = false;
        }

        case1 = true;
        case3 = true;
        close = i;
      } else {
        case1 = false;
        case2 = false;
        case3 = false;
      }
      depth++;
    } else if (word[i] == OPENING_BRACKET) {
      if (depth == 1) {
        bool should_move{(case1 && word[i + 1] == STRING_GAP) ||
                         (case3 && (i == 0 || word[i - 1] == STRING_GAP)) ||
                         case2};

        if (should_move) solution.PairOff(i, close);
      }
      depth--;
    }
  }
}

void MakeObviousBlockMoves(Solution &solution) {
  // Case: .._((^n)^n)_...

  std::vector<int> opening_indicies;
  std::vector<int> closing_indicies;
  bool opening{true};
  bool case1{false};
  int depth{};

  for (size_t i{}; i < solution.GetWord().size(); i++) {
    const auto &word = solution.GetWord();

    // Track all the opening brackets and closing when we are matching this
    // pattern
    if (word[i] == OPENING_BRACKET) {
      if (depth == 0 && (i == 0 || word[i - 1] == STRING_GAP)) {
        opening_indicies.clear();
        closing_indicies.clear();
        opening_indicies.push_back(i);
        opening = true;
        case1 = true;
      } else if (depth == 0 || !opening) {
        case1 = false;
      } else {
        opening_indicies.push_back(i);
      }

      depth++;
    } else if (word[i] == CLOSING_BRACKET) {
      opening = false;
      closing_indicies.push_back(i);
      bool empty_after = i == word.size() - 1 || word[i + 1] == STRING_GAP;

      // If we are at the end of the match then pair from out to in
      if (depth == 1 && case1 && empty_after) {
        auto size = opening_indicies.size();
        for (size_t j{}; j < size; j++) {
          solution.PairOff(opening_indicies[j], closing_indicies[size - 1 - j]);
        }
      }
      depth--;
    }
  }
}

}  // namespace derived
}  // namespace solve
