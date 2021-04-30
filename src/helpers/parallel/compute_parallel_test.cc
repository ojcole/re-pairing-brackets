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

#include "compute_parallel.h"

#include <gtest/gtest.h>

#include <memory>

namespace {

struct Config {
  int worker_id;
};

struct Result {
  int sum;
};

void Worker(std::shared_ptr<Config> config, std::shared_ptr<Result> result,
            int workers, int worker_id) {
  result->sum = worker_id + workers + config->worker_id;
}

Result Combiner(Result &result1, Result &result2) {
  return {result1.sum + result2.sum};
}

Config ConfigGen(int i) { return {i}; }

TEST(ComputeParallelTest, CorrectThreadCount) {
  for (int i{1}; i < 10; i++) {
    auto result = helper::parallel::GenericParallelRunner<Result, Config>(
        Worker, ConfigGen, Combiner, i);

    int expected = i * (2 * i - 1);
    EXPECT_EQ(expected, result.sum);
  }
}

}  // namespace
