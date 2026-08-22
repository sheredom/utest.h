/* Shared test cases for utest.h.

   Each test translation unit must define UTEST_TEST_SUITE before including this
   header: #define UTEST_TEST_SUITE c #include "test_shared.h"

   The wrapper macros expand UTEST_TEST_SUITE before UTEST token pasting, giving
   each standard-specific translation unit unique test symbols and fixtures.
*/

#ifndef UTEST_TEST_SUITE
#error "Define UTEST_TEST_SUITE before including test_shared.h"
#endif

#ifdef _MSC_VER
/* disable 'conditional expression is constant' - our examples below use this! */
#pragma warning(disable : 4127)
#endif

#if defined(__cplusplus) && !defined(UTEST_TEST_NO_EXCEPTIONS)
#include <stdexcept>
#endif

#define UTEST_TEST_NAME3(prefix, name) prefix##_##name
#define UTEST_TEST_NAME2(prefix, name) UTEST_TEST_NAME3(prefix, name)
#define UTEST_TEST2(suite, name) UTEST(suite, name)
#define UTEST_TEST(name) UTEST_TEST2(UTEST_TEST_SUITE, name)

#define UTEST_TEST_FIXTURE(fixture)                                            \
  UTEST_TEST_NAME2(UTEST_TEST_SUITE, fixture)
#define UTEST_TEST_F_SETUP2(fixture) UTEST_F_SETUP(fixture)
#define UTEST_TEST_F_SETUP(fixture)                                            \
  UTEST_TEST_F_SETUP2(UTEST_TEST_FIXTURE(fixture))
#define UTEST_TEST_F_TEARDOWN2(fixture) UTEST_F_TEARDOWN(fixture)
#define UTEST_TEST_F_TEARDOWN(fixture)                                         \
  UTEST_TEST_F_TEARDOWN2(UTEST_TEST_FIXTURE(fixture))
#define UTEST_TEST_F2(fixture, name) UTEST_F(fixture, name)
#define UTEST_TEST_F(fixture, name)                                            \
  UTEST_TEST_F2(UTEST_TEST_FIXTURE(fixture), name)
#define UTEST_TEST_I_SETUP2(fixture) UTEST_I_SETUP(fixture)
#define UTEST_TEST_I_SETUP(fixture)                                            \
  UTEST_TEST_I_SETUP2(UTEST_TEST_FIXTURE(fixture))
#define UTEST_TEST_I_TEARDOWN2(fixture) UTEST_I_TEARDOWN(fixture)
#define UTEST_TEST_I_TEARDOWN(fixture)                                         \
  UTEST_TEST_I_TEARDOWN2(UTEST_TEST_FIXTURE(fixture))
#define UTEST_TEST_I2(fixture, name, index) UTEST_I(fixture, name, index)
#define UTEST_TEST_I(fixture, name, index)                                     \
  UTEST_TEST_I2(UTEST_TEST_FIXTURE(fixture), name, index)

#if defined(__cplusplus) &&                                                    \
    ((__cplusplus >= 201103L) || (defined(_MSC_VER) && (_MSC_VER >= 1900)))
#define UTEST_TEST_HAS_CPP11 1
#endif

#if !defined(__TINYC__) &&                                                     \
    (!defined(__cplusplus) || defined(UTEST_TEST_HAS_CPP11))
struct UtestOpaque;

UTEST_TEST(OPAQUE_POINTER_NULL) {
  struct UtestOpaque *opaque = UTEST_NULL;
  struct UtestOpaque *expected = UTEST_NULL;
  EXPECT_EQ(expected, opaque);
  ASSERT_EQ(expected, opaque);
}
#endif

UTEST_TEST(ASSERT_TRUE) { ASSERT_TRUE(1); }

UTEST_TEST(ASSERT_FALSE) { ASSERT_FALSE(0); }

UTEST_TEST(ASSERT_EQ) { ASSERT_EQ(1, 1); }

UTEST_TEST(ASSERT_NE) { ASSERT_NE(1, 2); }

UTEST_TEST(ASSERT_LT) { ASSERT_LT(1, 2); }

UTEST_TEST(ASSERT_LE) {
  ASSERT_LE(1, 1);
  ASSERT_LE(1, 2);
}

UTEST_TEST(ASSERT_GT) { ASSERT_GT(2, 1); }

UTEST_TEST(ASSERT_GE) {
  ASSERT_GE(1, 1);
  ASSERT_GE(2, 1);
}

UTEST_TEST(ASSERT_MEMEQ) {
  const char a1[4] = {1, 2, 3, 4};
  const char a2[4] = {1, 2, 3, 4};
  ASSERT_MEMEQ(a1, a2, 4);
}

UTEST_TEST(EXPECT_MEMEQ) {
  const char a1[4] = {1, 2, 3, 4};
  const char a2[4] = {1, 2, 3, 4};
  EXPECT_MEMEQ(a1, a2, 4);
}

UTEST_TEST(ASSERT_STREQ) { ASSERT_STREQ("foo", "foo"); }

UTEST_TEST(ASSERT_STRNE) { ASSERT_STRNE("foo", "bar"); }

UTEST_TEST(ASSERT_STRNEQ) { ASSERT_STRNEQ("foo", "foobar", strlen("foo")); }

UTEST_TEST(ASSERT_STRNNE) { ASSERT_STRNNE("foo", "barfoo", strlen("foo")); }

UTEST_TEST(EXPECT_TRUE) { EXPECT_TRUE(1); }

UTEST_TEST(EXPECT_FALSE) { EXPECT_FALSE(0); }

UTEST_TEST(EXPECT_EQ) { EXPECT_EQ(1, 1); }

UTEST_TEST(EXPECT_NE) { EXPECT_NE(1, 2); }

UTEST_TEST(EXPECT_LT) { EXPECT_LT(1, 2); }

UTEST_TEST(EXPECT_LE) {
  EXPECT_LE(1, 1);
  EXPECT_LE(1, 2);
}

UTEST_TEST(EXPECT_GT) { EXPECT_GT(2, 1); }

UTEST_TEST(EXPECT_GE) {
  EXPECT_GE(1, 1);
  EXPECT_GE(2, 1);
}

UTEST_TEST(EXPECT_STREQ) { EXPECT_STREQ("foo", "foo"); }

UTEST_TEST(EXPECT_STRNE) { EXPECT_STRNE("foo", "bar"); }

UTEST_TEST(EXPECT_STRNEQ) { EXPECT_STRNEQ("foo", "foobar", strlen("foo")); }

UTEST_TEST(EXPECT_STRNNE) { EXPECT_STRNNE("foo", "barfoo", strlen("foo")); }

UTEST_TEST(ASSERT_TRUE_MSG) { ASSERT_TRUE_MSG(1, "custom message"); }

UTEST_TEST(ASSERT_FALSE_MSG) { ASSERT_FALSE_MSG(0, "custom message"); }

UTEST_TEST(ASSERT_EQ_MSG) { ASSERT_EQ_MSG(1, 1, "custom message"); }

UTEST_TEST(ASSERT_NE_MSG) { ASSERT_NE_MSG(1, 2, "custom message"); }

UTEST_TEST(ASSERT_LT_MSG) { ASSERT_LT_MSG(1, 2, "custom message"); }

UTEST_TEST(ASSERT_LE_MSG) {
  ASSERT_LE_MSG(1, 1, "custom message");
  ASSERT_LE_MSG(1, 2, "custom message");
}

UTEST_TEST(ASSERT_GT_MSG) { ASSERT_GT_MSG(2, 1, "custom message"); }

UTEST_TEST(ASSERT_GE_MSG) {
  ASSERT_GE_MSG(1, 1, "custom message");
  ASSERT_GE_MSG(2, 1, "custom message");
}

UTEST_TEST(ASSERT_MEMEQ_MSG) {
  const char a1[4] = {1, 2, 3, 4};
  const char a2[4] = {1, 2, 3, 4};
  ASSERT_MEMEQ_MSG(a1, a2, 4, "custom message");
}

UTEST_TEST(ASSERT_STREQ_MSG) {
  ASSERT_STREQ_MSG("foo", "foo", "custom message");
}

UTEST_TEST(ASSERT_STRNE_MSG) {
  ASSERT_STRNE_MSG("foo", "bar", "custom message");
}

UTEST_TEST(ASSERT_STRNEQ_MSG) {
  ASSERT_STRNEQ_MSG("foo", "foobar", strlen("foo"), "custom message");
}

UTEST_TEST(ASSERT_STRNNE_MSG) {
  ASSERT_STRNNE_MSG("foo", "barfoo", strlen("foo"), "custom message");
}

UTEST_TEST(ASSERT_NEAR_MSG) {
  ASSERT_NEAR_MSG(42.0f, 42.01f, 0.01f, "custom message");
}

UTEST_TEST(EXPECT_TRUE_MSG) { EXPECT_TRUE_MSG(1, "custom message"); }

UTEST_TEST(EXPECT_FALSE_MSG) { EXPECT_FALSE_MSG(0, "custom message"); }

UTEST_TEST(EXPECT_EQ_MSG) { EXPECT_EQ_MSG(1, 1, "custom message"); }

UTEST_TEST(EXPECT_NE_MSG) { EXPECT_NE_MSG(1, 2, "custom message"); }

UTEST_TEST(EXPECT_LT_MSG) { EXPECT_LT_MSG(1, 2, "custom message"); }

UTEST_TEST(EXPECT_LE_MSG) {
  EXPECT_LE_MSG(1, 1, "custom message");
  EXPECT_LE_MSG(1, 2, "custom message");
}

UTEST_TEST(EXPECT_GT_MSG) { EXPECT_GT_MSG(2, 1, "custom message"); }

UTEST_TEST(EXPECT_GE_MSG) {
  EXPECT_GE_MSG(1, 1, "custom message");
  EXPECT_GE_MSG(2, 1, "custom message");
}

UTEST_TEST(EXPECT_MEMEQ_MSG) {
  const char a1[4] = {1, 2, 3, 4};
  const char a2[4] = {1, 2, 3, 4};
  EXPECT_MEMEQ_MSG(a1, a2, 4, "custom message");
}

UTEST_TEST(EXPECT_STREQ_MSG) {
  EXPECT_STREQ_MSG("foo", "foo", "custom message");
}

UTEST_TEST(EXPECT_STRNE_MSG) {
  EXPECT_STRNE_MSG("foo", "bar", "custom message");
}

UTEST_TEST(EXPECT_STRNEQ_MSG) {
  EXPECT_STRNEQ_MSG("foo", "foobar", strlen("foo"), "custom message");
}

UTEST_TEST(EXPECT_STRNNE_MSG) {
  EXPECT_STRNNE_MSG("foo", "barfoo", strlen("foo"), "custom message");
}

UTEST_TEST(EXPECT_NEAR_MSG) {
  EXPECT_NEAR_MSG(42.0f, 42.01f, 0.01f, "custom message");
}

UTEST_TEST(no_double_eval) {
  int i = 0;
  ASSERT_EQ(i++, 0);
  ASSERT_EQ(i, 1);
}

#if defined(UTEST_TEST_HAS_CPP11)
UTEST_TEST(bool_eval) {
  bool i = false;
  ASSERT_EQ(i, false);
  i = true;
  ASSERT_EQ(i, true);
}
#endif

struct UTEST_TEST_FIXTURE(MyTestF) {
  int foo;
};

UTEST_TEST_F_SETUP(MyTestF) {
  ASSERT_EQ(0, utest_fixture->foo);
  utest_fixture->foo = 42;
}

UTEST_TEST_F_TEARDOWN(MyTestF) { ASSERT_EQ(13, utest_fixture->foo); }

UTEST_TEST_F(MyTestF, first) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

UTEST_TEST_F(MyTestF, second) {
  ASSERT_EQ(42, utest_fixture->foo);
  utest_fixture->foo = 13;
}

struct UTEST_TEST_FIXTURE(MyTestI) {
  size_t foo;
  size_t bar;
};

UTEST_TEST_I_SETUP(MyTestI) {
  ASSERT_EQ(0u, utest_fixture->foo);
  ASSERT_EQ(0u, utest_fixture->bar);
  utest_fixture->foo = 42;
  utest_fixture->bar = utest_index;
}

UTEST_TEST_I_TEARDOWN(MyTestI) {
  ASSERT_EQ(13u, utest_fixture->foo);
  ASSERT_EQ(utest_index, utest_fixture->bar);
}

UTEST_TEST_I(MyTestI, first, 2) {
  ASSERT_GT(2u, utest_fixture->bar);
  utest_fixture->foo = 13;
}

UTEST_TEST_I(MyTestI, second, 128) {
  ASSERT_GT(128u, utest_fixture->bar);
  utest_fixture->foo = 13;
}

UTEST_TEST(Float) {
  float a = 1;
  float b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(Double) {
  double a = 1;
  double b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(LongDouble) {
  long double a = 1;
  long double b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(Char) {
  char a = 1;
  char b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(SignedChar) {
  signed char a = 1;
  signed char b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(UChar) {
  unsigned char a = 1;
  unsigned char b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(Short) {
  short a = 1;
  short b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(UShort) {
  unsigned short a = 1;
  unsigned short b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(Int) {
  int a = 1;
  int b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(UInt) {
  unsigned int a = 1;
  unsigned int b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(Long) {
  long a = 1;
  long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(ULong) {
  unsigned long a = 1;
  unsigned long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

#if defined(UTEST_TEST_HAS_CPP11)
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

UTEST_TEST(LongLong) {
  long long a = 1;
  long long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

UTEST_TEST(ULongLong) {
  unsigned long long a = 1;
  unsigned long long b = 2;
  EXPECT_NE(a, b);
  ASSERT_NE(a, b);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

#if defined(__clang__)
#if __has_warning("-Wunsafe-buffer-usage")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif

UTEST_TEST(Ptr) {
  char foo = 42;
  EXPECT_NE(&foo, &foo + 1);
}

#if !defined(__cplusplus)
UTEST_TEST(VoidPtr) {
  void *foo = 0;
  EXPECT_NE(foo, (char *)foo + 1);
}
#elif defined(UTEST_TEST_HAS_CPP11)
UTEST_TEST(VoidPtr) {
  void *foo = reinterpret_cast<void *>(0);
  EXPECT_NE(foo, static_cast<char *>(foo) + 1);
}
#endif

static const int UTEST_TEST_FIXTURE(data)[4] = {42, 13, 6, -53};

UTEST_TEST(Array) { EXPECT_NE(UTEST_TEST_FIXTURE(data), UTEST_TEST_FIXTURE(data) + 1); }

#if defined(__clang__)
#if __has_warning("-Wunsafe-buffer-usage")
#pragma clang diagnostic pop
#endif
#endif

UTEST_TEST(Near) {
  float a = 42.0f;
  float b = 42.01f;
  EXPECT_NEAR(a, b, 0.01f);
  ASSERT_NEAR(a, b, 0.01f);
}

#if defined(__cplusplus) && !defined(UTEST_TEST_NO_EXCEPTIONS)
/* GCC stdlib has a sanitizer bug in exceptions! */
#if defined(__has_feature)
#if __has_feature(memory_sanitizer)
#define MEMORY_SANITIZER
#endif
#endif

#if defined(MEMORY_SANITIZER)
__attribute__((no_sanitize("memory")))
#endif
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4710)
#endif
static int UTEST_TEST_FIXTURE(foo)(int bar) {
  if (bar == 1)
    throw std::range_error("bad bar");
  return bar + 1;
}
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

UTEST_TEST(Exception) {
  EXPECT_EXCEPTION(UTEST_TEST_FIXTURE(foo)(1), std::range_error);
  ASSERT_EXCEPTION(UTEST_TEST_FIXTURE(foo)(1), std::range_error);
}

UTEST_TEST(EXPECT_EXCEPTION_MSG) {
  EXPECT_EXCEPTION_MSG(UTEST_TEST_FIXTURE(foo)(1), std::range_error,
                       "custom message");
}

UTEST_TEST(ASSERT_EXCEPTION_MSG) {
  ASSERT_EXCEPTION_MSG(UTEST_TEST_FIXTURE(foo)(1), std::range_error,
                       "custom message");
}

#if !defined(MEMORY_SANITIZER)
UTEST_TEST(ExceptionWithMessage) {
  EXPECT_EXCEPTION_WITH_MESSAGE(UTEST_TEST_FIXTURE(foo)(1), std::range_error,
                                "bad bar");
  ASSERT_EXCEPTION_WITH_MESSAGE(UTEST_TEST_FIXTURE(foo)(1), std::range_error,
                                "bad bar");
}

UTEST_TEST(EXPECT_EXCEPTION_WITH_MESSAGE_MSG) {
  EXPECT_EXCEPTION_WITH_MESSAGE_MSG(UTEST_TEST_FIXTURE(foo)(1),
                                    std::range_error, "bad bar",
                                    "custom message");
}

UTEST_TEST(ASSERT_EXCEPTION_WITH_MESSAGE_MSG) {
  ASSERT_EXCEPTION_WITH_MESSAGE_MSG(UTEST_TEST_FIXTURE(foo)(1),
                                    std::range_error, "bad bar",
                                    "custom message");
}
#endif
#endif

UTEST_TEST(Todo) { UTEST_SKIP("Not yet implemented!"); }

#if defined(__cplusplus)
enum UTEST_TEST_FIXTURE(SomeEnum) { UTEST_TEST_FIXTURE(SomeEnumFoo), UTEST_TEST_FIXTURE(SomeEnumBar) };

UTEST_TEST(Enum) {
  EXPECT_NE(UTEST_TEST_FIXTURE(SomeEnumFoo), UTEST_TEST_FIXTURE(SomeEnumBar));
  ASSERT_EQ(UTEST_TEST_FIXTURE(SomeEnumFoo), UTEST_TEST_FIXTURE(SomeEnumFoo));
}

UTEST_TEST(Modulo) {
  int c = 42;
  EXPECT_NE(c % 16, 0);
  EXPECT_NE(0, c % 16);
  ASSERT_EQ(10, c % 16);
}
#endif

#if defined(UTEST_TEST_HAS_CPP11)
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

enum class UTEST_TEST_FIXTURE(SomeEnumClass) { Foo, Bar };

UTEST_TEST(EnumClass) {
  EXPECT_NE(UTEST_TEST_FIXTURE(SomeEnumClass)::Foo,
            UTEST_TEST_FIXTURE(SomeEnumClass)::Bar);
  ASSERT_EQ(UTEST_TEST_FIXTURE(SomeEnumClass)::Foo,
            UTEST_TEST_FIXTURE(SomeEnumClass)::Foo);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

UTEST_TEST(Null) {
  EXPECT_EQ(nullptr, nullptr);
  ASSERT_EQ(nullptr, nullptr);
}

struct UTEST_TEST_FIXTURE(SomeStruct) {
  int a;
  bool operator<(const UTEST_TEST_FIXTURE(SomeStruct) &other) const {
    return a < other.a;
  }
};

UTEST_TEST(CustomType) {
  UTEST_TEST_FIXTURE(SomeStruct) s1 = {3};
  UTEST_TEST_FIXTURE(SomeStruct) s2 = {4};
  EXPECT_LT(s1, s2);
}
#endif
