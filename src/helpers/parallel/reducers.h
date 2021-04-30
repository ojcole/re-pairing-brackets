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

#ifndef PROJECT_HELPERS_PARALLEL_VECTOR_REDUCER_H_
#define PROJECT_HELPERS_PARALLEL_VECTOR_REDUCER_H_

#include <vector>

namespace helper {
namespace parallel {

// Reducer/Combiner for GenericParallelRunner which builds a vector up from the
// first to the last
template <typename T>
inline std::vector<T> VectorReducer(std::vector<T> &accumulator,
                                    const std::vector<T> &result) {
  accumulator.insert(accumulator.end(), result.begin(), result.end());
  return accumulator;
}

// Reducer/Combiner for GenericParallelRunner which returns the first value
// passed to it that is non-empty. This can be any type that has a size function
template <typename T>
inline T FirstNonEmpty(const T &accumulator, const T &other) {
  return accumulator.size() > 0 ? accumulator : other;
}

}  // namespace parallel
}  // namespace helper

#endif
