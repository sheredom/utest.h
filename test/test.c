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
#pragma
#endif

UTEST(c, ASSERT_TRUE) { ASSERT_TRUE(1); }

UTEST(c, ASSERT_FALSE) { ASSERT_FALSE(0); }

UTEST(c, ASSERT_EQ) { ASSERT_EQ(1, 1); }

UTEST(c, ASSERT_NE) { ASSERT_NE(1, 2); }

UTEST(c, ASSERT_LT) { ASSERT_LT(1, 2); }

UTEST(c, ASSERT_LE) {
  ASSERT_LE(1, 1);
  ASSERT_LE(1, 2);
}

UTEST(c, ASSERT_GT) { ASSERT_GT(2, 1); }

UTEST(c, ASSERT_GE) {
  ASSERT_GE(1, 1);
  ASSERT_GE(2, 1);
}

UTEST(c, ASSERT_STREQ) { ASSERT_STREQ("foo", "foo"); }

UTEST(c, ASSERT_STRNE) { ASSERT_STRNE("foo", "bar"); }

UTEST(c, EXPECT_TRUE) { EXPECT_TRUE(1); }

UTEST(c, EXPECT_FALSE) { EXPECT_FALSE(0); }

UTEST(c, EXPECT_EQ) { EXPECT_EQ(1, 1); }

UTEST(c, EXPECT_NE) { EXPECT_NE(1, 2); }

UTEST(c, EXPECT_LT) { EXPECT_LT(1, 2); }

UTEST(c, EXPECT_LE) {
  EXPECT_LE(1, 1);
  EXPECT_LE(1, 2);
}

UTEST(c, EXPECT_GT) { EXPECT_GT(2, 1); }

UTEST(c, EXPECT_GE) {
  EXPECT_GE(1, 1);
  EXPECT_GE(2, 1);
}

UTEST(c, EXPECT_STREQ) { EXPECT_STREQ("foo", "foo"); }

UTEST(c, EXPECT_STRNE) { EXPECT_STRNE("foo", "bar"); }

struct MyTestF {
  int foo;
};

UTEST_F_SETUP(MyTestF) {
  ASSERT_EQ(0, utest_fixture->foo);
  utest_fixture->foo = 42;
}

UTEST_F_TEARDOWN(MyTestF) {
  ASSERT_EQ(13, utest_fixture->foo);
}

UTEST_F(MyTestF, c) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

UTEST_F(MyTestF, c2) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

struct MyTestI {
  size_t foo;
  size_t bar;
};

UTEST_I_SETUP(MyTestI) {
  ASSERT_EQ(0, utest_fixture->foo);
  ASSERT_EQ(0, utest_fixture->bar);
  utest_fixture->foo = 42;
  utest_fixture->bar = utest_index;
}

UTEST_I_TEARDOWN(MyTestI) {
  ASSERT_EQ(13, utest_fixture->foo);
  ASSERT_EQ(utest_index, utest_fixture->bar);
}

UTEST_I(MyTestI, c, 2) {
  ASSERT_GT(2, utest_fixture->bar);
  utest_fixture->foo = 13;
}

UTEST_I(MyTestI, c2, 128) {
  ASSERT_GT(128, utest_fixture->bar);
  utest_fixture->foo = 13;
}
