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

#include "generate_random.h"

#include <random>
#include <string>

#include "solve/solution.h"

namespace generate {

using rand_gen = std::ranlux48;

std::string RandomSymmetricWord(int size) {
  std::random_device random;
  rand_gen gen(random());
  std::bernoulli_distribution distribution(0.5);

  // First element is not random so set it and resize to the full length
  std::string result{OPENING_BRACKET};
  result.resize(size * 2);
  bool complete{false};

  // Perform a guess and check by randomly generating and checking if the
  // resulting half word is positive
  while (!complete) {
    int depth{1};

    for (int i{1}; i < size; i++) {
      bool open = distribution(gen);

      if (open) {
        result[i] = OPENING_BRACKET;
        depth++;
      } else {
        result[i] = CLOSING_BRACKET;
        depth--;

        if (depth < 0) {
          break;
        }
      }

      if (i == size - 1) complete = true;
    }
  }

  // If the half word is positive, we can just mirror the word to get a
  // symmetric word
  for (int i{}; i < size; i++) {
    auto c = OPENING_BRACKET;
    if (result[i] == OPENING_BRACKET) {
      c = CLOSING_BRACKET;
    }

    result[size * 2 - 1 - i] = c;
  }

  return result;
}

// Probability of picking an opening bracket as the next:
// http://gt-alea.math.cnrs.fr/COURS/Gouyou-Beauchamps_alea2002.pdf
bool NextIsOpen(int p, int q, int actual_size, rand_gen &generator) {
  int m = actual_size - p - q;
  int h = p - q;
  long double d_m = m;
  long double d_h = h;
  long double first = (d_h + 2) / (d_h + 1);
  long double second = (d_m - d_h) / (2 * d_m);
  std::bernoulli_distribution distribution(first * second);
  return distribution(generator);
}

std::string RandomUniformWord(int size) {
  int actual_size = 2 * size;
  std::string res{OPENING_BRACKET};
  res.resize(actual_size);
  res[actual_size - 1] = CLOSING_BRACKET;
  int p{1};
  int q{0};
  std::random_device random;
  rand_gen gen(random());

  // Keep generating all of the chars in the word
  while (p + q < actual_size - 1) {
    int next = NextIsOpen(p, q, actual_size, gen);

    if (next) {
      res[p + q] = OPENING_BRACKET;
      p++;
    } else {
      res[p + q] = CLOSING_BRACKET;
      q++;
    }
  }

  return res;
}

}  // namespace generate
