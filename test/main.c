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

// TODO: Fix in subprocess.h!
#if defined(__clang__)
#if __has_warning("-Wunsafe-buffer-usage")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4710)
#endif
#include "subprocess.h"
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

// TODO: Broken under MINGW for some reason.
#if !(defined(__MINGW32__) || defined(__MINGW64__))

// 64k should be enough for anyone
#define MAX_CHARS (64 * 1024)

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4711)
#endif

static size_t utest_cmdline_not_found(void) { return UTEST_CAST(size_t, -1); }

static void utest_cmdline_strip_newline(char *buffer) {
  size_t index;

  for (index = 0; '\0' != buffer[index]; index++) {
    if ((buffer[index] == '\r') || (buffer[index] == '\n')) {
      buffer[index] = '\0';
      break;
    }
  }
}

static int utest_cmdline_list_positions(const char *const *names,
                                        size_t names_length,
                                        size_t *positions) {
  struct subprocess_s process;
  const char *command[3] = {"utest_test", "--list-tests", 0};
  int return_code;
  FILE *stdout_file;
  size_t index;
  size_t line;
  char buffer[MAX_CHARS] = {0};

  for (index = 0; index < names_length; index++) {
    positions[index] = utest_cmdline_not_found();
  }

  if (0 != subprocess_create(command, subprocess_option_combined_stdout_stderr,
                             &process)) {
    return 1;
  }

  stdout_file = subprocess_stdout(&process);
  line = 0;

  while (buffer == fgets(buffer, MAX_CHARS, stdout_file)) {
    utest_cmdline_strip_newline(buffer);

    for (index = 0; index < names_length; index++) {
      if (0 == strcmp(buffer, names[index])) {
        positions[index] = line;
      }
    }

    line++;
  }

  if (0 != subprocess_join(&process, &return_code)) {
    (void)subprocess_destroy(&process);
    return 1;
  }

  if (0 != subprocess_destroy(&process)) {
    return 1;
  }

  return return_code;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

UTEST(utest_cmdline, filter_with_list) {
  struct subprocess_s process;
  const char *command[3] = {"utest_test", "--list-tests", 0};
  int return_code;
  FILE *stdout_file;
  size_t kndex;
  char *hits;

  char buffer[MAX_CHARS] = {0};

  hits = (char *)malloc(utest_state.tests_length);
  memset(hits, 0, utest_state.tests_length);

  ASSERT_EQ(0,
            subprocess_create(command, subprocess_option_combined_stdout_stderr,
                              &process));

  stdout_file = subprocess_stdout(&process);

  while (buffer == fgets(buffer, MAX_CHARS, stdout_file)) {

#if defined(__clang__)
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif
#endif

    // First wipe out the newlines from the fgets.
    utest_cmdline_strip_newline(buffer);

    // Record the hit for listed test.
    for (kndex = 0; kndex < utest_state.tests_length; kndex++) {
      if (0 == strcmp(buffer, utest_state.tests[kndex].name)) {
        ASSERT_EQ(hits[kndex], 0);
        hits[kndex] = 1;
        break;
      }
    }

#if defined(__clang__)
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic pop
#endif
#endif
  }

  ASSERT_EQ(0, subprocess_join(&process, &return_code));
  ASSERT_EQ(0, return_code);

  ASSERT_EQ(0, subprocess_destroy(&process));

  // Run through all the hits and make sure we got exactly one for each.
  for (kndex = 0; kndex < utest_state.tests_length; kndex++) {
    ASSERT_EQ(hits[kndex], 1);
  }

  free(hits);
}

UTEST(utest_cmdline, list_tests_same_line_sorted_by_name) {
  const char *const names[2] = {"utest_order_same_line.a",
                                "utest_order_same_line.b"};
  size_t positions[2];

  ASSERT_EQ(0, utest_cmdline_list_positions(
                   names, sizeof names / sizeof names[0], positions));
  ASSERT_NE(utest_cmdline_not_found(), positions[0]);
  ASSERT_NE(utest_cmdline_not_found(), positions[1]);
  ASSERT_LT(positions[0], positions[1]);
}

UTEST(utest_cmdline, list_tests_same_line_sorted_by_index) {
  const char *const names[12] = {"utest_order_indexed_fixture.many/0",
                                 "utest_order_indexed_fixture.many/1",
                                 "utest_order_indexed_fixture.many/2",
                                 "utest_order_indexed_fixture.many/3",
                                 "utest_order_indexed_fixture.many/4",
                                 "utest_order_indexed_fixture.many/5",
                                 "utest_order_indexed_fixture.many/6",
                                 "utest_order_indexed_fixture.many/7",
                                 "utest_order_indexed_fixture.many/8",
                                 "utest_order_indexed_fixture.many/9",
                                 "utest_order_indexed_fixture.many/10",
                                 "utest_order_indexed_fixture.many/11"};
  size_t positions[12];
  size_t index;

  ASSERT_EQ(0, utest_cmdline_list_positions(
                   names, sizeof names / sizeof names[0], positions));

  for (index = 0; index < sizeof positions / sizeof positions[0]; index++) {
    ASSERT_NE(utest_cmdline_not_found(), positions[index]);
  }

  for (index = 1; index < sizeof positions / sizeof positions[0]; index++) {
    ASSERT_LT(positions[index - 1], positions[index]);
  }
}
#endif

/* utest_should_filter_test returns 0 to run a test and 1 to skip it. These
   call it directly rather than spawning a binary, so they also run on MinGW. */

UTEST(utest_filter, exact_name) {
  EXPECT_EQ(0, utest_should_filter_test("foo.bar", "foo.bar"));
  EXPECT_EQ(1, utest_should_filter_test("foo.baz", "foo.bar"));
}

UTEST(utest_filter, no_filter_runs_everything) {
  EXPECT_EQ(0, utest_should_filter_test(UTEST_NULL, "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*", "foo.bar"));
}

UTEST(utest_filter, leading_and_trailing_wildcards) {
  EXPECT_EQ(0, utest_should_filter_test("foo.*", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*bar", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*.ba*", "foo.bar"));
  EXPECT_EQ(1, utest_should_filter_test("*baz*", "foo.bar"));
}

/* A wildcard may stand for nothing, so a trailing one must still match when
   the literal part reached the end of the name. */
UTEST(utest_filter, trailing_wildcard_matches_empty_remainder) {
  EXPECT_EQ(0, utest_should_filter_test("*bar*", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("foo.bar*", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*foo.bar*", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*bar**", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*", ""));
}

/* The same shape, but the filter still has literal characters left over. */
UTEST(utest_filter, literals_after_an_exhausted_name_do_not_match) {
  EXPECT_EQ(1, utest_should_filter_test("*bar*baz", "foo.bar"));
  EXPECT_EQ(1, utest_should_filter_test("foo.bar.", "foo.bar"));
}

/* A wildcard must be able to give characters back when the first place its
   literal matched turns out to be the wrong one. */
UTEST(utest_filter, wildcard_backtracks) {
  EXPECT_EQ(0, utest_should_filter_test("*o.b*", "foo.bar"));
  EXPECT_EQ(0, utest_should_filter_test("*a*a*", "banana"));
  EXPECT_EQ(0, utest_should_filter_test("*ana*na", "banana"));
  EXPECT_EQ(0, utest_should_filter_test("*oo*ar", "foo.bar"));
  EXPECT_EQ(1, utest_should_filter_test("*oo*az", "foo.bar"));
}

UTEST_MAIN()
