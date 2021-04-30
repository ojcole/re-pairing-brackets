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

#ifndef PROJECT_GENERATE_GENERATE_NEXT_H_
#define PROJECT_GENERATE_GENERATE_NEXT_H_

#include <cassert>
#include <string>

#include "helpers/verifiers.h"

namespace generate {

class Generator {
 public:
  using Integer = uint64_t;

  // Construct a generator based on length. This can generate full words of
  // length * 2
  Generator(int length)
      : kLength(length),
        kMinWord(MinWord(kLength)),
        kMaxWord(MaxWord(kLength)),
        current(kMinWord) {}

  // Construct a generator starting at a specific word. This will generate words
  // from this point onwards of the same length as the passed word. The internal
  // representation uses 64 bits so words must be passed with length less than
  // this
  Generator(const std::string &word)
      : kLength(static_cast<int>(word.size()) / 2),
        kMinWord(MinWord(kLength)),
        kMaxWord(MaxWord(kLength)),
        current(DyckToWord(word)) {
    assert(word.size() % 2 == 0);
    assert(word.size() <= 64);
    assert(helper::VerifyWord(word));
  }

  // Generates the next full word in the sequence returning it. Once there are
  // no more new words to return, kErrorWord will be returned
  Integer GenerateNext();

  // Given a word created by the generator, get the corresponding generated word
  std::string WordToDyck(Integer word);

  // Given a word created by the generator, test if it is a hard word
  bool IsHardWord(Integer word);

  // The value to be returned when there are no more new words
  static const Integer kErrorWord = 0UL;

  // The first word in the sequence with the smallest numeric value (10)^n
  static Integer MinWord(int length);

  // The last word in the sequence with the largest numeric value 1^n0^n
  static Integer MaxWord(int length);

  // Given a Dyck string word convert it to its Integer counterpart. This menas
  // that words longer than 64 bits are not accepted
  static Integer DyckToWord(const std::string &dyck);

 private:
  // Half length of the words generated
  const int kLength;
  // The minimum word for the specified length
  const Integer kMinWord;
  // The maximum word for the specified length
  const Integer kMaxWord;
  // The current word stored
  Integer current;
};

}  // namespace generate

#endif
