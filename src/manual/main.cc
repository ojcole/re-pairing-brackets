#include <iomanip>
#include <iostream>
#include <set>
#include <string>

#include "generate/generate_next_symmetric.h"
#include "helpers/manipulators.h"
#include "helpers/verifiers.h"
#include "manual_search.h"
#include "search/segment_width_search.h"
#include "solve/exhaustive/solve_exhaustive.h"
#include "solve/greedy/solve_simple_greedy.h"
#include "solve/minimise/minimise_width.h"
#include "solve/predicate/width_check.h"
#include "stats/hardness.h"
#include "stats/results_output.h"

int main() {
  const std::string kWorkingWord{"manual/data_files/working_word.txt"};
  const std::string kPlaceholderWord{"manual/data_files/placeholder_word.txt"};
  const std::string kTmpWord{"manual/data_files/tmp.txt"};
  const std::string kSeg1{"manual/data_files/segment1.txt"};
  const std::string kSeg2{"manual/data_files/segment2.txt"};
  const std::string words174{"manual/data_files/174words.txt"};
  const std::string words170{"manual/data_files/170words.txt"};

  auto words = manual::LoadWords(words170);

  stats::OutputRepairing(solve::ExhaustiveSolve(words[0]));
}
