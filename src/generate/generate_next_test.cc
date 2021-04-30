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

#include "generate_next.h"

#include <gtest/gtest.h>

#include <unordered_set>

#include "generate_all.h"

#define WORD_SIZE_LIMIT 15

namespace {

TEST(GenerateNextTests, WordToDyckToWordIdentity) {
  generate::Generator generator(WORD_SIZE_LIMIT);

  for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
       word = generator.GenerateNext()) {
    ASSERT_EQ(word, generator.DyckToWord(generator.WordToDyck(word)));
    ASSERT_EQ(
        generator.WordToDyck(word),
        generator.WordToDyck(generator.DyckToWord(generator.WordToDyck(word))));
  }
}

TEST(GenerateNextTests, DyckInitialisation) {
  generate::Generator generator(WORD_SIZE_LIMIT);

  for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
       word = generator.GenerateNext()) {
    std::string dyck = generator.WordToDyck(word);
    generate::Generator gen(dyck);
    auto tmp_word = gen.GenerateNext();
    ASSERT_EQ(tmp_word, word);
    ASSERT_EQ(dyck, gen.WordToDyck(tmp_word));
  }
}

TEST(GenerateNextTests, IsHardWordEven) {
  std::unordered_set<std::string> hard_words;

  auto words = generate::GenerateDynamic(5);

  for (auto word1 : words) {
    for (auto word2 : words) {
      hard_words.insert("(" + word1 + ")(" + word2 + ")");
    }
  }

  generate::Generator generator(12);

  for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
       word = generator.GenerateNext()) {
    std::string dyck = generator.WordToDyck(word);
    auto is_hard = hard_words.find(dyck) != hard_words.end();

    ASSERT_EQ(generator.IsHardWord(word), is_hard) << dyck;
  }
}

TEST(GenerateNextTests, IsHardWordOdd) {
  std::unordered_set<std::string> hard_words;

  auto words1 = generate::GenerateDynamic(5);
  auto words2 = generate::GenerateDynamic(6);

  for (auto word1 : words1) {
    for (auto word2 : words2) {
      hard_words.insert("(" + word1 + ")(" + word2 + ")");
    }
  }

  for (auto word2 : words2) {
    for (auto word1 : words1) {
      hard_words.insert("(" + word2 + ")(" + word1 + ")");
    }
  }

  generate::Generator generator(13);

  for (auto word = generator.GenerateNext(); word != generator.kErrorWord;
       word = generator.GenerateNext()) {
    std::string dyck = generator.WordToDyck(word);
    auto is_hard = hard_words.find(dyck) != hard_words.end();

    ASSERT_EQ(generator.IsHardWord(word), is_hard) << dyck;
  }
}

}  // namespace
