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
