// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>

#include "utest.h"

#ifdef _MSC_VER
// disable 'conditional expression is constant' - our examples below use this!
#pragma warning(disable : 4127)
#endif

UTEST(cpp17, ASSERT_TRUE) { ASSERT_TRUE(1); }

UTEST(cpp17, ASSERT_FALSE) { ASSERT_FALSE(0); }

UTEST(cpp17, ASSERT_EQ) { ASSERT_EQ(1, 1); }

UTEST(cpp17, ASSERT_NE) { ASSERT_NE(1, 2); }

UTEST(cpp17, ASSERT_LT) { ASSERT_LT(1, 2); }

UTEST(cpp17, ASSERT_LE) {
  ASSERT_LE(1, 1);
  ASSERT_LE(1, 2);
}

UTEST(cpp17, ASSERT_GT) { ASSERT_GT(2, 1); }

UTEST(cpp17, ASSERT_GE) {
  ASSERT_GE(1, 1);
  ASSERT_GE(2, 1);
}

UTEST(cpp17, ASSERT_STREQ) { ASSERT_STREQ("foo", "foo"); }

UTEST(cpp17, ASSERT_STRNE) { ASSERT_STRNE("foo", "bar"); }

UTEST(cpp17, ASSERT_STRNEQ) { ASSERT_STRNEQ("foo", "foobar", strlen("foo")); }

UTEST(cpp17, ASSERT_STRNNE) { ASSERT_STRNNE("foo", "barfoo", strlen("foo")); }

UTEST(cpp17, EXPECT_TRUE) { EXPECT_TRUE(1); }

UTEST(cpp17, EXPECT_FALSE) { EXPECT_FALSE(0); }

UTEST(cpp17, EXPECT_EQ) { EXPECT_EQ(1, 1); }

UTEST(cpp17, EXPECT_NE) { EXPECT_NE(1, 2); }

UTEST(cpp17, EXPECT_LT) { EXPECT_LT(1, 2); }

UTEST(cpp17, EXPECT_LE) {
  EXPECT_LE(1, 1);
  EXPECT_LE(1, 2);
}

UTEST(cpp17, EXPECT_GT) { EXPECT_GT(2, 1); }

UTEST(cpp17, EXPECT_GE) {
  EXPECT_GE(1, 1);
  EXPECT_GE(2, 1);
}

UTEST(cpp17, EXPECT_STREQ) { EXPECT_STREQ("foo", "foo"); }

UTEST(cpp17, EXPECT_STRNE) { EXPECT_STRNE("foo", "bar"); }

UTEST(cpp17, EXPECT_STRNEQ) { EXPECT_STRNEQ("foo", "foobar", strlen("foo")); }

UTEST(cpp17, EXPECT_STRNNE) { EXPECT_STRNNE("foo", "barfoo", strlen("foo")); }

UTEST(cpp17, no_double_eval) {
  int i = 0;
  ASSERT_EQ(i++, 0);
  ASSERT_EQ(i, 1);
}

struct MyTestF {
  int foo;
};

UTEST_F_SETUP(MyTestF) {
  ASSERT_EQ(0, utest_fixture->foo);
  utest_fixture->foo = 42;
}

UTEST_F_TEARDOWN(MyTestF) { ASSERT_EQ(13, utest_fixture->foo); }

UTEST_F(MyTestF, cpp17_1) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

UTEST_F(MyTestF, cpp17_2) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

struct MyTestI {
  size_t foo;
  size_t bar;
};

UTEST_I_SETUP(MyTestI) {
  ASSERT_EQ(0u, utest_fixture->foo);
  ASSERT_EQ(0u, utest_fixture->bar);
  utest_fixture->foo = 42;
  utest_fixture->bar = utest_index;
}

UTEST_I_TEARDOWN(MyTestI) {
  ASSERT_EQ(13u, utest_fixture->foo);
  ASSERT_EQ(utest_index, utest_fixture->bar);
}

UTEST_I(MyTestI, cpp17_1, 2) {
  ASSERT_GT(2u, utest_fixture->bar);
  utest_fixture->foo = 13;
}

UTEST_I(MyTestI, cpp17_2, 128) {
  ASSERT_GT(128u, utest_fixture->bar);
  utest_fixture->foo = 13;
}

UTEST(cpp17, Float) {
  float a = 1;
  float b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, Double) {
  double a = 1;
  double b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, LongDouble) {
  long double a = 1;
  long double b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, Char) {
  signed char a = 1;
  signed char b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, UChar) {
  unsigned char a = 1;
  unsigned char b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, Short) {
  short a = 1;
  short b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, UShort) {
  unsigned short a = 1;
  unsigned short b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, Int) {
  int a = 1;
  int b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, UInt) {
  unsigned int a = 1;
  unsigned int b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, Long) {
  long a = 1;
  long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, ULong) {
  unsigned long a = 1;
  unsigned long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

UTEST(cpp17, LongLong) {
  long long a = 1;
  long long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST(cpp17, ULongLong) {
  unsigned long long a = 1;
  unsigned long long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

UTEST(cpp17, Ptr) {
  char foo = 42;
  EXPECT_NE(&foo, &foo + 1);
}

UTEST(cpp17, VoidPtr) {
  void *foo = reinterpret_cast<void *>(0);
  EXPECT_NE(foo, static_cast<char *>(foo) + 1);
}

static const int data[4] = {42, 13, 6, -53};

UTEST(cpp17, Array) { EXPECT_NE(data, data + 1); }

UTEST(cpp17, Near) {
  float a = 42.0f;
  float b = 42.01f;
  EXPECT_NEAR(a, b, 0.01f);
  ASSERT_NEAR(a, b, 0.01f);
}

static int foo(int bar) {
  if (bar == 1)
    throw std::range_error("bad bar");
  return bar + 1;
}

UTEST(cpp17, Exception) {
  EXPECT_EXCEPTION(foo(1), std::range_error);
  ASSERT_EXCEPTION(foo(1), std::range_error);
}

UTEST(cpp17, Todo) { UTEST_SKIP("Not yet implemented!"); }

enum SomeEnum { SomeEnumFoo, SomeEnumBar };

UTEST(cpp17, Enum) {
  EXPECT_NE(SomeEnumFoo, SomeEnumBar);
  ASSERT_EQ(SomeEnumFoo, SomeEnumFoo);
}

#if !defined(_MSC_VER) || (_MSC_VER >= 1900)
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

enum class SomeEnumClass { Foo, Bar };

UTEST(cpp17, EnumClass) {
  EXPECT_NE(SomeEnumClass::Foo, SomeEnumClass::Bar);
  ASSERT_EQ(SomeEnumClass::Foo, SomeEnumClass::Foo);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
