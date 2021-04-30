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

#ifndef PROJECT_SOLVE_GREEDY_GREEDY_STRATEGY_1_H_
#define PROJECT_SOLVE_GREEDY_GREEDY_STRATEGY_1_H_

#include <string>

namespace solve {
namespace greedy1 {

// Calculate the score of the opening bracket at index in the word with depth
int ScoreOpenIndex(const std::string &word, int index, int depth);

// Calculate the score of the closing bracket at index in the word with depth
// with the corresponding open bracket index
int ScoreCloseIndex(const std::string &word, int open_index, int index,
                    int depth);

}  // namespace greedy1
}  // namespace solve

#endif
