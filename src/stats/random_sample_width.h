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

#ifndef PROJECT_STATS_RANDOM_SAMPLE_WIDTH_H_
#define PROJECT_STATS_RANDOM_SAMPLE_WIDTH_H_

#include <string>
#include <vector>

namespace stats {

// The results of sampling with indexes corresponding to widths
using SampleResults = std::vector<long>;

// Take samples number of samples of random uniform words of size size
SampleResults RandomUniformSampleWidths(int samples, int size);
// Take samples number of samples of random uniform words of size size across
// workers number of threads
SampleResults RandomUniformSampleWidths(int samples, int size, int workers);
// Take samples number of samples of random symmetric words of size size
SampleResults RandomSymmetricSampleWidths(int samples, int size);
// Take samples number of samples of random symmetric words of size size across
// workers number of threads
SampleResults RandomSymmetricSampleWidths(int samples, int size, int workers);
// Take samples number of samples of random hard words of size size
SampleResults RandomHardSampleWidths(int samples, int size);
// Take samples number of samples of random hard words of size size across
// workers number of threads
SampleResults RandomHardSampleWidths(int samples, int size, int workers);
// Take samples number of samples of random symmetric hard words of size size
SampleResults RandomSymmetricHardSampleWidths(int samples, int size);
// Take samples number of samples of random symmetric hard words of size size
// across workers number of threads
SampleResults RandomSymmetricHardSampleWidths(int samples, int size,
                                              int workers);

}  // namespace stats

#endif
