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

#ifndef PROJECT_SOLVE_SOLUTION_H_
#define PROJECT_SOLVE_SOLUTION_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "helpers/constants.h"

namespace solve {

// Class representing a partial or complete solution for a word. A solution is
// comprised of: the word the solution is for, a re-pairing of the word, and the
// width of the re-pairing
class Solution {
 public:
  // Aliases for the types used for width and repairings
  using width_size = int;
  using Repairing = std::vector<std::pair<width_size, width_size>>;
  using RepairingVector = std::vector<width_size>;

  // Default constructor with a word
  Solution(std::string w);
  // Constructor taking an offset which is used when this solution is being used
  // to pair off another
  Solution(std::string w, int offset);

  // A solution with the worst possible width and actual width
  static Solution BadSolution(std::string word);

  // Pair off an opening and closing bracket and update width
  void PairOff(int left, int right);
  // Pair off an opening and closing bracket and use diff to update width
  void PairOffWithDiff(int left, int right, int diff);
  // Use the moves of sol offset by sol's offset and make them in this solution
  void PairOffSolution(const Solution& sol);
  // Get the current overall width of the re-pairing
  width_size GetWidth();
  // Get the current overall width of the re-pairing
  const width_size GetWidth() const;
  // Add width to the overall width of the re-pairing
  void AddWidth(width_size num);
  // Get the instantaneous width of the partial word
  width_size GetCurrentWidth();
  // Get the re-pairing held within the solution
  const Repairing GetRepairing() const;
  // Get the vector representation of the re-pairing not paired
  const RepairingVector GetRepairingVector() const;
  // Get the size of the internal re-pairing vector
  const size_t GetRepairingVectorSize() const;
  // Get the current partially re-paired word
  std::string GetWord();
  // Get reference to the current partially re-paired word
  const std::string& GetWord() const;
  // Get the initial word before moves were made
  const std::string GetInitialWord() const;
  // Get the actual width of the word. This is calculated as the maximum width
  // increase during the re-pairing
  const width_size GetActualWidth() const;
  // Get the offset of the solution
  int GetOffset() const;
  // Set the offset of the solution
  void SetOffset(int offset);
  // Returns true if the solution is complete (the word is completely re-paired)
  bool IsComplete();

  // Undo the last "number" moves that were made with prev_width reflecting the
  // previous width and prev_max reflecting the previous maximum width
  void Undo(int prev_width, int prev_max, int number);
  // Undo the last move that was made with prev_width reflecting the previous
  // width and prev_max reflecting the previous maximum width
  void Undo(int prev_width, int prev_max);

 private:
  // Private constructor setting the width. Default value is 1
  Solution(std::string word, int width, int offset);
  // Internal representation of the word
  std::string word;
  // The size of the word stored ignoring spaces
  size_t word_size;
  // Internal representation of the current width of the word
  width_size width;
  // Internal representation of the width of the re-pairing
  width_size max_width;
  // Internal representation of the actual width change after an actual change
  width_size actual_max_width;
  // Internal representation of the re-pairing vector
  RepairingVector repairing;
  // Offset of the solution
  int offset;
  // Helper for displaying the solution as its re-pairing
  friend std::ostream& operator<<(std::ostream& os, const Solution& sol);
  // Helper for testing equality of solutions
  friend bool operator==(const Solution& lhs, const Solution& rhs);
  // Helper for testing if a solution is less than another
  friend bool operator<(const Solution& lhs, const Solution& rhs);
};

// Calculate the change in width in word caused by removing the given open and
// closing brackets
inline int RecalculateWidthRemoval(const std::string& word, int left,
                                   int right) {
  // Initially assume the worst case
  int score = 2;

  // Test each case independently which could cause changes in width as:
  // ..._(...
  // ...()...
  // ...(_...)...
  // ...(..._)...
  // ...)_...
  if (left == 0 || word[left - 1] == STRING_GAP) {
    score--;
  }
  if (left + 1 == right) {
    score--;
  } else {
    if (word[left + 1] == STRING_GAP) {
      score--;
    }
    if (word[right - 1] == STRING_GAP) {
      score--;
    }
  }
  if (right == static_cast<int>(word.size()) - 1 ||
      word[right + 1] == STRING_GAP) {
    score--;
  }

  return score;
}

// Types for memos of solutions and results of batch solution solving
using SolutionMemo = std::map<std::string, Solution>;
using Solutions = std::vector<Solution>;

// Helper for creating a batch solver taking in a range and an algorithm which
// then applies the algorithm to each of the words in the range
template <typename solve::Solution (*SingleSolver)(const std::string& word),
          typename Iter>
inline Solutions Solver(Iter begin, Iter end) {
  Solutions solutions;

  for (; begin != end; begin++) {
    Solution sol = SingleSolver(*begin);

    solutions.push_back(sol);
  }

  return solutions;
}

// Helper for creating a batch solver which can make use of a memo for
// remembering results taking in a range and an algorithm which then applies the
// algorithm to each of the words in the range maintaing the same memo across
// all runs
template <typename Memo,
          typename solve::Solution (*SingleSolver)(const std::string& word,
                                                   Memo& memo),
          typename Iter>
Solutions MemoSolver(Iter begin, Iter end, Memo& memo) {
  Solutions solutions;

  for (; begin != end; begin++) {
    Solution sol = SingleSolver(*begin, memo);

    solutions.push_back(sol);
  }

  return solutions;
}

}  // namespace solve

#endif
