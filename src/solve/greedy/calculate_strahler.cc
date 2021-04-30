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

#include "calculate_strahler.h"

#include <algorithm>
#include <memory>
#include <vector>

#include "solve/solution.h"

namespace solve {

// Tree node for representing the word
struct TreeNode {
  std::vector<std::unique_ptr<TreeNode>> children;
};

// Create the tree for the word
std::unique_ptr<TreeNode> CreateTree(const std::string &word) {
  auto root = std::make_unique<TreeNode>();

  // Build a stack to construct the tree
  std::vector<std::unique_ptr<TreeNode>> current_stack;
  current_stack.push_back(std::move(root));

  for (size_t i{}; i < word.size(); i++) {
    if (word[i] == OPENING_BRACKET) {
      current_stack.push_back(std::make_unique<TreeNode>());
    } else if (word[i] == CLOSING_BRACKET) {
      auto back = std::move(current_stack.back());
      current_stack.pop_back();
      current_stack.back()->children.push_back(std::move(back));
    }
  }

  return std::move(current_stack.front());
}

int CalculateWordStrahler(
    const std::vector<std::unique_ptr<TreeNode>> &children) {
  // If there are no children then the number is 1
  if (children.size() == 0) {
    return 1;
  }

  // If there is a single child, don't increase the width
  if (children.size() == 1) {
    return CalculateWordStrahler(children.front()->children);
  }

  // Calculate the number of maximums and the maximum and the number of min
  // children
  int num_max{};
  int max_num{};
  size_t num_min_children{};

  for (auto &child : children) {
    auto num = CalculateWordStrahler(child->children);
    auto c_children = child->children.size();

    if (c_children == 0) {
      num_min_children++;
    }

    if (num == max_num) {
      num_max++;
    } else if (num > max_num) {
      num_max = 1;
      max_num = num;
    }
  }

  // If the number of max is 1 then we don't increase the number at all
  // If the maximum number is 1 then we don't increase the number at all so long
  // as each of these are () besides 1. If more than 1 is not () then it
  // increases the width to 2
  return (num_max == 1 ||
          (max_num == 1 && num_min_children >= children.size() - 1))
             ? max_num
             : max_num + 1;
}

int CalculateWordStrahler(const std::string &word) {
  auto root = CreateTree(word);
  return CalculateWordStrahler(root->children);
}

}  // namespace solve
