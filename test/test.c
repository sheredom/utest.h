#include "utest.h"

#define UTEST_TEST_SUITE c
#include "test_shared.h"

UTEST(c_type_eval, preserves_narrow_unsigned_type) {
  uint8_t narrow = 1;
  size_t wide = 1;
  EXPECT_EQ(narrow, wide);
}

UTEST(c_type_eval, arrays_decay_to_pointers) {
  int left[] = {1};
  int right[] = {1};
  EXPECT_NE(left, right);
}
