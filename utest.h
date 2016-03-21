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

#ifdef _MSC_VER
#pragma warning(push, 1)
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#if defined(_MSC_VER)
#if defined(_M_IX86)
#define _X86_
#endif

#if defined(_M_AMD64)
#define _AMD64_
#endif

#pragma warning(push, 1)
#include <winbase.h>
#include <windef.h>
#pragma warning(pop)

#elif defined(__linux__)

// slightly obscure include here - we need to include glibc's features.h, but
// we don't want to just include a header that might not be defined for other
// c libraries like musl. Instead we include limits.h, which we know on all
// glibc distributions includes features.h
#include <limits.h>

#if defined(__GLIBC__) && defined(__GLIBC_MINOR__)
#include <time.h>

#if ((2 < __GLIBC__) || ((2 == __GLIBC__) && (17 <= __GLIBC_MINOR__)))
// glibc is version 2.17 or above, so we can just use clock_gettime
#define UTEST_USE_CLOCKGETTIME
#else // ((2 < __GLIBC__) || ((2 == __GLIBC__) && (17 <= __GLIBC_MINOR__)))
#include <sys/syscall.h>
#include <unistd.h>
#endif // ((2 < __GLIBC__) || ((2 == __GLIBC__) && (17 <= __GLIBC_MINOR__)))
#endif // defined(__GLIBC__) && defined(__GLIBC_MINOR__)

#elif defined(__APPLE__)
#include <mach/mach_time.h>
#endif

#if defined(_MSC_VER)
#define UTEST_PRId64 "I64d"
#define UTEST_INLINE __forceinline

#pragma section(".CRT$XCU", read)
#define UTEST_INITIALIZER(f)                                                   \
  static void __cdecl f(void);                                                 \
  __declspec(allocate(".CRT$XCU")) void(__cdecl * f##_)(void) = f;             \
  static void __cdecl f(void)
#else
#include <inttypes.h>

#define UTEST_PRId64 PRId64
#define UTEST_INLINE inline

#define UTEST_INITIALIZER(f)                                                   \
  static void f(void) __attribute__((constructor));                            \
  static void f(void)
#endif

#if defined(__cplusplus)
#define UTEST_CAST(type, x) static_cast<type>(x)
#define UTEST_PTR_CAST(type, x) reinterpret_cast<type>(x)
#define UTEST_EXTERN extern "C"
#else
#define UTEST_CAST(type, x) ((type)x)
#define UTEST_PTR_CAST(type, x) ((type)x)
#define UTEST_EXTERN extern
#endif

static UTEST_INLINE int64_t utest_ns(void) {
#ifdef _MSC_VER
  LARGE_INTEGER counter;
  LARGE_INTEGER frequency;
  QueryPerformanceCounter(&counter);
  QueryPerformanceFrequency(&frequency);
  return UTEST_CAST(int64_t,
                    (counter.QuadPart * 1000000000) / frequency.QuadPart);
#elif defined(__linux)
  struct timespec ts;
  const clockid_t cid = CLOCK_REALTIME;
#if defined(UTEST_USE_CLOCKGETTIME)
  clock_gettime(cid, &ts);
#else
  syscall(SYS_clock_gettime, cid, &ts);
#endif
  return UTEST_CAST(int64_t, ts.tv_sec) * 1000 * 1000 * 1000 + ts.tv_nsec;
#elif __APPLE__
  return UTEST_CAST(int64_t, mach_absolute_time());
#endif
}

typedef void (*utest_testcase_t)(int *);

struct utest_test_state_s {
  utest_testcase_t testcase;
  const char *name;
};

struct utest_state_s {
  struct utest_test_state_s *tests;
  size_t tests_length;
};

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

#define ASSERT_STREQ(x, y)                                                     \
  if (0 != strcmp(x, y)) {                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
    return;                                                                    \
  }

#define ASSERT_STRNE(x, y)                                                     \
  if (0 == strcmp(x, y)) {                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
    return;                                                                    \
  }

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

#define EXPECT_STREQ(x, y)                                                     \
  if (0 != strcmp(x, y)) {                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
  }

#define EXPECT_STRNE(x, y)                                                     \
  if (0 == strcmp(x, y)) {                                                     \
    printf("%s:%u: Failure\n", __FILE__, __LINE__);                            \
    *utest_result = 1;                                                         \
  }

#define UTEST(SET, NAME)                                                       \
  UTEST_EXTERN struct utest_state_s utest_state;                               \
  static void utest_run_##SET##_##NAME(int *utest_result);                     \
  UTEST_INITIALIZER(utest_register_##SET##_##NAME) {                           \
    const size_t index = utest_state.tests_length++;                           \
    utest_state.tests =                                                        \
        UTEST_PTR_CAST(struct utest_test_state_s *,                            \
                       realloc(UTEST_PTR_CAST(void *, utest_state.tests),      \
                               sizeof(struct utest_test_state_s) *             \
                                   utest_state.tests_length));                 \
    utest_state.tests[index].testcase = &utest_run_##SET##_##NAME;             \
    utest_state.tests[index].name = #SET "." #NAME;                            \
  }                                                                            \
  void utest_run_##SET##_##NAME(int *utest_result)

#define UTEST_F_SETUP(FIXTURE)                                                 \
  static void utest_setup_##FIXTURE(int *utest_result, struct FIXTURE *fixture)

#define UTEST_F_TEARDOWN(FIXTURE)                                              \
  static void utest_teardown_##FIXTURE(int *utest_result,                      \
                                       struct FIXTURE *fixture)

#define UTEST_F(FIXTURE, NAME)                                                 \
  UTEST_EXTERN struct utest_state_s utest_state;                               \
  static void utest_run_##FIXTURE##_##NAME(int *, struct FIXTURE *);           \
  static void utest_fixture_##FIXTURE##_##NAME(int *utest_result) {            \
    struct FIXTURE fixture = {0};                                              \
    utest_setup_##FIXTURE(utest_result, &fixture);                             \
    if (0 != *utest_result) {                                                  \
      return;                                                                  \
    }                                                                          \
    utest_run_##FIXTURE##_##NAME(utest_result, &fixture);                      \
    utest_teardown_##FIXTURE(utest_result, &fixture);                          \
  }                                                                            \
  UTEST_INITIALIZER(utest_register_##FIXTURE##_##NAME) {                       \
    const size_t index = utest_state.tests_length++;                           \
    utest_state.tests =                                                        \
        UTEST_PTR_CAST(struct utest_test_state_s *,                            \
                       realloc(UTEST_PTR_CAST(void *, utest_state.tests),      \
                               sizeof(struct utest_test_state_s) *             \
                                   utest_state.tests_length));                 \
    utest_state.tests[index].testcase = &utest_fixture_##FIXTURE##_##NAME;     \
    utest_state.tests[index].name = #FIXTURE "." #NAME;                        \
  }                                                                            \
  void utest_run_##FIXTURE##_##NAME(int *utest_result, struct FIXTURE *fixture)

#define UTEST_MAIN()                                                           \
  UTEST_EXTERN struct utest_state_s utest_state;                               \
  struct utest_state_s utest_state;                                            \
  int main(void) {                                                             \
    size_t failed = 0;                                                         \
    size_t index = 0;                                                          \
    size_t *failed_tests = 0;                                                  \
    size_t failed_tests_length = 0;                                            \
    printf("\033[32m[==========]\033[0m Running %u test cases.\n",             \
           (unsigned)utest_state.tests_length);                                \
    for (index = 0; index < utest_state.tests_length; index++) {               \
      int result = 0;                                                          \
      int64_t ns = 0;                                                          \
      printf("\033[32m[ RUN      ]\033[0m %s\n",                               \
             utest_state.tests[index].name);                                   \
      ns = utest_ns();                                                         \
      utest_state.tests[index].testcase(&result);                              \
      ns = utest_ns() - ns;                                                    \
      if (0 != result) {                                                       \
        const size_t failed_test_index = failed_tests_length++;                \
        failed_tests = realloc(UTEST_PTR_CAST(void *, failed_tests),           \
                               sizeof(size_t) * failed_tests_length);          \
        failed_tests[failed_test_index] = index;                               \
        failed++;                                                              \
        printf("\033[31m[  FAILED  ]\033[0m %s (%" UTEST_PRId64 "ns)\n",       \
               utest_state.tests[index].name, ns);                             \
      } else {                                                                 \
        printf("\033[32m[       OK ]\033[0m %s (%" UTEST_PRId64 "ns)\n",       \
               utest_state.tests[index].name, ns);                             \
      }                                                                        \
    }                                                                          \
    printf("\033[32m[==========]\033[0m %u test cases ran.\n",                 \
           (unsigned)utest_state.tests_length);                                \
    printf("\033[32m[  PASSED  ]\033[0m %u tests.\n",                          \
           (unsigned)(utest_state.tests_length - failed));                     \
    if (0 != failed) {                                                         \
      printf("\033[31m[  FAILED  ]\033[0m %u tests, listed below:\n",          \
             (unsigned)failed);                                                \
      for (index = 0; index < failed_tests_length; index++) {                  \
        printf("\033[31m[  FAILED  ]\033[0m %s\n",                             \
               utest_state.tests[failed_tests[index]].name);                   \
      }                                                                        \
    }                                                                          \
    free(UTEST_PTR_CAST(void *, failed_tests));                                \
    free(UTEST_PTR_CAST(void *, utest_state.tests));                           \
    return (int)failed;                                                        \
  }

#endif // SHEREDOM_UTEST_H_INCLUDED
