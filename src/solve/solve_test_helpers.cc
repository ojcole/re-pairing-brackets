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

#include "solve_test_helpers.h"

#include <optional>
#include <set>
#include <string>
#include <utility>

#include "solve/solution.h"

std::optional<std::string> ValidRepairing(
    const solve::Solution::Repairing &repairing, const std::string &word) {
  const int kWordLength = static_cast<int>(word.size());

  std::set<int> indices;

  for (const auto &pair : repairing) {
    if (pair.first >= pair.second) return "First is after second";
    if (pair.first < 0) return "First is negatively out of bounds";
    if (pair.second >= kWordLength) return "Second is positively out of bounds";
    if (indices.find(pair.first) != indices.end())
      return "First has already been used";
    if (indices.find(pair.second) != indices.end())
      return "Second has already been used";
    if (word[pair.first] != OPENING_BRACKET)
      return "First of pair is not an opening bracket";
    if (word[pair.second] != CLOSING_BRACKET)
      return "Second of pair is not a closing bracket";

    indices.insert(pair.first);
    indices.insert(pair.second);
  }

  return std::nullopt;
}

std::optional<std::string> ValidSolution(solve::Solution solution) {
  std::string word = solution.GetInitialWord();
  solve::Solution::Repairing repairing = solution.GetRepairing();
  const int kWordLength = static_cast<int>(word.size());
  int pairs = kWordLength / 2;

  if (static_cast<int>(repairing.size()) != pairs)
    return "Incorrect number of pairs";

  return ValidRepairing(repairing, word);
}

// Helper to generate all simple pairs for an initial word
std::set<std::pair<int, int>> SimplePairs(const std::string &word) {
  std::set<std::pair<int, int>> pairs;
  std::vector<int> stack;

  for (int i{}; i < static_cast<int>(word.size()); i++) {
    if (word[i] == OPENING_BRACKET) {
      stack.push_back(i);
    } else {
      int j = stack.back();
      stack.pop_back();

      pairs.insert({j, i});
    }
  }

  return pairs;
}

bool IsSimpleRepairing(solve::Solution solution) {
  std::set<std::pair<int, int>> pairs = SimplePairs(solution.GetInitialWord());

  for (auto pair : solution.GetRepairing()) {
    if (pairs.find(pair) == pairs.end()) return false;
  }

  return true;
}
