// The latest version of this library is available on GitHub;
//   https://github.com/sheredom/utest.h

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

#ifndef SHEREDOM_UTEST_H_INCLUDED
#define SHEREDOM_UTEST_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#else
#include <time.h>
#endif

#if defined(__cplusplus)
#define UTEST_CAST(type, x) static_cast<type>(x)
#define UTEST_PTR_CAST(type, x) reinterpret_cast<type>(x)
#else
#define UTEST_CAST(type, x) ((type)x)
#define UTEST_PTR_CAST(type, x) ((type)x)
#endif

static inline long utest_ns() {
#ifdef _MSC_VER
#else
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return UTEST_CAST(long, ts.tv_sec) * 1000 * 1000 * 1000 + ts.tv_nsec;
#endif
}

typedef void (*utest_testcase_t)(int *);

struct utest_state_s {
  utest_testcase_t *testcases;
  const char **testcase_names;
  size_t testcases_length;
};

#ifdef _MSC_VER
#pragma section(".CRT$XCU", read)
#define UTEST_INITIALIZER(f)                                                   \
  static void __cdecl f(void);                                                 \
  __declspec(allocate(".CRT$XCU")) void(__cdecl * f##_)(void) = f;             \
  static void __cdecl f(void)
#else
#define UTEST_INITIALIZER(f)                                                   \
  static void f(void) __attribute__((constructor));                            \
  static void f(void)
#endif

#define UTEST_ASSERT(x, y, cond)                                               \
  if (!((x)cond(y))) {                                                         \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
    return;                                                                    \
  }

#define ASSERT_TRUE(x)                                                         \
  if (!(x)) {                                                                  \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
    return;                                                                    \
  }

#define ASSERT_FALSE(x)                                                        \
  if (x) {                                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
    return;                                                                    \
  }

#define ASSERT_EQ(x, y) UTEST_ASSERT(x, y, ==)
#define ASSERT_NE(x, y) UTEST_ASSERT(x, y, !=)
#define ASSERT_LT(x, y) UTEST_ASSERT(x, y, <)
#define ASSERT_LE(x, y) UTEST_ASSERT(x, y, <=)
#define ASSERT_GT(x, y) UTEST_ASSERT(x, y, >)
#define ASSERT_GE(x, y) UTEST_ASSERT(x, y, >=)

#define UTEST_EXPECT(x, y, cond)                                               \
  if (!((x)cond(y))) {                                                         \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
  }

#define EXPECT_TRUE(x)                                                         \
  if (!(x)) {                                                                  \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
  }

#define EXPECT_FALSE(x)                                                        \
  if (x) {                                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
  }

#define EXPECT_EQ(x, y) UTEST_EXPECT(x, y, ==)
#define EXPECT_NE(x, y) UTEST_EXPECT(x, y, !=)
#define EXPECT_LT(x, y) UTEST_EXPECT(x, y, <)
#define EXPECT_LE(x, y) UTEST_EXPECT(x, y, <=)
#define EXPECT_GT(x, y) UTEST_EXPECT(x, y, >)
#define EXPECT_GE(x, y) UTEST_EXPECT(x, y, >=)

#define TESTCASE(set, name)                                                    \
  extern struct utest_state_s utest_state;                                     \
  static void utest_run_##set##_##name(int *utest_result);                     \
  UTEST_INITIALIZER(utest_register_##set##_##name) {                           \
    const size_t index = utest_state.testcases_length++;                       \
    utest_state.testcases = UTEST_PTR_CAST(                                    \
        utest_testcase_t *,                                                    \
        realloc(utest_state.testcases,                                         \
                sizeof(utest_testcase_t) * utest_state.testcases_length));     \
    utest_state.testcases[index] = &utest_run_##set##_##name;                  \
    utest_state.testcase_names = UTEST_PTR_CAST(                               \
        const char **,                                                         \
        realloc(utest_state.testcase_names,                                    \
                sizeof(char *) * utest_state.testcases_length));               \
    utest_state.testcase_names[index] = #set "." #name;                        \
  }                                                                            \
  void utest_run_##set##_##name(int *utest_result)

#define UTEST_MAIN()                                                           \
  extern struct utest_state_s utest_state;                                     \
  struct utest_state_s utest_state;                                            \
  int main() {                                                                 \
    size_t failed = 0;                                                         \
    size_t index = 0;                                                          \
    size_t *failed_testcases = 0;                                              \
    size_t failed_testcases_length = 0;                                        \
    printf("\033[32m[==========]\033[0m Running %u test cases.\n",             \
           (unsigned)utest_state.testcases_length);                            \
    for (index = 0; index < utest_state.testcases_length; index++) {           \
      int result = 0;                                                          \
      long ns = 0;                                                             \
      printf("\033[32m[ RUN      ]\033[0m %s\n",                               \
             utest_state.testcase_names[index]);                               \
      ns = utest_ns();                                                         \
      utest_state.testcases[index](&result);                                   \
      ns = utest_ns() - ns;                                                    \
      if (0 != result) {                                                       \
        const size_t failed_testcase_index = failed_testcases_length++;        \
        failed_testcases = realloc(failed_testcases,                           \
                                   sizeof(size_t) * failed_testcases_length);  \
        failed_testcases[failed_testcase_index] = index;                       \
        failed++;                                                              \
        printf("\033[31m[  FAILED  ]\033[0m %s (%ldns)\n",                     \
               utest_state.testcase_names[index], ns);                         \
      } else {                                                                 \
        printf("\033[32m[       OK ]\033[0m %s (%ldns)\n",                     \
               utest_state.testcase_names[index], ns);                         \
      }                                                                        \
    }                                                                          \
    printf("\033[32m[==========]\033[0m %u test cases ran.\n",                 \
           (unsigned)utest_state.testcases_length);                            \
    printf("\033[32m[  PASSED  ]\033[0m %u tests.\n",                          \
           (unsigned)(utest_state.testcases_length - failed));                 \
    if (0 != failed) {                                                         \
      printf("\033[31m[  FAILED  ]\033[0m %u tests, listed below:\n",          \
             (unsigned)failed);                                                \
      for (index = 0; index < failed_testcases_length; index++) {              \
        printf("\033[31m[  FAILED  ]\033[0m %s\n",                             \
               utest_state.testcase_names[failed_testcases[index]]);           \
      }                                                                        \
    }                                                                          \
    free(failed_testcases);                                                    \
    free(utest_state.testcases);                                               \
    free(utest_state.testcase_names);                                          \
    return (int)failed;                                                        \
  }

#endif // SHEREDOM_UTEST_H_INCLUDED
