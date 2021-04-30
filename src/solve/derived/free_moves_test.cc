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

#include "free_moves.h"

#include <gtest/gtest.h>

#include "generate/generate_random.h"
#include "solve/solution.h"

namespace {

TEST(FreeMoves, CatchesCase1) {
  std::string word{"(())(  )(())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())    (())");
}

TEST(FreeMoves, CatchesCase1Multiple) {
  std::string word{"(())((  ))(())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())      (())");

  std::string word1{"(())(((  )))(())"};
  solve::Solution sol1(word1);

  solve::derived::MakeFreeMoves(sol1);

  ASSERT_EQ(sol1.GetWord(), "(())        (())");
}

TEST(FreeMoves, CatchesCase2) {
  std::string word{"(())()  (())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())    (())");
}

TEST(FreeMoves, CatchesCase2Multiple) {
  std::string word{"(())()()  (())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())      (())");
}

TEST(FreeMoves, CatchesCase3) {
  std::string word{"(())  ()(())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())    (())");
}

TEST(FreeMoves, CatchesCase3Multiple) {
  std::string word{"(())  ()()(())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())      (())");
}

TEST(FreeMoves, CatchesAll) {
  std::string word{"(())(()  ())(())"};
  solve::Solution sol(word);

  solve::derived::MakeFreeMoves(sol);

  ASSERT_EQ(sol.GetWord(), "(())        (())");

  std::string word1{"(())( ( ()))(())"};
  solve::Solution sol1(word1);

  solve::derived::MakeFreeMoves(sol1);

  ASSERT_EQ(sol1.GetWord(), "(())        (())");
}

TEST(FreeMoves, OnePassCorrectness) {
  const int kWordSize = 100;

  for (int i{}; i < 10000; i++) {
    auto word = generate::RandomUniformWord(kWordSize);
    solve::Solution single(word);
    solve::Solution many(word);

    solve::derived::MakeFreeMoves(single);

    for (int i{}; i < kWordSize; i++) {
      solve::derived::MakeFreeMoves(many);
    }

    ASSERT_EQ(single, many);
  }
}

}  // namespace
