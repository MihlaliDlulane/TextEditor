#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int tests_passed;
  int tests_total;
  int tests_failed;
  bool verbose;
  const char *current_suite;
} TestFramework;

/* Core functions */
void init_test_framework(TestFramework *tf);
void set_verbose(TestFramework *tf, bool verbose);
void begin_test_suite(TestFramework *tf, const char *suite_name);
void print_summary(TestFramework *tf);
int get_exit_code(TestFramework *tf);

/* Assertion functions */
void assert_true(TestFramework *tf, const char *test_name, bool condition);
void assert_false(TestFramework *tf, const char *test_name, bool condition);
void assert_equal_str(TestFramework *tf, const char *test_name,
                      const char *actual, const char *expected);
void assert_equal_int(TestFramework *tf, const char *test_name, int actual,
                      int expected);
void assert_equal_float(TestFramework *tf, const char *test_name, double actual,
                        double expected, double epsilon);
void assert_not_null(TestFramework *tf, const char *test_name, const void *ptr);
void assert_null(TestFramework *tf, const char *test_name, const void *ptr);

/* Convenience macros */
#define ASSERT_TRUE(tf, name, condition) assert_true(tf, name, condition)
#define ASSERT_FALSE(tf, name, condition) assert_false(tf, name, condition)
#define ASSERT_EQ_STR(tf, name, actual, expected)                              \
  assert_equal_str(tf, name, actual, expected)
#define ASSERT_EQ_INT(tf, name, actual, expected)                              \
  assert_equal_int(tf, name, actual, expected)
#define ASSERT_EQ_FLOAT(tf, name, actual, expected, eps)                       \
  assert_equal_float(tf, name, actual, expected, eps)
#define ASSERT_NOT_NULL(tf, name, ptr) assert_not_null(tf, name, ptr)
#define ASSERT_NULL(tf, name, ptr) assert_null(tf, name, ptr)

#endif
