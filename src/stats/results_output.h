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

#ifndef PROJECT_STATS_GREEDY_RESULTS_H_
#define PROJECT_STATS_GREEDY_RESULTS_H_

#include <vector>

#include "random_sample_width.h"
#include "solve/parallel/result.h"
#include "solve/solution.h"

namespace stats {

// Outputs in a CSV format the following content to stdout:
// Word,Width,RePairing
// ()(),1,(0|1) (2|3)
void OutputResultsCSV(const solve::Solutions &sols);

// Outputs in a CSV format the following content to stdout for any word with
// width >= 3:
// Word,Width,RePairing
// ()(),1,(0|1) (2|3)
// To stderr, it outputs Width k: n where k is the width and n is the number
// found at that width
// This uses the solutions passed
void OutputResultsCSVMini(const solve::Solutions &sols);

// Outputs in a CSV format the following content to stdout for any word with
// width >= 3:
// Word,Width,RePairing
// ()(),1,(0|1) (2|3)
// To stderr, it outputs Width k: n where k is the width and n is the number
// found at that width
// This uses the results in the result object which follow this format
void OutputResultsCSVMini(const solve::parallel::Result &result);

// Outputs width k: n for each k in the sample results
void OutputRandomSample(const SampleResults &results);

// Outputs n1,n2,n3,...,nk for each k of width
void OutputRandomSampleMinimal(const SampleResults &results);

// Outputs a full re-pairing showing the word at each point in time
void OutputRepairing(const solve::Solution &solution);

}  // namespace stats

#endif
