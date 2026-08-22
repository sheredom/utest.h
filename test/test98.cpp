#include "utest.h"

#define UTEST_TEST_SUITE cpp98
#include "test_shared.h"

#if __cplusplus < 201103L
UTEST(cpp98_type_eval, arrays_decay_to_pointers) {
  int left[] = {1};
  int right[] = {1};
  EXPECT_NE(left, right);
}
#endif
