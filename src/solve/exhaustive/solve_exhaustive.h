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

#ifndef PROJECT_SOLVE_EXHAUSTIVE_SOLVE_EXHAUSTIVE_H_
#define PROJECT_SOLVE_EXHAUSTIVE_SOLVE_EXHAUSTIVE_H_

#include "solve/solution.h"

namespace solve {

// Exhaustively search through possible re-pairings to find the best without a
// limit on the size of the memo
Solution ExhaustiveSolve(const std::string &word);

// Exhaustively search through possible re-pairings to find the best with the
// solution being passed being treated as the best found so far without a
// limit on the size of the memo
Solution ExhaustiveSolve(const Solution &solution);

// Exhaustively search through possible re-pairings to find the best with a hard
// limit on the size of the memo
Solution ExhaustiveSolveLimitedMemo(const std::string &word);

// Exhaustively search through possible re-pairings to find the best with the
// solution being passed being treated as the best found so far with a hard
// limit on the size of the memo
Solution ExhaustiveSolveLimitedMemo(const Solution &solution);

// Exhaustively search through possible re-pairings to find the best with a
// period based usage of the memo to limit its usage but still without a limit
// on it
Solution ExhaustiveSolvePeriodMemo(const std::string &word);

// Exhaustively search through possible re-pairings to find the best with the
// solution being passed being treated as the best found so far with a
// period based usage of the memo to limit its usage but still without a limit
// on it
Solution ExhaustiveSolvePeriodMemo(const Solution &solution);

// Exhaustively solve across a range solving each and returning all solutions
template <typename Iter>
Solutions Solve(Iter begin, Iter end) {
  return Solver<ExhaustiveSolve>(begin, end);
}

}  // namespace solve

#endif
