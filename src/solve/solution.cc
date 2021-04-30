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

#include "solution.h"

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helpers/constants.h"

namespace solve {

// Calculate the size of the word as the number of brackets. This also checks if
// all characters are correct
int CalculateWordSize(const std::string& word) {
  size_t size{};
  for (auto& ch : word) {
    if (ch == OPENING_BRACKET || ch == CLOSING_BRACKET) {
      size++;
    } else {
      assert(ch == STRING_GAP);
    }
  }

  return size;
}

Solution::Solution(std::string word) : Solution::Solution(word, 0) {}
Solution::Solution(std::string word, int offset) : Solution(word, 1, offset) {}
Solution::Solution(std::string word, int width, int offset)
    : word(word),
      word_size(CalculateWordSize(word)),
      width(width),
      max_width(width),
      actual_max_width(INT_MIN),
      offset(offset) {
  repairing.reserve(word.size() / 2);
}

Solution Solution::BadSolution(std::string word) {
  Solution sol(word, INT_MAX, 0);
  sol.actual_max_width = INT_MAX;

  return sol;
}

void Solution::PairOff(int left, int right) {
  assert(word[left] == OPENING_BRACKET);
  assert(word[right] == CLOSING_BRACKET);

  auto change = RecalculateWidthRemoval(word, left, right);

  PairOffWithDiff(left, right, change);
}

void Solution::PairOffWithDiff(int left, int right, int diff) {
  assert(word[left] == OPENING_BRACKET);
  assert(word[right] == CLOSING_BRACKET);

  word[left] = STRING_GAP;
  word[right] = STRING_GAP;

  // If the width changes then we update the actual different value
  if (diff != 0) {
    width += diff;
    max_width = std::max(max_width, width);
    actual_max_width = std::max(actual_max_width, width);
  }

  // Add both to the solution
  repairing.push_back(left);
  repairing.push_back(right);
}

void Solution::PairOffSolution(const Solution& sol) {
  int offset = sol.GetOffset();
  for (int i{1}; i < static_cast<int>(sol.repairing.size()); i += 2) {
    PairOff(sol.repairing[i - 1] + offset, sol.repairing[i] + offset);
  }
}

void Solution::Undo(int prev_width, int prev_max, int number) {
  for (int i{}; i < number; i++) {
    int second = repairing.back();
    repairing.pop_back();
    word[second] = CLOSING_BRACKET;

    int first = repairing.back();
    repairing.pop_back();
    word[first] = OPENING_BRACKET;
  }

  width = prev_width;
  max_width = prev_max;
}

void Solution::Undo(int prev_width, int prev_max) {
  Undo(prev_width, prev_max, 1);
}

void Solution::SetOffset(int offset) { this->offset = offset; }

int Solution::GetOffset() const { return this->offset; }

Solution::width_size Solution::GetWidth() { return this->max_width; }
const Solution::width_size Solution::GetWidth() const {
  return this->max_width;
};

void Solution::AddWidth(width_size num) { this->max_width += num; }

const Solution::width_size Solution::GetActualWidth() const {
  return actual_max_width;
}

Solution::width_size Solution::GetCurrentWidth() { return this->width; }

const size_t Solution::GetRepairingVectorSize() const {
  return repairing.size();
}

const Solution::Repairing Solution::GetRepairing() const {
  Solution::Repairing repairing;
  for (int i{1}; i < static_cast<int>(this->repairing.size()); i += 2) {
    repairing.push_back({this->repairing[i - 1], this->repairing[i]});
  }

  return repairing;
}

const Solution::RepairingVector Solution::GetRepairingVector() const {
  return repairing;
}

const std::string Solution::GetInitialWord() const {
  // We can reconstruct the original word from the current state and the current
  // state of the re-pairing
  std::string word(this->word);
  for (auto pair : this->GetRepairing()) {
    word[pair.first] = '(';
    word[pair.second] = ')';
  }

  return word;
}

std::string Solution::GetWord() { return this->word; }
const std::string& Solution::GetWord() const { return this->word; }

bool Solution::IsComplete() { return word_size <= repairing.size(); }

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  for (int i = 0; i < static_cast<int>(sol.repairing.size()); i += 2) {
    std::cout << "(" << sol.repairing[i] << ", " << sol.repairing[i + 1]
              << ") ";
  }

  return os;
}

bool operator==(const Solution& lhs, const Solution& rhs) {
  return lhs.GetInitialWord() == rhs.GetInitialWord() &&
         lhs.repairing == rhs.repairing && lhs.max_width == rhs.max_width;
}

bool operator<(const Solution& lhs, const Solution& rhs) {
  return std::tie(lhs.GetInitialWord(), lhs.repairing, lhs.max_width) <
         std::tie(rhs.GetInitialWord(), rhs.repairing, rhs.max_width);
}

}  // namespace solve
