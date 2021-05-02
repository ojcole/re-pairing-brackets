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
