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

#include "random_sample_width.h"

#include <algorithm>
#include <memory>

#include "generate/generate_random.h"
#include "generate/generate_random_hard.h"
#include "helpers/parallel/compute_parallel.h"
#include "solve/derived/derived_strategy.h"
#include "solve/exhaustive/solve_exhaustive.h"

namespace stats {

// Type for a generator of words
using Generator = std::string (*)(int size);

// Config for the worker
struct Config {
  // Number of samples for the worker to run
  int samples;
  // The size of the words to generate
  int size;
};

// Worker which generates the given amount of samples and records the results of
// each width
template <Generator WordGen>
void GenericSamplerWorker(std::shared_ptr<Config> config,
                          std::shared_ptr<SampleResults> result, int workers,
                          int worker) {
  result->resize(100);

  for (int i{}; i < config->samples; i++) {
    std::string word = WordGen(config->size);

    auto res = solve::derived::Solve(word);
    auto solution = solve::ExhaustiveSolvePeriodMemo(res);

    (*result)[solution.GetWidth() - 1]++;
  }
}

// Generic samples which, when given a word generation function, will sample
// using that generator across a number of threads with the given samples and
// size parameters, returning the collated results
template <Generator WordGen>
SampleResults GenericSampler(int samples, int size, int workers) {
  int samples_per_worker = samples / workers;
  int remaining = samples % samples_per_worker;

  auto config_gen = [&samples_per_worker, &remaining, &size](int i) -> Config {
    return {samples_per_worker + (i == 0 ? remaining : 0), size};
  };

  auto reducer = [](SampleResults& acc, const SampleResults& result) {
    for (size_t j{}; j < result.size(); j++) {
      acc[j] += result[j];
    }

    return acc;
  };

  auto result = helper::parallel::GenericParallelRunner<SampleResults, Config>(
      GenericSamplerWorker<WordGen>, config_gen, reducer, workers);

  // Reduce the result vector size as much as possible
  size_t max_size{};

  for (size_t i{}; i < result.size(); i++) {
    if (result[i] != 0) max_size = i + 1;
  }

  result.resize(max_size);

  return result;
}

SampleResults RandomUniformSampleWidths(int samples, int size) {
  return RandomUniformSampleWidths(samples, size, 1);
}

SampleResults RandomUniformSampleWidths(int samples, int size, int workers) {
  return GenericSampler<generate::RandomUniformWord>(samples, size, workers);
}

SampleResults RandomSymmetricSampleWidths(int samples, int size) {
  return RandomSymmetricSampleWidths(samples, size, 1);
}

SampleResults RandomSymmetricSampleWidths(int samples, int size, int workers) {
  return GenericSampler<generate::RandomSymmetricWord>(samples, size, workers);
}

SampleResults RandomHardSampleWidths(int samples, int size) {
  return RandomHardSampleWidths(samples, size, 1);
}

SampleResults RandomHardSampleWidths(int samples, int size, int workers) {
  return GenericSampler<generate::RandomHardWord>(samples, size, workers);
}

SampleResults RandomSymmetricHardSampleWidths(int samples, int size) {
  return RandomSymmetricHardSampleWidths(samples, size, 1);
}

SampleResults RandomSymmetricHardSampleWidths(int samples, int size,
                                              int workers) {
  return GenericSampler<generate::RandomSymmetricHardWord>(samples, size,
                                                           workers);
}

}  // namespace stats
