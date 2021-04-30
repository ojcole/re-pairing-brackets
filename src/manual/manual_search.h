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

#ifndef PROJECT_MANUAL_MANUAL_SEARCH_H_
#define PROJECT_MANUAL_MANUAL_SEARCH_H_

#include <string>
#include <vector>

namespace manual {

// Save word to the specified file
void SaveWord(const std::string &word, std::string file);

// Save all words on newlines in file. These words must be compressed to read
// them back correctly
void SaveWords(const std::vector<std::string> &words, std::string file);

// Load a single word from a file uncompressed
std::string LoadWord(std::string file);

// Load a single word that is halfed in the file before concatenating it with
// itself
std::string LoadHalfWord(std::string file);

// Load a single word that is spread, compressing it before returning
std::string LoadSpreadWord(std::string file);

// Load a single half word that is spread, compressing it before concatenating
// it with itself and returning
std::string LoadSpreadHalfWord(std::string file);

// Load a list of words each on one line from a file
std::vector<std::string> LoadWords(std::string file);

// Spread a symmetric hard word for visualising
std::string SpreadSymmetricHardWord(std::string word);

// Returns true iff the symmetric hard word in the file has width as least n
bool SymmetricHardWordWidthAtLeastN(std::string file, int n);

}  // namespace manual

#endif
