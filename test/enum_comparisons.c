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

enum comparison_value { comparison_zero, comparison_one, comparison_two };

UTEST(enum_comparisons, constants_and_variables) {
  enum comparison_value value = comparison_one;
  ASSERT_EQ(comparison_one, value);
  EXPECT_EQ(value, comparison_one);
  ASSERT_NE(comparison_zero, value);
  EXPECT_NE(value, comparison_zero);
  ASSERT_LT(comparison_zero, value);
  EXPECT_LT(value, comparison_two);
  ASSERT_LE(comparison_one, value);
  EXPECT_LE(value, comparison_two);
  ASSERT_GT(comparison_two, value);
  EXPECT_GT(value, comparison_zero);
  ASSERT_GE(comparison_one, value);
  EXPECT_GE(value, comparison_zero);
}
