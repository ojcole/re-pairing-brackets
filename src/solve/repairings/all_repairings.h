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

#ifndef PROJECT_SOLVE_REPAIRINGS_ALL_REPAIRINGS_H_
#define PROJECT_SOLVE_REPAIRINGS_ALL_REPAIRINGS_H_

#include <climits>
#include <set>
#include <string>
#include <vector>

#include "solve/solution.h"

namespace solve {
namespace repairings {

// Result of getting all re-pairings
struct RepairingsResult {
  // Set of all re-pairings of significant length
  std::set<Solution::Repairing> repairings;
  // The width of all re-pairings
  Solution::width_size width = INT_MAX;
};

// Find all optimal re-pairings of a word stopping counting when max is reached
// with the significant length being n
RepairingsResult AllOptimalRepairings(const std::string &word, size_t max);

// Find all optimal re-pairings of a word stopping counting when max is reached
// allowing for the setting of the significant length
RepairingsResult AllOptimalRepairings(const std::string &word, size_t max,
                                      size_t significant);

}  // namespace repairings
}  // namespace solve

#endif
