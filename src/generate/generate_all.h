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

#ifndef PROJECT_GENERATE_GENERATE_ALL_H_
#define PROJECT_GENERATE_GENERATE_ALL_H_

#include <list>
#include <string>
#include <vector>

namespace generate {

// Generates all Dyck words with a particular length in lexicographic order
std::vector<std::string> GenerateSimple(int length);

// Generates all Dyck words with a particular length. This method uses a memo to
// skip computation. Experimentation shows this method performs better than
// GenerateSimple for larger values of length. However, the words are not in
// lexicographic order
std::vector<std::string> GenerateMemoed(int length);

// Generates all Dyck words with a particular length using dynamic programming.
// There is no guarantee of the order of these words
std::vector<std::string> GenerateDynamic(int length);

// Generates all Dyck words with a particular length using constant time next
// generation. There is no guarantee of the order of these words
std::vector<std::string> GenerateConstant(int length);

// Generates all Dyck words with a particular length using the swapping
// algorithm. There is no guarantee of the order of these words. This is the
// fastest method for generating all words
std::vector<std::string> GenerateSwapping(int length);

// Generates all symmetric Dyck words with a particular length. This is no
// guarantee of the order of these words
std::vector<std::string> GenerateSymmetric(int length);

}  // namespace generate

#endif
