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

#include <cassert>
#include <string>

#include "solve/solution.h"

namespace generate {

// Helper for if a specific generated word is a single component by checking
// each bit and ensuring that the sum only reaches 0 at the final digit
bool IsComponent(Generator::Integer word, int length) {
  int sum{};
  for (int i{}; i < length; i++) {
    if (word % 2 == 0) {
      sum++;
    } else {
      sum--;
      if (sum == 0 && i != length - 1) return false;
    }

    word = word >> 1;
  }

  return sum == 0;
}

// Helper for if a specific generated word is a hard word where each block
// length has to be specified
bool IsHardWord(Generator::Integer word, int block1, int block2) {
  // Mask for the first block and check its a component
  Generator::Integer mask = 0xffffffffffffffff >> (64 - block1);
  Generator::Integer last = word & mask;

  if (!IsComponent(last, block1)) return false;

  // Mask for the second block and check its a component
  mask = 0xffffffffffffffff >> (64 - block2);

  last = (word >> block1) & mask;

  return IsComponent(last, block2);
}

Generator::Integer Generator::GenerateNext() {
  // Get and generate the next word in the sequence
  if (current > kMaxWord) return kErrorWord;

  Integer old = current;

  // https://arxiv.org/pdf/1602.06426.pdf
  const Integer a = current & -current;
  const Integer b = current + a;
  Integer c = current ^ b;
  c = (c / a >> 2) + 1;
  c = ((c * c - 1) & 0xaaaaaaaaaaaaaaaa) | b;
  current = c;

  return old;
}

Generator::Integer Generator::MinWord(int length) {
  Integer num{};

  // Create (10)^n
  for (int i{}; i < length; i++) {
    num++;
    num = num << 2;
  }

  return num >> 1;
}

Generator::Integer Generator::MaxWord(int length) {
  Integer num{};

  // Create 1^n0^n
  for (int i{}; i < length; i++) {
    num++;
    num = num << 1;
  }

  num = num << (length - 1);

  return num;
}

Generator::Integer Generator::DyckToWord(const std::string &dyck) {
  if (dyck.size() == 0) return kErrorWord;

  Integer word{};
  auto sz = dyck.size() - 1;

  // Iterate through the entire word setting the correct bits. Skip the final
  // iteration for 64 bit compatibility
  for (size_t i{}; i < sz; i++) {
    auto ch = dyck[i];
    assert(ch == OPENING_BRACKET || ch == CLOSING_BRACKET);

    if (ch == OPENING_BRACKET) {
      word++;
    }

    word = word << 1;
  }

  auto ch = dyck[sz];
  assert(ch == OPENING_BRACKET || ch == CLOSING_BRACKET);

  if (ch == OPENING_BRACKET) {
    word++;
  }

  return word;
}

std::string Generator::WordToDyck(Generator::Integer word) {
  const int N = kLength * 2;
  std::string output;

  output.resize(N);

  // Iterate backwards setting the appropriate char based on the bit
  for (int i{N - 1}; i >= 0; i--) {
    if (word % 2 == 0) {
      output[i] = CLOSING_BRACKET;
    } else {
      output[i] = OPENING_BRACKET;
    }

    word = word >> 1;
  }

  return output;
}

bool Generator::IsHardWord(Integer word) {
  if (kLength % 2 == 0) {
    return generate::IsHardWord(word, kLength, kLength);
  }

  // For odd lengths, the split can be either direction of the middle
  return generate::IsHardWord(word, kLength + 1, kLength - 1) ||
         generate::IsHardWord(word, kLength - 1, kLength + 1);
}

}  // namespace generate
