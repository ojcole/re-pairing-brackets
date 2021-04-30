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

#ifndef PROJECT_SOLVE_PARALLEL_PARALLEL_WORKER_H_
#define PROJECT_SOLVE_PARALLEL_PARALLEL_WORKER_H_

#include <memory>

#include "generate/generate_next.h"
#include "result.h"

namespace solve {
namespace parallel {

// The type of a parallel worker to be used for solving in parallel
using Worker = void (*)(std::shared_ptr<generate::Generator> generator,
                        std::shared_ptr<Result> result, int workers,
                        int worker);

// A worker that generates words using its generator and captures the count of
// one and two width, storing all other words
void SolveWorkerLazy(std::shared_ptr<generate::Generator> generator,
                     std::shared_ptr<Result> result, int workers, int worker);

// A worker that generates only Hard words using its generator and captures the
// count of one and two width, storing all other words
void SolveWorkerMinimal(std::shared_ptr<generate::Generator> generator,
                        std::shared_ptr<Result> result, int workers,
                        int worker);

// A worker that generates and saves solutions to all words outputted from its
// generator
void SolveWorkerCollect(std::shared_ptr<generate::Generator> generator,
                        std::shared_ptr<Result> result, int workers,
                        int worker);

}  // namespace parallel
}  // namespace solve

#endif
