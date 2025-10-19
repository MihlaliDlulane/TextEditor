#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/arrays/line_array.h"

void test_line_array_creation(TestFramework *tf) {
  LineArray *la = create_line_array();
  ASSERT_NOT_NULL(tf, "LineArray creation", la);
  ASSERT_EQ_INT(tf, "Initial line count", get_line_count(la), 0);
  free_line_array(la);
}

void test_add_line(TestFramework *tf) {
  LineArray *la = create_line_array();
  add_line(la, "Hello World");
  ASSERT_EQ_INT(tf, "Line count after add", get_line_count(la), 1);
  StringBuffer *line = get_line(la, 0);
  ASSERT_EQ_STR(tf, "Line content", get_content(line), "Hello World");
  free_line_array(la);
}

void test_insert_remove_line(TestFramework *tf) {
  LineArray *la = create_line_array();
  add_line(la, "Line 1");
  add_line(la, "Line 3");
  insert_line(la, 1, "Line 2");
  ASSERT_EQ_INT(tf, "Line count after insert", get_line_count(la), 3);
  ASSERT_EQ_STR(tf, "Inserted line content", get_content(get_line(la, 1)), "Line 2");
  
  remove_line(la, 1);
  ASSERT_EQ_INT(tf, "Line count after remove", get_line_count(la), 2);
  ASSERT_EQ_STR(tf, "Line after removal", get_content(get_line(la, 1)), "Line 3");
  free_line_array(la);
}

void test_space_complexity_linear_lines(TestFramework *tf) {
  init_memory_tracker();
  
  LineArray *la = create_line_array();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Add 10 lines
  for (int i = 0; i < 10; i++) {
    add_line(la, "Test line");
  }
  size_t memory_10_lines = get_memory_stats().current_usage - base_memory;
  
  // Add 10 more lines (20 total)
  for (int i = 0; i < 10; i++) {
    add_line(la, "Another test line");
  }
  size_t memory_20_lines = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(tf, "Memory grows with line count", memory_20_lines > memory_10_lines);
  ASSERT_TRUE(tf, "Space complexity O(n)", memory_20_lines <= memory_10_lines * 3);
  
  free_line_array(la);
  ASSERT_EQ_INT(tf, "No memory leaks", get_memory_stats().current_usage, 0);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "LineArray Tests");
  
  test_line_array_creation(&tf);
  test_add_line(&tf);
  test_insert_remove_line(&tf);
  test_space_complexity_linear_lines(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}