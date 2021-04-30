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

#include "generate_all.h"

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "generate_next.h"
#include "generate_next_symmetric.h"
#include "helpers/catalan.h"
#include "helpers/constants.h"

namespace generate {

// A partial Dyck word used for generating Dyck words by building them up
struct PartialDyckWord {
  // The length of the word
  int length;
  // The word itself being built up
  std::string word;
  // The height at the last position in the word
  int score;
};

const size_t kPreallocationLimit = 100000000UL;

using DyckGenerationMemo = std::vector<std::vector<std::string>>;

std::vector<std::string> GenerateSimple(int length) {
  if (length == 0) return {""};

  // The length is passed as n whereas words have length 2*n
  auto double_length = length * 2;

  std::string base;

  base.resize(double_length);
  base[0] = OPENING_BRACKET;

  std::vector<PartialDyckWord> collection{{1, base, 1}};

  // Iterate through each point in the length, updating the collection including
  // new words that are still valid partial words. We set length initially to
  // improve efficiency. The final step will have all words requiring a closing
  // bracket so that is performed separately for efficiency
  for (int i = double_length - 1; i > 1; i--) {
    std::vector<PartialDyckWord> new_collection;

    for (PartialDyckWord &word : collection) {
      if (word.score > 0) {
        // We can avoid memory allocation be reusing the memory used by the
        // string so long as we will not use it later
        if (word.score >= i) {
          word.score--;
          word.word[word.length] = CLOSING_BRACKET;
          word.length++;
          new_collection.push_back(std::move(word));
          continue;
        }

        PartialDyckWord new_word = word;
        new_word.score--;
        new_word.word[new_word.length] = CLOSING_BRACKET;
        new_word.length++;
        new_collection.push_back(std::move(new_word));
      }

      // We will not use the memory beyond this point so we simply reuse this
      // memory
      if (word.score < i) {
        word.score++;
        word.word[word.length] = OPENING_BRACKET;
        word.length++;
        new_collection.push_back(std::move(word));
      }
    }

    collection = std::move(new_collection);
  }

  // Assing the closing brackets to all
  std::vector<std::string> result;

  // Preallocate as much as possible
  auto cat = helper::CalculateNthCatalanNumber(length);
  result.reserve(std::min(cat, kPreallocationLimit));

  for (auto &s : collection) {
    s.word[double_length - 1] = CLOSING_BRACKET;
    result.push_back(std::move(s.word));
  }

  return result;
}

// Runner for the memoed version of simple generation returning words of a
// specific length
std::vector<std::string> GenerateMemoedRunner(DyckGenerationMemo &memo,
                                              int length) {
  std::string base;

  // Resize to the correct length now to reduce memory allocations
  base.resize(length);
  base[0] = OPENING_BRACKET;

  PartialDyckWord minimal_word{1, base, 1};

  std::vector<PartialDyckWord> collection{minimal_word};
  std::vector<std::string> final_collection{};

  // Preallocate as much as possible (the length is doubled before being passed)
  auto cat = helper::CalculateNthCatalanNumber(length / 2);
  final_collection.reserve(std::min(cat, kPreallocationLimit));

  for (int i = length - 1; i > 1; i--) {
    std::vector<PartialDyckWord> new_collection;

    // There will be zero scores iff i is even
    if (i % 2 == 0 && memo[i / 2].size() == 0) {
      memo[i / 2] = std::move(GenerateMemoedRunner(memo, i));
    }

    for (PartialDyckWord &word : collection) {
      if (word.score == 0) {
        // In the case where the height at the end position is zero we can use
        // stored values to fill out the remaining word
        const auto &words = memo[i / 2];

        for (const auto &small_word : words) {
          auto cpy = word.word;
          cpy.replace(word.length, i, small_word);

          final_collection.push_back(std::move(cpy));
        }

        memo[i / 2] = std::move(words);

        continue;
      }

      if (word.score > 0) {
        // Check if we can reuse the allocation of the word without making a new
        // one
        if (word.score >= i) {
          word.score--;
          word.word[word.length] = CLOSING_BRACKET;
          word.length++;
          new_collection.push_back(std::move(word));

          continue;
        }

        PartialDyckWord new_word = word;

        new_word.score--;
        new_word.word[new_word.length] = CLOSING_BRACKET;
        new_word.length++;

        new_collection.push_back(std::move(new_word));
      }

      // The allocation will not be used beyond this point so we can reuse it
      if (word.score < i) {
        word.score++;
        word.word[word.length] = OPENING_BRACKET;
        word.length++;

        new_collection.push_back(std::move(word));
      }
    }

    collection = std::move(new_collection);
  }

  // Assign the final closing bracket and add to the final collection
  for (auto &s : collection) {
    s.word[length - 1] = CLOSING_BRACKET;
    final_collection.push_back(std::move(s.word));
  }

  return final_collection;
}

std::vector<std::string> GenerateMemoed(int length) {
  if (length == 0) return {""};

  // Create the memo and set the correct length
  DyckGenerationMemo memo;
  memo.resize(length + 1);

  length *= 2;

  return GenerateMemoedRunner(memo, length);
}

std::vector<std::string> GenerateDynamic(int length) {
  std::vector<std::string> seq[length + 1];
  seq[0] = {""};

  for (int i = 1; i <= length; i++) {
    // Preallocate as much as possible
    auto cat = helper::CalculateNthCatalanNumber(length);
    seq[i].reserve(std::min(cat, kPreallocationLimit));

    // Every word can be built from taking all lengths, wrapping one side in
    // brackets then adding the other end
    for (int j = i; j > 0; j--) {
      auto &base = seq[j - 1];
      auto &rem = seq[i - j];

      for (auto &str1 : base) {
        for (auto &str2 : rem) {
          seq[i].push_back(OPENING_BRACKET + str1 + CLOSING_BRACKET + str2);
        }
      }
    }
  }

  return seq[length];
}

std::vector<std::string> GenerateConstant(int length) {
  if (length == 0) return {""};

  // Preallocate as much as possible
  std::vector<std::string> words;
  auto cat = helper::CalculateNthCatalanNumber(length);
  words.reserve(std::min(cat, kPreallocationLimit));

  // Iterate through the words generated
  auto generator = Generator(length);

  for (auto num = generator.GenerateNext();
       num != generate::Generator::kErrorWord; num = generator.GenerateNext()) {
    words.push_back(generator.WordToDyck(num));
  }

  return words;
}

std::vector<std::string> GenerateSymmetric(int length) {
  if (length == 0) return {""};

  std::vector<std::string> words;

  // Preallocate as much as possible
  auto cat = helper::CalculateNthCatalanNumber(length);
  words.reserve(std::min(cat, kPreallocationLimit));

  // Iterate through the words generated
  auto generator = SymmetricGenerator(length);

  for (auto num = generator.GenerateNext();
       num != generate::SymmetricGenerator::kErrorWord;
       num = generator.GenerateNext()) {
    words.push_back(generator.WordToDyck(num));
  }

  return words;
}

// Helper for performing the swapping procedure
// Details for the algorithm found here: https://arxiv.org/pdf/1002.2625.pdf
void GenerateSwapping(const std::string &word, int index,
                      std::vector<std::string> &storage) {
  storage.push_back(word);
  int size = static_cast<int>(word.size()) - 1;
  while (index < size) {
    int j = 0;
    for (int i{index}; i < size; i++) {
      if (word[i] == CLOSING_BRACKET && word[i + 1] == OPENING_BRACKET) {
        j = i;
        break;
      }
    }

    if (j > 0) {
      std::string new_word = word;
      new_word[j] = OPENING_BRACKET;
      new_word[j + 1] = CLOSING_BRACKET;
      GenerateSwapping(new_word, j - 1, storage);
      index = j + 2;
    } else {
      break;
    }
  }
}

std::vector<std::string> GenerateSwapping(int length) {
  std::vector<std::string> result;

  // Preallocate as much as possible
  auto cat = helper::CalculateNthCatalanNumber(length);
  result.reserve(std::min(cat, kPreallocationLimit));

  std::string starting_word;
  starting_word.resize(length * 2);

  // Begin with ()()()()()...
  for (int i{}; i < length; i++) {
    starting_word[2 * i] = OPENING_BRACKET;
    starting_word[2 * i + 1] = CLOSING_BRACKET;
  }

  GenerateSwapping(starting_word, 1, result);

  return result;
}

}  // namespace generate
