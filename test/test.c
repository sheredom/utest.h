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

#ifdef _MSC_VER
/* disable 'conditional expression is constant' - our examples below use this! */
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

UTEST(c, no_double_eval) {
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


#ifdef __linux__
#include <errno.h>
/** Check that the output from --list-tests matches our internal view of the
 * listed tests. This means calling ourselves recursively and filtering the
 * output, so it's hacky. To do this, we need to get the full path to the
 * current program, there is a different way to get this information on nearly
 * every OS, but the thing we're testing is platform independent, so we should
 * be able to get away with just Linux here
*/
static int testname_cmp(const void *x_, const void *y_) {
    const char *x = *(const char *const*)x_;
    const char *y = *(const char *const*)y_;
    return strcmp(x, y);
}

/* Some bright spark decided -Werror and -Weverything should be used together,
 * which breaks idiomatic code... */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomma"
#endif
UTEST(utest_cmdline, filter_with_list) {
  // 64k should be enough for anyone
  char exe_buf[64 * 1024] = {0}, cmd_buf[64 * 1024] = {0};
  ssize_t path_len = readlink("/proc/self/exe", exe_buf, sizeof exe_buf);
  int count, ret;
  FILE *ps;
  const char **test_names;
  size_t n = 0, i = 0;
  char *lineptr;
  ASSERT_NE(path_len, UTEST_CAST(ssize_t, -1));
  count = snprintf(cmd_buf, sizeof cmd_buf, "%s --list-tests", exe_buf);
  ASSERT_EQ(errno, 0);
  ASSERT_LT(UTEST_CAST(size_t, count), sizeof cmd_buf);

  ps = popen(cmd_buf, "r");
  ASSERT_TRUE(ps);

  test_names =
      malloc(utest_state.tests_length * sizeof test_names[0]);
  ASSERT_TRUE(test_names);

  for (i = 0; i < utest_state.tests_length; ++i) {
    test_names[i] = utest_state.tests[i].name;
  }
  qsort(test_names, utest_state.tests_length, sizeof test_names[0],
        testname_cmp);

  lineptr = malloc(1);
  ASSERT_TRUE(lineptr);
  for (i = 0, n = 0; getline(&lineptr, &n, ps) != (ssize_t)-1; n = 0, ++i) {
    /* remove the terminating newline */
    const char **name;
    char *nl = strchr(lineptr, '\n');
    EXPECT_TRUE(nl);
    *nl = '\0';

    name = bsearch(&lineptr, test_names, utest_state.tests_length,
                                sizeof test_names[0], testname_cmp);
    EXPECT_TRUE(name);
    EXPECT_STREQ(*name, lineptr);
  }
  EXPECT_EQ(i, utest_state.tests_length);
  free(lineptr);
  free(test_names);
  ret = pclose(ps);
  ASSERT_EQ(ret, 0);
}
#endif
