#include "generate_random_hard.h"

#include <cassert>

#include "generate_random.h"

namespace generate {

// Helper for generating GenericHardWords based on a generator of random words
std::string GenericHardWord(int size, RandomGenerator WordGen) {
  int half_size = size / 2;

  // For even lengths both sides should be of the same length
  if (size % 2 == 0) {
    auto word1 = WordGen(half_size - 1);
    auto word2 = WordGen(half_size - 1);

    return "(" + word1 + ")(" + word2 + ")";
  }

  // For odd lengths choose the second half to be longer
  auto word1 = WordGen(half_size - 1);
  auto word2 = WordGen(half_size);

  return "(" + word1 + ")(" + word2 + ")";
}

std::string RandomHardWord(int size) {
  return GenericHardWord(size, RandomUniformWord);
}

std::string RandomSymmetricHardWord(int size) {
  // If both sides are symmetric and the same word, then the entire word is
  // symmetric
  assert(size % 2 == 0);
  auto word = RandomSymmetricWord(size / 2 - 1);
  return "(" + word + ")(" + word + ")";
}

}  // namespace generate
