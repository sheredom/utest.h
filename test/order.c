/*
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
*/

#include "utest.h"

struct utest_order_indexed_fixture {
  int unused;
};

UTEST_I_SETUP(utest_order_indexed_fixture) {
  (void)utest_fixture;
  (void)utest_index;
  ASSERT_TRUE(1);
}

UTEST_I_TEARDOWN(utest_order_indexed_fixture) {
  (void)utest_fixture;
  (void)utest_index;
  ASSERT_TRUE(1);
}

UTEST_I(utest_order_indexed_fixture, many, 12) {
  (void)utest_fixture;
  ASSERT_TRUE(1);
}

// clang-format off
UTEST(utest_order_same_line, b) { ASSERT_TRUE(1); } UTEST(utest_order_same_line, a) { ASSERT_TRUE(1); }
// clang-format on
