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
#include "subprocess.h"

// TODO: Broken under MINGW for some reason.
#if !(defined(__MINGW32__) || defined(__MINGW64__))
UTEST(utest_cmdline, filter_with_list) {
  struct subprocess_s process;
  const char *command[3] = {"utest_test", "--list-tests", 0};
  int return_code;
  FILE *stdout_file;
  size_t index, kndex;
  char *hits;

// 64k should be enough for anyone
#define MAX_CHARS (64 * 1024)
  char buffer[MAX_CHARS] = {0};

  hits = (char *)malloc(utest_state.tests_length);
  memset(hits, 0, utest_state.tests_length);

  ASSERT_EQ(0,
            subprocess_create(command, subprocess_option_combined_stdout_stderr,
                              &process));

  stdout_file = subprocess_stdout(&process);

  for (index = 0; index < utest_state.tests_length; index++) {
    if (buffer != fgets(buffer, MAX_CHARS, stdout_file)) {
      break;
    }

#if defined(__clang__)
#if __has_warning("-Wdisabled-macro-expansion")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif
#endif

    // First wipe out the newlines from the fgets.
    for (kndex = 0;; kndex++) {
      if ((buffer[kndex] == '\r') || (buffer[kndex] == '\n')) {
        buffer[kndex] = '\0';
        break;
      }
    }

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
#endif

UTEST_MAIN()
