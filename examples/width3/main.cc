#include <iostream>

#include "external/repairings/search/width_search.h"

int main() {
  auto word = search::HardSymmetricWidthSearch(3, 20, 10000, 4);

  std::cout << word << std::endl;
}
