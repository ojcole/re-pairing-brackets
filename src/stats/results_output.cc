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

#include "results_output.h"

#include <iostream>

#include "generate/generate_all.h"

namespace stats {

// Algorithm for a solver
using SolverAlgo = solve::Solutions (*)(std::vector<std::string>::iterator,
                                        std::vector<std::string>::iterator);

void OutputResultsCSV(const solve::Solutions &sols) {
  std::cout << "Word,Width,RePairing" << std::endl;

  for (const auto &sol : sols) {
    std::cout << sol.GetInitialWord() << "," << sol.GetWidth() << ",";

    for (const auto &pair : sol.GetRepairing()) {
      std::cout << "(" << pair.first << " | " << pair.second << ") ";
    }

    std::cout << std::endl;
  }
}

void OutputResultsCSVMini(const solve::Solutions &sols) {
  int totals[2] = {0, 0};
  std::cout << "Word,Width,RePairing" << std::endl;

  for (const auto &sol : sols) {
    if (sol.GetWidth() > 2) {
      std::cout << sol.GetInitialWord() << "," << sol.GetWidth() << ",";

      for (auto pair : sol.GetRepairing()) {
        std::cout << "(" << pair.first << " | " << pair.second << ") ";
      }

      std::cout << std::endl;
    } else {
      totals[sol.GetWidth() - 1]++;
    }
  }

  std::cerr << "Width 1: " << totals[0] << std::endl;
  std::cerr << "Width 2: " << totals[1] << std::endl;
}

void OutputResultsCSVMini(const solve::parallel::Result &result) {
  OutputResultsCSV(result.other);

  std::cerr << "Width 1: " << result.one_count << std::endl;
  std::cerr << "Width 2: " << result.two_count << std::endl;
}

void OutputRandomSample(const SampleResults &results) {
  for (size_t i{}; i < results.size(); i++) {
    std::cout << "Width " << (i + 1) << ": " << results[i] << std::endl;
  }
}

void OutputRandomSampleMinimal(const SampleResults &results) {
  for (size_t i{}; i < results.size(); i++) {
    std::cout << results[i];
    if (i != results.size() - 1) {
      std::cout << ",";
    }
  }

  std::cout << std::endl;
}

void OutputRepairing(const solve::Solution &solution) {
  solve::Solution sol(solution.GetInitialWord());
  auto repairing = solution.GetRepairing();

  for (const auto &pair : repairing) {
    std::cout << sol.GetWord() << std::endl;
    sol.PairOff(pair.first, pair.second);
  }
}

}  // namespace stats
