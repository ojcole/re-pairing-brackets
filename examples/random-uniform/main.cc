#include <iostream>

#include "external/repairings/generate/generate_random.h"

int main() {
  const int n{30};

  std::cout << generate::RandomUniformWord(n) << std::endl;
}
