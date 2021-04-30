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

#ifndef PROJECT_HELPERS_VERIFIERS_H_
#define PROJECT_HELPERS_VERIFIERS_H_

#include <string>

namespace helper {

// Returns true iff the word is a symmetric word. The word can be spread out or
// compressed
bool VerifySymmetricWord(std::string word);

// Returns true iff the word is a symmetric hard word. The word can be spread
// out or compressed
bool VerifySymmetricHardWord(std::string word);

// Returns true iff the word is a valid Dyck word. The word can be spread out or
// compressed
bool VerifyWord(const std::string &word);

// Returns true iff the word is a hard word. This word can be spread out or
// compressed
bool VerifyHardWord(std::string word);

}  // namespace helper

#endif
