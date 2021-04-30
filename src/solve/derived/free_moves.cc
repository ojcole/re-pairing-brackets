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

#include "free_moves.h"

#include <algorithm>
#include <vector>

#include "helpers/constants.h"

namespace solve {
namespace derived {

void MakeFreeMoves(Solution &solution) {
  // Case 1: ...(_)...
  // Case 2: ...()_...
  // Case 3: ..._()...
  bool case1{false};
  bool case2{false};
  bool case3{false};

  std::vector<size_t> open_idxs;
  open_idxs.reserve(solution.GetWord().size() / 2);

  for (size_t i{}; i < solution.GetWord().size(); i++) {
    const auto &word = solution.GetWord();

    if (word[i] == OPENING_BRACKET) {
      // If the next is a gap then the next closing bracket produces case 1
      if (word[i + 1] == STRING_GAP) {
        case1 = true;
      } else {
        case1 = false;
      }

      // If the previous is a gap then the next being a closing bracket
      // produces case 3
      if (i == 0 || word[i - 1] == STRING_GAP) {
        case3 = true;
      } else {
        case3 = false;
      }

      // For any we need to look after the closing bracket to use case 2
      case2 = true;

      // Track open indexes for moving backward for any moves opened up
      open_idxs.push_back(i);
    } else if (word[i] == CLOSING_BRACKET) {
      // Case 1 is captured by the first ||, case2 by the second, case3 by the
      // third
      bool should_move{
          (case1 && word[i - 1] == STRING_GAP) ||
          (case2 && (i == word.size() - 1 || word[i + 1] == STRING_GAP)) ||
          case3};

      // If we make a move we then need to also move just before the last
      // opening bracket so that the increment places on it so that we can
      // reconsider it now that it may have been opened up by the move just
      // performed
      if (should_move) {
        solution.PairOff(open_idxs.back(), i);
        open_idxs.pop_back();
        if (!open_idxs.empty()) {
          i = open_idxs.back() - 1;
          open_idxs.pop_back();
        }
      }

      case1 = false;
      case2 = false;
      case3 = false;
    }
  }
}

}  // namespace derived
}  // namespace solve
