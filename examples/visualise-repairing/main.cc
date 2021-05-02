#include <string>

#include "external/repairings/solve/exhaustive/solve_exhaustive.h"
#include "external/repairings/stats/results_output.h"

int main() {
  std::string word{"(((())((()))(())))(((())(((())))(())))"};

  auto sol = solve::ExhaustiveSolve(word);

  stats::OutputRepairing(sol);
}
