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

#ifndef PROJECT_HELPERS_MANIPULATORS_H_
#define PROJECT_HELPERS_MANIPULATORS_H_

#include <string>

namespace helper {

// Remove any chars from a word that are not opening or closing brackets. This
// does not maintain spaces mid string
std::string CompressWord(const std::string &word);

// Reflects a string to form a symmetric word of the form word.word^R
std::string MirrorWord(std::string word);

// Splits a word at the first instance of X compressing both sides of the result
std::pair<std::string, std::string> SplitAtX(const std::string &word, char x);

// Strips any characters not in the main chunk of the word. This means that any
// trailing or leading characters are removed, but any characters between the
// first and last brackets are left
std::string StripWord(const std::string &word);

}  // namespace helper

#endif
