#include "test_framework.h"
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ANSI color codes */
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"

/* Simple check for color support - assumes most terminals support colors */
static bool should_use_colors(void) {
  const char *term = getenv("TERM");
  const char *no_color = getenv("NO_COLOR");

  /* Don't use colors if NO_COLOR is set */
  if (no_color != NULL) {
    return false;
  }

  /* Use colors if TERM is set and not "dumb" */
  if (term != NULL && strcmp(term, "dumb") != 0) {
    return true;
  }

  return false;
}

/* Color-aware printing */
static void print_colored(const char *color, const char *format, ...) {
  va_list args;
  va_start(args, format);

  if (should_use_colors()) {
    printf("%s", color);
    vprintf(format, args);
    printf("%s", RESET);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

void init_test_framework(TestFramework *tf) {
  tf->tests_passed = 0;
  tf->tests_total = 0;
  tf->tests_failed = 0;
  tf->verbose = true;
  tf->current_suite = NULL;
}

void set_verbose(TestFramework *tf, bool verbose) { tf->verbose = verbose; }

void begin_test_suite(TestFramework *tf, const char *suite_name) {
  tf->current_suite = suite_name;
  if (tf->verbose) {
    print_colored(BLUE BOLD, "\n=== Test Suite: %s ===\n", suite_name);
  }
}

static void print_test_result(TestFramework *tf, const char *test_name,
                              bool passed, const char *message) {
  tf->tests_total++;

  if (passed) {
    tf->tests_passed++;
    if (tf->verbose) {
      if (tf->current_suite) {
        print_colored(GREEN, "[PASS] [%s] %s\n", tf->current_suite, test_name);
      } else {
        print_colored(GREEN, "[PASS] %s\n", test_name);
      }
    }
  } else {
    tf->tests_failed++;
    if (tf->current_suite) {
      print_colored(RED, "[FAIL] [%s] %s - %s\n", tf->current_suite, test_name,
                    message);
    } else {
      print_colored(RED, "[FAIL] %s - %s\n", test_name, message);
    }
  }
}

void assert_true(TestFramework *tf, const char *test_name, bool condition) {
  if (condition) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    print_test_result(tf, test_name, false, "Expected true, got false");
  }
}

void assert_false(TestFramework *tf, const char *test_name, bool condition) {
  if (!condition) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    print_test_result(tf, test_name, false, "Expected false, got true");
  }
}

void assert_equal_str(TestFramework *tf, const char *test_name,
                      const char *actual, const char *expected) {
  char msg[512];

  /* Handle NULL pointers */
  if (actual == NULL && expected == NULL) {
    print_test_result(tf, test_name, true, NULL);
    return;
  }

  if (actual == NULL) {
    snprintf(msg, sizeof(msg), "Expected '%s', got NULL", expected);
    print_test_result(tf, test_name, false, msg);
    return;
  }

  if (expected == NULL) {
    snprintf(msg, sizeof(msg), "Expected NULL, got '%s'", actual);
    print_test_result(tf, test_name, false, msg);
    return;
  }

  if (strcmp(actual, expected) == 0) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    snprintf(msg, sizeof(msg), "Expected '%s', got '%s'", expected, actual);
    print_test_result(tf, test_name, false, msg);
  }
}

void assert_equal_int(TestFramework *tf, const char *test_name, int actual,
                      int expected) {
  char msg[256];

  if (actual == expected) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    snprintf(msg, sizeof(msg), "Expected %d, got %d", expected, actual);
    print_test_result(tf, test_name, false, msg);
  }
}

void assert_equal_float(TestFramework *tf, const char *test_name, double actual,
                        double expected, double epsilon) {
  char msg[256];

  if (fabs(actual - expected) <= epsilon) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    snprintf(msg, sizeof(msg), "Expected %.6f, got %.6f (epsilon: %.6f)",
             expected, actual, epsilon);
    print_test_result(tf, test_name, false, msg);
  }
}

void assert_not_null(TestFramework *tf, const char *test_name,
                     const void *ptr) {
  if (ptr != NULL) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    print_test_result(tf, test_name, false,
                      "Expected non-NULL pointer, got NULL");
  }
}

void assert_null(TestFramework *tf, const char *test_name, const void *ptr) {
  if (ptr == NULL) {
    print_test_result(tf, test_name, true, NULL);
  } else {
    print_test_result(tf, test_name, false,
                      "Expected NULL pointer, got non-NULL");
  }
}

void print_summary(TestFramework *tf) {
  double pass_rate;

  printf("\n");
  print_colored(BOLD, "=== Test Summary ===\n");

  pass_rate = tf->tests_total > 0
                  ? (double)tf->tests_passed / tf->tests_total * 100.0
                  : 0.0;

  printf("Total tests: %d\n", tf->tests_total);
  print_colored(GREEN, "Passed: %d\n", tf->tests_passed);

  if (tf->tests_failed > 0) {
    print_colored(RED, "Failed: %d\n", tf->tests_failed);
  }

  printf("Pass rate: %.1f%%\n", pass_rate);

  if (tf->tests_failed == 0 && tf->tests_total > 0) {
    print_colored(GREEN BOLD, "All tests passed!\n");
  } else if (tf->tests_failed > 0) {
    print_colored(RED BOLD, "Some tests failed.\n");
  }
}

int get_exit_code(TestFramework *tf) { return tf->tests_failed > 0 ? 1 : 0; }
