# utest.h #

[![Build status](https://ci.appveyor.com/api/projects/status/piell6hcrlwrcxp9?svg=true)](https://ci.appveyor.com/project/sheredom/utest-h)

[![Build status](https://api.travis-ci.org/repositories/sheredom/utest.h.svg)](https://travis-ci.org/sheredom/utest.h)

A simple one header solution to unit testing for C/C++.

## Usage ##

Just include utest.h in your code!

The current supported compilers are gcc, clang and msvc.

The current tested compiler versions are gcc 4.8.2, clang 3.5 and MSVC 18.0.21005.1.

## Design ##

UTest is a single header library to enable all the fun of unit testing in C and C++. The library has been designed to provide an output similar to Google's googletest framework;

    [==========] Running 1 test cases.
    [ RUN      ] foo.bar
    [       OK ] foo.bar (631ns)
    [==========] 1 test cases ran.
    [  PASSED  ] 1 tests.

To define a test case to run, you can do the following;

    #include "utest.h"

    TESTCASE(foo, bar) {
      ASSERT_TRUE(1);
    }

The TESTCASE macro takes two parameters - the first being the set that the test case belongs to, the second being the name of the test. This allows tests to be grouped for conveience.

Matching what googletest has, we provide two variants of each of the error checking conditions - ASSERT's and EXPECT's. If an ASSERT fails, the test case will cease execution, and utest.h will continue with the next test case to be run. If an EXPECT fails, the remainder of the test case will still be executed, allowing for further checks to be carried out.

We currently provide the following macros to be used within TESTCASE's.

### ASSERT_TRUE(x) ###

Asserts that x evaluates to true (EG. non-zero).

    TESTCASE(foo, bar) {
      int i = 1;
      ASSERT_TRUE(i);  // pass!
      ASSERT_TRUE(42); // pass!
      ASSERT_TRUE(0);  // fail!
    }

### ASSERT_FALSE(x) ###

Asserts that x evaluates to false (EG. zero).

    TESTCASE(foo, bar) {
      int i = 0;
      ASSERT_FALSE(i); // pass!
      ASSERT_FALSE(1); // fail!
    }

### ASSERT_EQ(x, y) ###

Asserts that x and y are equal.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 42;
      ASSERT_EQ(a, b);     // pass!
      ASSERT_EQ(a, 42);    // pass!
      ASSERT_EQ(42, b);    // pass!
      ASSERT_EQ(42, 42);   // pass!
      ASSERT_EQ(a, b + 1); // fail!
    }

### ASSERT_NE(x, y) ###

Asserts that x and y are not equal.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      ASSERT_NE(a, b);   // pass!
      ASSERT_NE(a, 27);  // pass!
      ASSERT_NE(69, b);  // pass!
      ASSERT_NE(42, 13); // pass!
      ASSERT_NE(a, 42);  // fail!
    }

### ASSERT_LT(x, y) ###

Asserts that x is less than y.

    TESTCASE(foo, bar) {
      int a = 13;
      int b = 42;
      ASSERT_LT(a, b);   // pass!
      ASSERT_LT(a, 27);  // pass!
      ASSERT_LT(27, b);  // pass!
      ASSERT_LT(13, 42); // pass!
      ASSERT_LT(b, a);   // fail!
    }

### ASSERT_LE(x, y) ###

Asserts that x is less than or equal to y.

    TESTCASE(foo, bar) {
      int a = 13;
      int b = 42;
      ASSERT_LE(a, b);   // pass!
      ASSERT_LE(a, 27);  // pass!
      ASSERT_LE(a, 13);  // pass!
      ASSERT_LE(27, b);  // pass!
      ASSERT_LE(42, b);  // pass!
      ASSERT_LE(13, 13); // pass!
      ASSERT_LE(13, 42); // pass!
      ASSERT_LE(b, a);   // fail!
    }

### ASSERT_GT(x, y) ###

Asserts that x is greater than y.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      ASSERT_GT(a, b);   // pass!
      ASSERT_GT(a, 27);  // pass!
      ASSERT_GT(27, b);  // pass!
      ASSERT_GT(42, 13); // pass!
      ASSERT_GT(b, a);   // fail!
    }

### ASSERT_GT(x, y) ###

Asserts that x is greater than or equal to y.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      ASSERT_GE(a, b);   // pass!
      ASSERT_GE(a, 27);  // pass!
      ASSERT_GE(a, 13);  // pass!
      ASSERT_GE(27, b);  // pass!
      ASSERT_GE(42, b);  // pass!
      ASSERT_GE(13, 13); // pass!
      ASSERT_GE(42, 13); // pass!
      ASSERT_GE(b, a);   // fail!
    }

### EXPECT_TRUE(x) ###

Expects that x evaluates to true (EG. non-zero).

    TESTCASE(foo, bar) {
      int i = 1;
      EXPECT_TRUE(i);  // pass!
      EXPECT_TRUE(42); // pass!
      EXPECT_TRUE(0);  // fail!
    }

### EXPECT_FALSE(x) ###

Expects that x evaluates to false (EG. zero).

    TESTCASE(foo, bar) {
      int i = 0;
      EXPECT_FALSE(i); // pass!
      EXPECT_FALSE(1); // fail!
    }

### EXPECT_EQ(x, y) ###

Expects that x and y are equal.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 42;
      EXPECT_EQ(a, b);     // pass!
      EXPECT_EQ(a, 42);    // pass!
      EXPECT_EQ(42, b);    // pass!
      EXPECT_EQ(42, 42);   // pass!
      EXPECT_EQ(a, b + 1); // fail!
    }

### EXPECT_NE(x, y) ###

Expects that x and y are not equal.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      EXPECT_NE(a, b);   // pass!
      EXPECT_NE(a, 27);  // pass!
      EXPECT_NE(69, b);  // pass!
      EXPECT_NE(42, 13); // pass!
      EXPECT_NE(a, 42);  // fail!
    }

### EXPECT_LT(x, y) ###

Expects that x is less than y.

    TESTCASE(foo, bar) {
      int a = 13;
      int b = 42;
      EXPECT_LT(a, b);   // pass!
      EXPECT_LT(a, 27);  // pass!
      EXPECT_LT(27, b);  // pass!
      EXPECT_LT(13, 42); // pass!
      EXPECT_LT(b, a);   // fail!
    }

### EXPECT_LE(x, y) ###

Expects that x is less than or equal to y.

    TESTCASE(foo, bar) {
      int a = 13;
      int b = 42;
      EXPECT_LE(a, b);   // pass!
      EXPECT_LE(a, 27);  // pass!
      EXPECT_LE(a, 13);  // pass!
      EXPECT_LE(27, b);  // pass!
      EXPECT_LE(42, b);  // pass!
      EXPECT_LE(13, 13); // pass!
      EXPECT_LE(13, 42); // pass!
      EXPECT_LE(b, a);   // fail!
    }

### EXPECT_GT(x, y) ###

Expects that x is greater than y.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      EXPECT_GT(a, b);   // pass!
      EXPECT_GT(a, 27);  // pass!
      EXPECT_GT(27, b);  // pass!
      EXPECT_GT(42, 13); // pass!
      EXPECT_GT(b, a);   // fail!
    }

### EXPECT_GT(x, y) ###

Expects that x is greater than or equal to y.

    TESTCASE(foo, bar) {
      int a = 42;
      int b = 13;
      EXPECT_GE(a, b);   // pass!
      EXPECT_GE(a, 27);  // pass!
      EXPECT_GE(a, 13);  // pass!
      EXPECT_GE(27, b);  // pass!
      EXPECT_GE(42, b);  // pass!
      EXPECT_GE(13, 13); // pass!
      EXPECT_GE(42, 13); // pass!
      EXPECT_GE(b, a);   // fail!
    }

## License ##

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
