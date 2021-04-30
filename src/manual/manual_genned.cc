
#include <iostream>
#include <string>

#include "generate/generate_next_symmetric.h"
#include "helpers/n_choose_k.h"
#include "search/segment_width_search.h"

int main() {
  std::string first = "(";
  std::string second = "";

  int size = 9;
  int worker = 5;
  int workers = 5;

  generate::SymmetricGenerator generator(size);

  auto words = helper::NChooseK(size, size / 2);
  auto group_size = words / workers;

  auto res = (worker - 1) * group_size;

  if (worker == workers) {
    group_size += words % workers;
  }

  for (size_t i{}; i < res; i++) {
    generator.GenerateNext();
  }

  auto result = search::PartialSearchSymmetricSegmentForWidth(first, second, generator,
                                                     3, group_size, 4);

  std::cout << result.size() << std::endl;

  for (auto w : result) {
    std::cout << w << std::endl;
  }

  return 0;
}
