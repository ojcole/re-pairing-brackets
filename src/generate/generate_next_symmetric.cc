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

#include <cassert>
#include <cmath>
#include <string>

#include "helpers/constants.h"

namespace generate {

// Helper for checking if the internal value is a valid symmetric half word. The
// input word should use the 1 for '(' and 0 for ')' representation and the
// number of bits used should be passed
bool ValidSymmetricHalfWord(SymmetricGenerator::Integer word, int bits) {
  int depth{};

  SymmetricGenerator::Integer mask{1};

  // Mask out individual bits
  mask = mask << (bits - 1);

  // Check each bits value by masking it and then count the depth based on this
  for (long i{}; i < bits; i++) {
    auto val = word & mask;

    if (val == 0) {
      depth--;
    } else {
      depth++;
    }

    if (depth < 0) return false;

    mask = mask >> 1;
  }

  return depth >= 0;
}

SymmetricGenerator::Integer SymmetricGenerator::GenerateNext() {
  // If the current is the error word we just want to give that back
  if (current == kErrorWord) return current;

  auto curr = current;

  // If we are at the last word then set the next word to be the error word,
  // otherwise iterate to the next valid word
  if (current <= kMaxWord) {
    current = kErrorWord;
  } else {
    while (!ValidSymmetricHalfWord(--current, kLength))
      ;
  }

  // Return the value that we set at the start. This avoids skipping over the
  // first or last
  return curr;
}

SymmetricGenerator::Integer SymmetricGenerator::MinWord(int length) {
  int x{};

  // Create 1^n
  for (int i{}; i < length - 1; i++) {
    x++;
    x = x << 1;
  }

  x++;

  return x;
}

SymmetricGenerator::Integer SymmetricGenerator::MaxWord(int length) {
  int x{};

  // Create (10)^(n/2)
  for (int i{}; i < length - 1; i += 2) {
    x++;
    x = x << 2;
  }

  // If length is odd add the final 1 or remove the extra shift
  if (length % 2 == 1) {
    x++;
  } else {
    x = x >> 1;
  }

  return x;
}

std::string SymmetricGenerator::WordToDyck(Integer word) {
  const int N = kLength * 2;
  std::string output;

  output.resize(N);

  // We are iterating backwards and so have to mirror the word from the middle
  // outwards at each step. This is performed by checking the last digit
  for (int i{}; i < kLength; i++) {
    if (word % 2 == 0) {
      output[kLength - 1 - i] = CLOSING_BRACKET;
      output[kLength + i] = OPENING_BRACKET;
    } else {
      output[kLength - 1 - i] = OPENING_BRACKET;
      output[kLength + i] = CLOSING_BRACKET;
    }

    word = word >> 1;
  }

  return output;
}

std::string SymmetricGenerator::WordToHalfDyck(Integer word) {
  std::string output;

  output.resize(kLength);

  // We are iterating backwards by checking the last digit and then shifting to
  // the next
  for (int i{}; i < kLength; i++) {
    if (word % 2 == 0) {
      output[kLength - 1 - i] = CLOSING_BRACKET;
    } else {
      output[kLength - 1 - i] = OPENING_BRACKET;
    }

    word = word >> 1;
  }

  return output;
}

SymmetricGenerator::Integer SymmetricGenerator::DyckToWord(
    const std::string &dyck) {
  Integer word{};

  for (size_t i{}; i < dyck.size() / 2; i++) {
    // Iterate through the word setting the corresponding bit
    auto ch = dyck[i];
    assert(ch == OPENING_BRACKET || ch == CLOSING_BRACKET);

    if (ch == OPENING_BRACKET) {
      word++;
    }

    // Don't shift for the final
    if (i != dyck.size() / 2 - 1) word = word << 1;
  }

  return word;
}

}  // namespace generate
