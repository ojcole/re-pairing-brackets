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

#ifndef PROJECT_SOLVE_DERIVED_OBVIOUS_MOVES_H_
#define PROJECT_SOLVE_DERIVED_OBVIOUS_MOVES_H_

#include "solve/solution.h"

namespace solve {
namespace derived {

// Eliminate obvious moves at depth 0. This is done separately to free moves
// as it must occur at depth 0 and the optimisations used can't be applied
//
// Case 1: ...(_)...
// Case 2: ..._()...
// Case 3: ...()_...
void MakeObviousMovesForward(Solution &solution);

// Eliminate obvious moves at depth 0. This is done separately to free moves
// as it must occur at depth 0 and the optimisations used can't be applied.
// This performs the same algorithm as above in the opposite direction. As
// this is taking place at depth 0, it can be seen that one pass in each
// direction covers all cases. The cases below show the progression backwards
// (in the iterating order)
//
// Case 1: ...)_(...
// Case 2: ..._)(...
// Case 3: ...)(_...
void MakeObviousMovesBackward(Solution &solution);

// Eliminate blocks which can be removed at the cost of no extra width. These
// match: ..._((^n)^n)_...
void MakeObviousBlockMoves(Solution &solution);

}  // namespace derived
}  // namespace solve

#endif
