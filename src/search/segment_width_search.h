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

#ifndef PROJECT_SEARCH_SEGMENT_WIDTH_SEARCH_H_
#define PROJECT_SEARCH_SEGMENT_WIDTH_SEARCH_H_

#include <string>
#include <vector>

#include "generate/generate_next.h"
#include "generate/generate_next_symmetric.h"

namespace search {

// Build words of the form first + w + second . (first + w + second)^R
// concatenated where w is every Dyck word of the given size. These words will
// be searched exhaustively across workers number of threads returning all with
// width >= n
std::vector<std::string> SearchSegmentForWidth(std::string first,
                                               std::string second, int size,
                                               int n, int workers);

// Build words of the form first + w + second . (first + w + second)^R where w
// is every word representing a positive Dyck path of the given size. This
// generates all half symmetric words as w. These words will be searched
// exhaustively across workers number of threads returning all with width >= n
std::vector<std::string> SearchSymmetricSegmentForWidth(std::string first,
                                                        std::string second,
                                                        int size, int n,
                                                        int workers);

// Performs the same operation as SearchSegmentForWidth, however only searches
// through the next group_size words of the generator. The intended usage of
// this is for distributing the work over many nodes, each node will jump the
// generator forward a set amount before the next group_size is searched.
// Examples of this generation can be found in scripts segment search
std::vector<std::string> PartialSearchSegmentForWidth(
    std::string first, std::string second, generate::Generator &generator,
    int width, int group_size, int workers);

// Performs the same operation as SearchSymmetricSegmentForWidth, however only
// searches through the next group_size words of the generator. The intended
// usage of this is for distributing the work over many nodes, each node will
// jump the generator forward a set amount before the next group_size is
// searched. Examples of this generation can be found in scripts segment search
std::vector<std::string> PartialSearchSymmetricSegmentForWidth(
    std::string first, std::string second,
    generate::SymmetricGenerator &generator, int width, int group_size,
    int workers);

}  // namespace search

#endif
