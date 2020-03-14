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
#include "process.h"

UTEST(utest_cmdline, filter_with_list) {
  struct process_s process;
  const char *command[3] = {"utest_test", "--list-tests", 0};
  int return_code;
  FILE *stdout_file;
  size_t index;

// 64k should be enough for anyone
#define MAX_CHARS (64 * 1024)
  char buffer[MAX_CHARS] = {0};

  ASSERT_EQ(0, process_create(command, process_option_combined_stdout_stderr,
                              &process));

  ASSERT_EQ(0, process_join(&process, &return_code));
  ASSERT_EQ(0, return_code);

  stdout_file = process_stdout(&process);

  for (index = 0; index < utest_state.tests_length; index++) {
    ASSERT_EQ(buffer, fgets(buffer, MAX_CHARS, stdout_file));

#if defined(__clang__)
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif
#endif

    ASSERT_EQ(0, strncmp(buffer, utest_state.tests[index].name,
                         strlen(utest_state.tests[index].name)));

#if defined(__clang__)
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic pop
#endif
#endif
  }

  ASSERT_EQ(0, process_destroy(&process));
}

UTEST_MAIN()
