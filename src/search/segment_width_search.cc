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

#include "segment_width_search.h"

#include <cassert>
#include <memory>
#include <thread>
#include <vector>

#include "generate/generate_next.h"
#include "generate/generate_next_symmetric.h"
#include "helpers/manipulators.h"
#include "helpers/parallel/compute_parallel.h"
#include "helpers/parallel/reducers.h"
#include "helpers/verifiers.h"
#include "solve/predicate/width_check.h"
#include "solve/solution.h"

namespace search {

// Config type for each worker which requires the specification of the generator
// interface, predicate for exiting and converter for getting the appropriate
// word from the generator
//
// GenInterface must support GenerateNext and kErrorWord
//
// Predicate has the following signature where count is the number of cycled
// words:
// bool Predicate(int count);
//
// Converter takes in a word and a generator and converts to a string:
// std::string Converter(GenInterface, word);
template <typename GenInterface, typename Predicate, typename Converter>
struct Config {
  GenInterface generator;
  Predicate predicate;
  Converter converter;
  std::string first;
  std::string second;
  int n;
};

using Result = std::vector<std::string>;

template <typename GenInterface, typename Predicate, typename Converter>
void SearchWorker(
    std::shared_ptr<Config<GenInterface, Predicate, Converter>> config,
    std::shared_ptr<Result> result, int workers, int index) {
  // Start counter on index as index many words have been skipped over before
  // this worker got its generator
  int count{index};

  while (true) {
    count++;

    if (config->predicate(count)) break;

    auto num = config->generator.GenerateNext();

    if (num == config->generator.kErrorWord) break;

    // Skip over words for each worker for the next iteration
    for (int i{}; i < workers - 1; i++) {
      count++;
      config->generator.GenerateNext();
    }

    // Create full word then compare and record
    auto word = config->first + config->converter(config->generator, num) +
                config->second;
    auto full_word = helper::MirrorWord(word);
    auto double_word = full_word + full_word;

    assert(helper::VerifySymmetricHardWord(double_word));

    if (solve::predicate::SymmetricHardWordIsWidthAtLeastN(double_word,
                                                           config->n)) {
      result->push_back(double_word);
    }
  }
}

// Converter for generating full words from the interface. For half productions
// of words for the SymmetricGenerator, use PartialConverter
template <typename GenInterface, typename Word>
std::string DefaultConverter(GenInterface &gen, Word &w) {
  return gen.WordToDyck(w);
}

// Converter for SymmetricGenerator to only generate half the word for placement
// into words
template <typename GenInterface, typename Word>
std::string PartialConverter(GenInterface &gen, Word &w) {
  return gen.WordToHalfDyck(w);
}

// Generic helper for searching a segment with a predicate to setup the config
// generation and run the actual runner
//
// GenInterface must support GenerateNext and kErrorWord
//
// Predicate has the following signature where count is the number of cycled
// words:
// bool Predicate(int count);
//
// Converter takes in a word and a generator and converts to a string:
// std::string Converter(GenInterface, word);
template <typename GenInterface, typename Predicate, typename Converter>
Result SearchSegmentForWidthGeneral(std::string first, std::string second,
                                    GenInterface generator, int n,
                                    Predicate predicate, int workers,
                                    Converter converter) {
  auto config_gen = [&first, &second, &generator, &predicate, &converter,
                     &n](int i) -> Config<GenInterface, Predicate, Converter> {
    GenInterface gen = generator;

    for (int j{}; j < i; j++) {
      gen.GenerateNext();
    }

    return {gen, predicate, converter, first, second, n};
  };

  return helper::parallel::GenericParallelRunner<
      Result, Config<GenInterface, Predicate, Converter>>(
      SearchWorker<GenInterface, Predicate, Converter>, config_gen,
      helper::parallel::VectorReducer<std::string>, workers);
}

Result SearchSegmentForWidth(std::string first, std::string second, int size,
                             int n, int workers) {
  generate::Generator generator(size);

  return SearchSegmentForWidthGeneral<generate::Generator>(
      first, second, generator, n, [](int _) { return false; }, workers,
      DefaultConverter<generate::Generator, generate::Generator::Integer>);
}

Result PartialSearchSegmentForWidth(std::string first, std::string second,
                                    generate::Generator &generator, int width,
                                    int group_size, int workers) {
  // Stop iterating if the number of words processed is greater than the number
  // permitted by this partial search
  return SearchSegmentForWidthGeneral<generate::Generator>(
      first, second, generator, width,
      [group_size](int i) { return i > group_size; }, workers,
      DefaultConverter<generate::Generator, generate::Generator::Integer>);
}

Result SearchSymmetricSegmentForWidth(std::string first, std::string second,
                                      int size, int n, int workers) {
  generate::SymmetricGenerator generator(size);

  return SearchSegmentForWidthGeneral<generate::SymmetricGenerator>(
      first, second, generator, n, [](int _) { return false; }, workers,
      PartialConverter<generate::SymmetricGenerator,
                       generate::SymmetricGenerator::Integer>);
}

Result PartialSearchSymmetricSegmentForWidth(
    std::string first, std::string second,
    generate::SymmetricGenerator &generator, int width, int group_size,
    int workers) {
  // Stop iterating if the number of words processed is greater than the number
  // permitted by this partial search
  return SearchSegmentForWidthGeneral<generate::SymmetricGenerator>(
      first, second, generator, width,
      [group_size](int i) { return i > group_size; }, workers,
      PartialConverter<generate::SymmetricGenerator,
                       generate::SymmetricGenerator::Integer>);
}

}  // namespace search
