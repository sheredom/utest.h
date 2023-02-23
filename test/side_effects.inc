struct test_reader {
  int offset;
};

static int test_next(struct test_reader *r) {
  const int current = r->offset;
  r->offset += 1;
  return current;
}

static int test_bools[20] = {0, 1, 0, 1};
static int test_ints[20] = {42, 13, 6, -53};
static const char *test_strings[20] = {"42", "13", "6", "-53"};

UTEST(side_effects, EXPECT_TRUE_EXPECT_FALSE) {
  struct test_reader reader = {0};
  EXPECT_FALSE(test_bools[test_next(&reader)]);
  EXPECT_TRUE(test_bools[test_next(&reader)]);
  EXPECT_FALSE(test_bools[test_next(&reader)]);
  EXPECT_TRUE(test_bools[test_next(&reader)]);
}

UTEST(side_effects, EXPECT_EQ_EXPECT_NE) {
  struct test_reader reader = {0};
  EXPECT_EQ(42, test_ints[test_next(&reader)]);
  EXPECT_NE(14, test_ints[test_next(&reader)]);
  EXPECT_EQ(6, test_ints[test_next(&reader)]);
  EXPECT_NE(52, test_ints[test_next(&reader)]);
}

UTEST(side_effects, EXPECT_LT_EXPECT_LE) {
  struct test_reader reader = {0};
  EXPECT_LT(41, test_ints[test_next(&reader)]);
  EXPECT_LE(13, test_ints[test_next(&reader)]);
  EXPECT_LT(5, test_ints[test_next(&reader)]);
  EXPECT_LE(-53, test_ints[test_next(&reader)]);
}

UTEST(side_effects, EXPECT_GT_EXPECT_GE) {
  struct test_reader reader = {0};
  EXPECT_GT(43, test_ints[test_next(&reader)]);
  EXPECT_GE(13, test_ints[test_next(&reader)]);
  EXPECT_GT(7, test_ints[test_next(&reader)]);
  EXPECT_GE(-53, test_ints[test_next(&reader)]);
}

UTEST(side_effects, EXPECT_STREQ_EXPECT_STRNE) {
  struct test_reader reader = {0};
  EXPECT_STRNE("!42", test_strings[test_next(&reader)]);
  EXPECT_STREQ("13", test_strings[test_next(&reader)]);
  EXPECT_STRNE("!6", test_strings[test_next(&reader)]);
  EXPECT_STREQ("-53", test_strings[test_next(&reader)]);
}

UTEST(side_effects, EXPECT_STRNEQ_EXPECT_STRNEQ) {
  struct test_reader reader = {0};
  EXPECT_STRNNE("!42", test_strings[test_next(&reader)], 3);
  EXPECT_STRNEQ("13", test_strings[test_next(&reader)], 2);
  EXPECT_STRNNE("!6", test_strings[test_next(&reader)], 2);
  EXPECT_STRNEQ("-53", test_strings[test_next(&reader)], 3);
}

UTEST(side_effects, ASSERT_TRUE_ASSERT_FALSE) {
  struct test_reader reader = {0};
  ASSERT_FALSE(test_bools[test_next(&reader)]);
  ASSERT_TRUE(test_bools[test_next(&reader)]);
  ASSERT_FALSE(test_bools[test_next(&reader)]);
  ASSERT_TRUE(test_bools[test_next(&reader)]);
}

UTEST(side_effects, ASSERT_EQ_ASSERT_NE) {
  struct test_reader reader = {0};
  ASSERT_EQ(42, test_ints[test_next(&reader)]);
  ASSERT_NE(14, test_ints[test_next(&reader)]);
  ASSERT_EQ(6, test_ints[test_next(&reader)]);
  ASSERT_NE(52, test_ints[test_next(&reader)]);
}

UTEST(side_effects, ASSERT_LT_ASSERT_LE) {
  struct test_reader reader = {0};
  ASSERT_LT(41, test_ints[test_next(&reader)]);
  ASSERT_LE(13, test_ints[test_next(&reader)]);
  ASSERT_LT(5, test_ints[test_next(&reader)]);
  ASSERT_LE(-53, test_ints[test_next(&reader)]);
}

UTEST(side_effects, ASSERT_GT_ASSERT_GE) {
  struct test_reader reader = {0};
  ASSERT_GT(43, test_ints[test_next(&reader)]);
  ASSERT_GE(13, test_ints[test_next(&reader)]);
  ASSERT_GT(7, test_ints[test_next(&reader)]);
  ASSERT_GE(-53, test_ints[test_next(&reader)]);
}

UTEST(side_effects, ASSERT_STREQ_ASSERT_STRNE) {
  struct test_reader reader = {0};
  ASSERT_STRNE("!42", test_strings[test_next(&reader)]);
  ASSERT_STREQ("13", test_strings[test_next(&reader)]);
  ASSERT_STRNE("!6", test_strings[test_next(&reader)]);
  ASSERT_STREQ("-53", test_strings[test_next(&reader)]);
}

UTEST(side_effects, ASSERT_STRNEQ_ASSERT_STRNEQ) {
  struct test_reader reader = {0};
  ASSERT_STRNNE("!42", test_strings[test_next(&reader)], 3);
  ASSERT_STRNEQ("13", test_strings[test_next(&reader)], 2);
  ASSERT_STRNNE("!6", test_strings[test_next(&reader)], 2);
  ASSERT_STRNEQ("-53", test_strings[test_next(&reader)], 3);
}
