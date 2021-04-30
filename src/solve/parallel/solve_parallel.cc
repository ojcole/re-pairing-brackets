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

#include "solve_parallel.h"

#include <memory>
#include <vector>

#include "generate/generate_next.h"
#include "helpers/parallel/compute_parallel.h"
#include "parallel_worker.h"
#include "result.h"

namespace solve {
namespace parallel {

Result SolveLazy(int length) { return SolveGeneral(length, SolveWorkerLazy); }
Result SolveLazy(int length, int workers) {
  return SolveGeneral(length, workers, SolveWorkerLazy);
}
Result SolveLazy(generate::Generator generator) {
  return SolveGeneral(generator, SolveWorkerLazy);
}
Result SolveLazy(generate::Generator generator, int workers) {
  return SolveGeneral(generator, workers, SolveWorkerLazy);
}

Result SolveMinimal(int length) {
  return SolveGeneral(length, SolveWorkerMinimal);
}
Result SolveMinimal(int length, int workers) {
  return SolveGeneral(length, workers, SolveWorkerMinimal);
}
Result SolveMinimal(generate::Generator generator) {
  return SolveGeneral(generator, SolveWorkerMinimal);
}
Result SolveMinimal(generate::Generator generator, int workers) {
  return SolveGeneral(generator, workers, SolveWorkerMinimal);
}

Solutions SolveCollect(int length) { return SolveCollect(length, 1); }
Solutions SolveCollect(int length, int workers) {
  auto generator = generate::Generator(length);

  return SolveCollect(generator, workers);
}
Solutions SolveCollect(generate::Generator generator) {
  return SolveCollect(generator, 1);
}
Solutions SolveCollect(generate::Generator generator, int workers) {
  auto result = SolveGeneral(generator, workers, SolveWorkerCollect);

  return result.other;
}

Result SolveGeneral(int length, Worker ParallelWorker) {
  return SolveGeneral(length, 1, ParallelWorker);
}
Result SolveGeneral(int length, int workers, Worker ParallelWorker) {
  auto generator = generate::Generator(length);

  return SolveGeneral(generator, workers, ParallelWorker);
}
Result SolveGeneral(generate::Generator generator, Worker ParallelWorker) {
  return SolveGeneral(generator, 1, ParallelWorker);
}

// Method for combining the results
inline Result CombineResults(Result &accumulator, Result &next) {
  accumulator.one_count += next.one_count;
  accumulator.two_count += next.two_count;
  accumulator.other.insert(accumulator.other.end(),
                           std::make_move_iterator(next.other.begin()),
                           std::make_move_iterator(next.other.end()));

  return accumulator;
}

Result SolveGeneral(generate::Generator generator, int workers,
                    Worker ParallelWorker) {
  return helper::parallel::GenericParallelRunner<Result, generate::Generator>(
      ParallelWorker,
      [&generator](int i) {
        // Offset generators by the workers count to generate different words on
        // each worker
        generate::Generator gen = generator;
        for (int j{}; j < i; j++) {
          gen.GenerateNext();
        }

        return gen;
      },
      CombineResults, workers);
}

}  // namespace parallel
}  // namespace solve
