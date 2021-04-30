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

#include "parallel_worker.h"

#include "generate/generate_next.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/solution.h"

namespace solve {
namespace parallel {

// Type of how solutions should be combined into results
using Handler = void (*)(std::shared_ptr<Result> &result,
                         const Solution &solution);

// General helper for solving which takes in a handler and a checker to see if
// the word should be counted and how the solution should be saved
template <typename Checker>
void SolveWorker(std::shared_ptr<generate::Generator> &generator,
                 std::shared_ptr<Result> result, int workers, int worker,
                 Handler SolHandle, Checker WordChecker) {
  while (true) {
    auto num = generator->GenerateNext();

    if (num == generate::Generator::kErrorWord) break;

    // Skip over the next few words as they are processed by other workers
    for (int i{}; i < workers - 1; i++) {
      generator->GenerateNext();
    }

    if (WordChecker(num)) {
      auto word = generator->WordToDyck(num);

      Solution solution = ExhaustiveSolve(word);

      SolHandle(result, std::move(solution));
    }
  }
}

// Helper which specifies an always truthy checker
void SolveWorker(std::shared_ptr<generate::Generator> &generator,
                 std::shared_ptr<Result> result, int workers, int worker,
                 Handler SolHandle) {
  return SolveWorker(generator, result, workers, worker, SolHandle,
                     [](generate::Generator::Integer _) { return true; });
}

void SolveWorkerLazy(std::shared_ptr<generate::Generator> generator,
                     std::shared_ptr<Result> result, int workers, int worker) {
  SolveWorker(generator, result, workers, worker,
              [](std::shared_ptr<Result> &result, const Solution &solution) {
                int width = solution.GetWidth();

                if (width > 2) {
                  result->other.push_back(std::move(solution));
                } else if (width == 2) {
                  result->two_count++;
                } else {
                  result->one_count++;
                }
              });
}

void SolveWorkerMinimal(std::shared_ptr<generate::Generator> generator,
                        std::shared_ptr<Result> result, int workers,
                        int worker) {
  SolveWorker(
      generator, result, workers, worker,
      [](std::shared_ptr<Result> &result, const Solution &solution) {
        int width = solution.GetWidth();

        if (width > 2) {
          result->other.push_back(std::move(solution));
        } else if (width == 2) {
          result->two_count++;
        } else {
          result->one_count++;
        }
      },
      [&generator](generate::Generator::Integer word) {
        return generator->IsHardWord(word);
      });
}

void SolveWorkerCollect(std::shared_ptr<generate::Generator> generator,
                        std::shared_ptr<Result> result, int workers,
                        int worker) {
  // Store all values in other so we can keep all solutions
  SolveWorker(generator, result, workers, worker,
              [](std::shared_ptr<Result> &result, const Solution &solution) {
                result->other.push_back(std::move(solution));
              });
}

}  // namespace parallel
}  // namespace solve
