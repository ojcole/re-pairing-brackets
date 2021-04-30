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

#ifndef PROJECT_SOLVE_CHISTIKOV_SOLVE_CHISTIKOV_H_
#define PROJECT_SOLVE_CHISTIKOV_SOLVE_CHISTIKOV_H_

#include <string>
#include <vector>

#include "solve/solution.h"

namespace solve {

// Find a solution to a word using the method specified by Chistikov et al. in
// https://dl.acm.org/doi/10.1145/3373718.3394752
Solution SolveChistikov(const std::string &word);
// Find a solution to a word using the method specified by Chistikov et al. in
// https://dl.acm.org/doi/10.1145/3373718.3394752 with a given memo for
// recording results already known
Solution SolveChistikovMemo(const std::string &word, SolutionMemo &memo);

// Given a range of words, solve all of them returning the solutions to them all
// reusing the same memo between runs to avoid excess computation
template <typename Iter>
std::vector<Solution> ChistikovSolves(Iter begin, Iter end) {
  SolutionMemo memo;
  return MemoSolver<SolutionMemo, SolveChistikovMemo>(begin, end, memo);
}

}  // namespace solve

#endif
