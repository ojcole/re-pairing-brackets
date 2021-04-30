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

#ifndef PROJECT_SOLVE_PREDICATE_WIDTH_CHECK_H_
#define PROJECT_SOLVE_PREDICATE_WIDTH_CHECK_H_

#include <string>
#include <unordered_map>

namespace solve {
namespace predicate {

// Test if word has width at least n
bool WordIsWidthAtLeastN(const std::string &word, int n);
// Test if word has width at least n using memo passed as the memo and pass an
// exit flag which is periodically checked to exit execution
bool WordIsWidthAtLeastN(const std::string &word, int n,
                         std::unordered_map<std::string, int> &memo,
                         bool &exit);

// Test if a symmetric hard word has width at least n
bool SymmetricHardWordIsWidthAtLeastN(const std::string &word, int n);
// Test if a symmetric hard word has width at least n using memo passed as the
// memo and pass an exit flag which is periodically checked to exit execution
bool SymmetricHardWordIsWidthAtLeastN(
    const std::string &word, int n, std::unordered_map<std::string, int> &memo,
    bool &exit);

}  // namespace predicate
}  // namespace solve

#endif
