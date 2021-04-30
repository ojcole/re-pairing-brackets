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

#include "manual_search.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

#include "generate/generate_next.h"
#include "helpers/constants.h"
#include "helpers/manipulators.h"
#include "helpers/traversal.h"
#include "helpers/verifiers.h"
#include "solve/predicate/width_check.h"

namespace manual {

void SaveWord(const std::string &word, std::string file) {
  std::ofstream stream(file);

  stream << word << std::endl;
}

void SaveWords(const std::vector<std::string> &words, std::string file) {
  std::ofstream stream(file);

  for (auto word : words) {
    stream << word << std::endl;
  }
}

std::string LoadWord(std::string file) {
  std::ifstream handle(file);
  std::stringstream stream;

  if (handle.is_open()) {
    stream << handle.rdbuf();
    handle.close();
  }

  auto word = stream.str();

  // Clear final newlines
  if (!word.empty() && word[word.size() - 1] == '\n') {
    word.pop_back();
  }

  return word;
}

std::vector<std::string> LoadWords(std::string file) {
  std::ifstream handle(file);
  std::vector<std::string> result;
  std::string line;

  // Get a word per line
  if (handle.is_open()) {
    while (std::getline(handle, line)) {
      result.push_back(line);
    }
  }

  return result;
}

std::string LoadHalfWord(std::string file) {
  std::string word = LoadWord(file);

  return word + word;
}

std::string LoadSpreadWord(std::string file) {
  std::string word = LoadWord(file);

  return helper::CompressWord(word);
}

std::string LoadSpreadHalfWord(std::string file) {
  std::string word = LoadHalfWord(file);

  return helper::CompressWord(word);
}

// Helper to pad the strings in a vector with spaces for viewing
std::vector<std::string> PadStrings(std::vector<std::string> strings) {
  for (auto &s : strings) {
    s = "  " + s;
  }

  return strings;
}

// Helper for recursive calls for spreading a symmetric hard word. Returns a
// vector of words where each word consists of many lines. We only create a new
// block when there is more than one word on the next level
std::vector<std::vector<std::string>> SpreadSymmetricHardWordPrime(
    std::string word) {
  // Base case
  if (word.size() == 0) return {};

  std::vector<std::vector<std::string>> result;

  size_t i{};
  while (i < word.size()) {
    auto closing_i = helper::ClosingBracket(word, i);
    auto middle = word.substr(i + 1, closing_i - i - 1);

    // Get the words of the substring
    auto words = SpreadSymmetricHardWordPrime(middle);

    // If there are no deeper words then its simply (). If there is a single
    // then a new break should not be formed. Otherwise we pad the word
    if (words.size() == 0) {
      result.push_back({"()"});
    } else if (words.size() == 1) {
      words[0].front() = "(" + words[0][0];
      words[0].back() += ")";

      result.push_back(words[0]);
    } else {
      std::vector<std::string> new_words{"("};

      for (auto w : words) {
        // Pad each of the smaller words to indent the next layer
        w = PadStrings(w);
        new_words.insert(new_words.end(), w.begin(), w.end());
      }

      new_words.push_back(")");

      result.push_back(new_words);
    }

    // Next opening must be the next bracket or we have reached the end of the
    // word as the depth at each i is 0
    i = closing_i + 1;
  }

  return result;
}

std::string SpreadSymmetricHardWord(std::string word) {
  word = helper::CompressWord(word);

  assert(helper::VerifySymmetricHardWord(word));

  word = word.substr(0, word.size() / 2);

  // Spread and then save the word as a string
  auto words = SpreadSymmetricHardWordPrime(word);

  std::stringstream stream;

  for (auto w : words) {
    for (auto line : w) {
      stream << line << std::endl;
    }
  }

  auto w = stream.str();

  // Remove the final newline character
  return w.substr(0, w.size() - 1);
}

bool SymmetricHardWordWidthAtLeastN(std::string file, int n) {
  auto word = LoadSpreadHalfWord(file);

  assert(helper::VerifySymmetricHardWord(word));

  return solve::predicate::SymmetricHardWordIsWidthAtLeastN(word, n);
}

}  // namespace manual
