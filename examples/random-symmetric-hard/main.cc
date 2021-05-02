#include <iostream>

#include "external/repairings/generate/generate_random_hard.h"

int main() {
  const int n{30};

  std::cout << generate::RandomSymmetricHardWord(n) << std::endl;
}
