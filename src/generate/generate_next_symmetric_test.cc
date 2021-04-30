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

#include "generate_next_symmetric.h"

#include <gtest/gtest.h>

#include <cassert>
#include <unordered_set>
#include <vector>

#include "helpers/constants.h"
#include "helpers/manipulators.h"
#include "helpers/n_choose_k.h"

namespace {

TEST(MaxWord, CorrectWord) {
  ASSERT_EQ(generate::SymmetricGenerator::MaxWord(6), 0b101010);
  ASSERT_EQ(generate::SymmetricGenerator::MaxWord(7), 0b1010101);
  ASSERT_EQ(generate::SymmetricGenerator::MaxWord(8), 0b10101010);
}

TEST(MinWord, CorrectWord) {
  ASSERT_EQ(generate::SymmetricGenerator::MinWord(6), 0b111111);
  ASSERT_EQ(generate::SymmetricGenerator::MinWord(7), 0b1111111);
  ASSERT_EQ(generate::SymmetricGenerator::MinWord(8), 0b11111111);
}

TEST(GenerateNext, AfterLastWordIsErrorEven) {
  generate::SymmetricGenerator gen("()()()()()()()()()()");
  auto err = generate::SymmetricGenerator::kErrorWord;

  // Clear the last word
  gen.GenerateNext();

  ASSERT_EQ(gen.GenerateNext(), err);
}

TEST(GenerateNext, AfterLastWordIsErrorOdd) {
  generate::SymmetricGenerator gen("()()()()()()()()()()()");
  auto err = generate::SymmetricGenerator::kErrorWord;

  // Clear the last word
  gen.GenerateNext();

  ASSERT_EQ(gen.GenerateNext(), err);
}

TEST(GenerateNext, StringPassingGivesAValidWord) {
  std::string initial{"()()()()()()()()()()()"};
  auto err = generate::SymmetricGenerator::kErrorWord;
  generate::SymmetricGenerator gen(initial);
  auto word = gen.GenerateNext();

  ASSERT_NE(word, err);
  ASSERT_EQ(gen.WordToDyck(word), initial);
}

TEST(GenerateNext, WordsAreUniqueEven) {
  std::unordered_set<generate::SymmetricGenerator::Integer> words;
  generate::SymmetricGenerator gen(10);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    ASSERT_EQ(words.find(w), words.end());

    words.insert(w);
  }
}

TEST(GenerateNext, WordsAreUniqueOdd) {
  std::unordered_set<generate::SymmetricGenerator::Integer> words;
  generate::SymmetricGenerator gen(11);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    ASSERT_EQ(words.find(w), words.end());

    words.insert(w);
  }
}

TEST(GenerateNext, CorrectWordSymbolsEven) {
  generate::SymmetricGenerator gen(10);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    auto word = gen.WordToDyck(w);

    for (auto ch : word) {
      ASSERT_TRUE(ch == OPENING_BRACKET || ch == CLOSING_BRACKET);
    }
  }
}

TEST(GenerateNext, CorrectWordSymbolsOdd) {
  generate::SymmetricGenerator gen(11);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    auto word = gen.WordToDyck(w);

    for (auto ch : word) {
      ASSERT_TRUE(ch == OPENING_BRACKET || ch == CLOSING_BRACKET);
    }
  }
}

TEST(GenerateNext, CorrectWordCountEven) {
  std::vector<generate::SymmetricGenerator::Integer> words;
  generate::SymmetricGenerator gen(10);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    words.push_back(w);
  }

  ASSERT_EQ(words.size(), helper::NChooseK(10, 5));
}

TEST(GenerateNext, CorrectWordCountOdd) {
  std::vector<generate::SymmetricGenerator::Integer> words;
  generate::SymmetricGenerator gen(11);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    words.push_back(w);
  }

  ASSERT_EQ(words.size(), helper::NChooseK(11, 5));
}

TEST(GenerateNext, WordsAreTheCorrectLengthEven) {
  generate::SymmetricGenerator gen(10);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    ASSERT_EQ(gen.WordToDyck(w).size(), 20);
  }
}

TEST(GenerateNext, WordsAreTheCorrectLengthOdd) {
  generate::SymmetricGenerator gen(11);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    ASSERT_EQ(gen.WordToDyck(w).size(), 22);
  }
}

TEST(GenerateNext, WordsAreValidEven) {
  generate::SymmetricGenerator gen(10);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    auto word = gen.WordToDyck(w);

    int depth{};

    for (auto ch : word) {
      if (ch == OPENING_BRACKET) depth++;
      if (ch == CLOSING_BRACKET) depth--;

      ASSERT_GE(depth, 0) << word;
    }
  }
}

TEST(GenerateNext, WordsAreValidOdd) {
  generate::SymmetricGenerator gen(11);

  for (auto w = gen.GenerateNext();
       w != generate::SymmetricGenerator::kErrorWord; w = gen.GenerateNext()) {
    auto word = gen.WordToDyck(w);

    int depth{};

    for (auto ch : word) {
      if (ch == OPENING_BRACKET) depth++;
      if (ch == CLOSING_BRACKET) depth--;

      ASSERT_GE(depth, 0) << word;
    }
  }
}

}  // namespace
