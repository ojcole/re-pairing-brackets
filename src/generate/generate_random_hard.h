#ifndef PROJECT_GENERATE_GENERATE_RANDOM_HARD_H_
#define PROJECT_GENERATE_GENERATE_RANDOM_HARD_H_

#include <string>

namespace generate {

// Generate a hard word uniformly at random of n = size pairs
std::string RandomHardWord(int size);

// Generate a symmetric hard word uniformly at random of n = size pairs. Size
// must therefore be an even number
std::string RandomSymmetricHardWord(int size);

}  // namespace generate

#endif
