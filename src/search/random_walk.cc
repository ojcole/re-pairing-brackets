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

#include "random_walk.h"

#include <cassert>
#include <random>

#include "helpers/constants.h"
#include "helpers/manipulators.h"
#include "helpers/parallel/compute_parallel.h"
#include "helpers/parallel/reducers.h"
#include "helpers/verifiers.h"
#include "solve/predicate/width_check.h"

namespace search {

// The random number generator to use
using RandGen = std::mt19937;

// Config for the parallel workers
struct Config {
  std::string word;
  int runs;
  int shuffles;
  int width;
};

using Result = std::vector<std::string>;

// Worker for the parallelised searching for a new shorter word
void ParallelWorker(std::shared_ptr<Config> config,
                    std::shared_ptr<Result> result, int workers, int index) {
  std::uniform_int_distribution<int> dist(2, config->word.size() / 4 - 1);
  std::random_device rd;
  RandGen gen(rd());
  for (int i{}; i < config->runs; i++) {
    auto new_word = config->word;
    // Get the first half of the symmetric hard word
    auto half_word = new_word.substr(0, new_word.size() / 4);

    // Randomly remove a bits
    auto num = dist(gen);
    half_word.erase(num, 1);

    std::uniform_int_distribution<int> dist1(2, half_word.size() - 1);

    // Perform some shuffling of the bits
    for (int i{}; i < config->shuffles; i++) {
      auto ch = dist1(gen);

      if (half_word[ch] == OPENING_BRACKET) {
        half_word[ch] = CLOSING_BRACKET;
      } else {
        half_word[ch] = OPENING_BRACKET;
      }
    }

    // Create and check the full word
    auto full_word = helper::MirrorWord(half_word);
    auto full_full = full_word + full_word;

    if (helper::VerifySymmetricHardWord(full_full)) {
      if (solve::predicate::SymmetricHardWordIsWidthAtLeastN(full_full,
                                                             config->width)) {
        result->push_back(full_full);
      }
    }
  }
}

Result SymmetricHardRandomWalkShorterWord(std::string word, int width,
                                          int shuffles, int runs, int workers) {
  assert(helper::VerifySymmetricHardWord(word));
  assert(word.size() / 4 - 2 > 2);

  // Config generator
  auto config_gen = [word, runs, shuffles, width](int i) -> Config {
    return {word, runs, shuffles, width};
  };

  return helper::parallel::GenericParallelRunner<Result, Config>(
      ParallelWorker, config_gen, helper::parallel::VectorReducer<std::string>,
      workers);
}

}  // namespace search
