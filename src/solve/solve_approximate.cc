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

#include "solve_approximate.h"

#include "helpers/solutions/combine_solutions.h"
#include "solve/derived/derived_strategy.h"
#include "solve/greedy/solve_greedy.h"
#include "solve/greedy/solve_simple_greedy.h"

namespace solve {

Solution SolveApproximate(const std::string &word) {
  auto greedy_simple_sol = SolveSimpleGreedy(word);

  // Very little is gained below 80 from the other methods
  if (word.size() <= 80 || greedy_simple_sol.GetWidth() <= 2)
    return greedy_simple_sol;

  auto greedy_sol = SolveGreedy(word);

  // Very little is gained below 150 from derived
  if (word.size() <= 150 || greedy_sol.GetWidth() <= 2)
    return helper::BestSol({greedy_simple_sol, greedy_sol});

  auto derived_sol = derived::Solve(word);

  return helper::BestSol({derived_sol, greedy_simple_sol, greedy_sol});
}

}  // namespace solve
