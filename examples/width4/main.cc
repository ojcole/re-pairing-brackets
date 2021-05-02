

#include <iomanip>
#include <iostream>
#include <string>

#include "external/repairings/solve/predicate/width_check.h"

int main() {
  std::string word =
      "((((())((((())((((())))((())(((())))((()))))((((())((((()))((((()))((())"
      ")(())((()))))((((()))(())((()))((()))))((()))))(()))))((((()))(((())))(("
      ")))(((()))))(()))))(()))))((((())((((())((((())))((())(((())))((()))))(("
      "((())((((()))((((()))((()))(())((()))))((((()))(())((()))((()))))((())))"
      ")(()))))((((()))(((())))(()))(((()))))(()))))(()))))";

  std::cout << std::boolalpha
            << solve::predicate::SymmetricHardWordIsWidthAtLeastN(word, 4)
            << std::endl;
}
