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

struct reader {
  int offset;
};

static int next(struct reader *reader) {
  const int current = reader->offset;
  reader->offset += 1;
  return current;
}

static const int bools[20] = {0, 1, 0, 1};
static const int ints[20] = {42, 13, 6, -53};
static const char *const strings[20] = {"42", "13", "6", "-53"};

UTEST(cpp_side_effects, EXPECT_TRUE_EXPECT_FALSE) {
  struct reader reader = {0};
  EXPECT_FALSE(bools[next(&reader)]);
  EXPECT_TRUE(bools[next(&reader)]);
  EXPECT_FALSE(bools[next(&reader)]);
  EXPECT_TRUE(bools[next(&reader)]);
}

UTEST(cpp_side_effects, EXPECT_EQ_EXPECT_NE) {
  struct reader reader = {0};
  EXPECT_EQ(42, ints[next(&reader)]);
  EXPECT_NE(14, ints[next(&reader)]);
  EXPECT_EQ(6, ints[next(&reader)]);
  EXPECT_NE(52, ints[next(&reader)]);
}

UTEST(cpp_side_effects, EXPECT_LT_EXPECT_LE) {
  struct reader reader = {0};
  EXPECT_LT(41, ints[next(&reader)]);
  EXPECT_LE(13, ints[next(&reader)]);
  EXPECT_LT(5, ints[next(&reader)]);
  EXPECT_LE(-53, ints[next(&reader)]);
}

UTEST(cpp_side_effects, EXPECT_GT_EXPECT_GE) {
  struct reader reader = {0};
  EXPECT_GT(43, ints[next(&reader)]);
  EXPECT_GE(13, ints[next(&reader)]);
  EXPECT_GT(7, ints[next(&reader)]);
  EXPECT_GE(-53, ints[next(&reader)]);
}

UTEST(cpp_side_effects, EXPECT_STREQ_EXPECT_STRNE) {
  struct reader reader = {0};
  EXPECT_STRNE("!42", strings[next(&reader)]);
  EXPECT_STREQ("13", strings[next(&reader)]);
  EXPECT_STRNE("!6", strings[next(&reader)]);
  EXPECT_STREQ("-53", strings[next(&reader)]);
}

UTEST(cpp_side_effects, EXPECT_STRNEQ_EXPECT_STRNEQ) {
  struct reader reader = {0};
  EXPECT_STRNNE("!42", strings[next(&reader)], 3);
  EXPECT_STRNEQ("13", strings[next(&reader)], 2);
  EXPECT_STRNNE("!6", strings[next(&reader)], 2);
  EXPECT_STRNEQ("-53", strings[next(&reader)], 3);
}

UTEST(cpp_side_effects, ASSERT_TRUE_ASSERT_FALSE) {
  struct reader reader = {0};
  ASSERT_FALSE(bools[next(&reader)]);
  ASSERT_TRUE(bools[next(&reader)]);
  ASSERT_FALSE(bools[next(&reader)]);
  ASSERT_TRUE(bools[next(&reader)]);
}

UTEST(cpp_side_effects, ASSERT_EQ_ASSERT_NE) {
  struct reader reader = {0};
  ASSERT_EQ(42, ints[next(&reader)]);
  ASSERT_NE(14, ints[next(&reader)]);
  ASSERT_EQ(6, ints[next(&reader)]);
  ASSERT_NE(52, ints[next(&reader)]);
}

UTEST(cpp_side_effects, ASSERT_LT_ASSERT_LE) {
  struct reader reader = {0};
  ASSERT_LT(41, ints[next(&reader)]);
  ASSERT_LE(13, ints[next(&reader)]);
  ASSERT_LT(5, ints[next(&reader)]);
  ASSERT_LE(-53, ints[next(&reader)]);
}

UTEST(cpp_side_effects, ASSERT_GT_ASSERT_GE) {
  struct reader reader = {0};
  ASSERT_GT(43, ints[next(&reader)]);
  ASSERT_GE(13, ints[next(&reader)]);
  ASSERT_GT(7, ints[next(&reader)]);
  ASSERT_GE(-53, ints[next(&reader)]);
}

UTEST(cpp_side_effects, ASSERT_STREQ_ASSERT_STRNE) {
  struct reader reader = {0};
  ASSERT_STRNE("!42", strings[next(&reader)]);
  ASSERT_STREQ("13", strings[next(&reader)]);
  ASSERT_STRNE("!6", strings[next(&reader)]);
  ASSERT_STREQ("-53", strings[next(&reader)]);
}

UTEST(cpp_side_effects, ASSERT_STRNEQ_ASSERT_STRNEQ) {
  struct reader reader = {0};
  ASSERT_STRNNE("!42", strings[next(&reader)], 3);
  ASSERT_STRNEQ("13", strings[next(&reader)], 2);
  ASSERT_STRNNE("!6", strings[next(&reader)], 2);
  ASSERT_STRNEQ("-53", strings[next(&reader)], 3);
}
