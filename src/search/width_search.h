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

#ifndef PROJECT_SEARCH_WIDTH_SEARCH_H_
#define PROJECT_SEARCH_WIDTH_SEARCH_H_

#include <string>
#include <unordered_map>

#include "generate/generate_random.h"

namespace search {

// Type signature for a solver to pass which takes the word, the width to search
// for, a memo to utilize, and an exit condition boolean
using PredicateSolver = bool (*)(const std::string &, int,
                                 std::unordered_map<std::string, int> &,
                                 bool &);

// Randomly search for hard symmetric words of length size with width at least
// the specified values. This should be performed for a number of iterations
// over workers number of threads
std::string HardSymmetricWidthSearch(int width, int size, int iterations,
                                     int workers);

// Randomly search for words of length size with width at least
// the specified values using words generated by the generator. This should be
// performed for a number of iterations over workers number of threads
std::string WidthSearch(int width, generate::RandomGenerator generator,
                        int size, int iterations, int workers);

// Randomly search for words of length size with width at least
// the specified values using words generated by the generator. This should be
// performed for a number of iterations over workers number of threads. Words
// will be checked using the PredicateSolver passed
std::string WidthSearch(int width, generate::RandomGenerator generator,
                        int size, int iterations, int workers,
                        PredicateSolver Solver);

}  // namespace search

#endif
