#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/text_editor.h"
#include <stdio.h>

void test_comparative_space_complexity(TestFramework *tf) {
  printf("\n=== SPACE COMPLEXITY ANALYSIS ===\n");
  
  init_memory_tracker();
  
  // Test StringBuffer O(n) space
  printf("StringBuffer (O(n) space):\n");
  StringBuffer *sb = create_string_buffer();
  size_t sb_base = get_memory_stats().current_usage;
  
  append_string(sb, "Hello");
  size_t sb_5 = get_memory_stats().current_usage - sb_base;
  printf("  5 chars: %llu bytes\n", (unsigned long long)sb_5);
  
  append_string(sb, " World Test String");
  size_t sb_22 = get_memory_stats().current_usage - sb_base;
  printf("  22 chars: %llu bytes (ratio: %.2f)\n", (unsigned long long)sb_22, (double)sb_22/sb_5);
  
  free_string_buffer(sb);
  
  // Test LineArray O(n) space
  printf("\nLineArray (O(n) space):\n");
  LineArray *la = create_line_array();
  size_t la_base = get_memory_stats().current_usage;
  
  for (int i = 0; i < 5; i++) add_line(la, "Test line");
  size_t la_5 = get_memory_stats().current_usage - la_base;
  printf("  5 lines: %llu bytes\n", (unsigned long long)la_5);
  
  for (int i = 0; i < 15; i++) add_line(la, "Test line");
  size_t la_20 = get_memory_stats().current_usage - la_base;
  printf("  20 lines: %llu bytes (ratio: %.2f)\n", (unsigned long long)la_20, (double)la_20/la_5);
  
  free_line_array(la);
  
  // Test UndoStack O(k) space
  printf("\nUndoStack (O(k) space):\n");
  UndoStack *stack = create_undo_stack();
  size_t stack_base = get_memory_stats().current_usage;
  
  for (int i = 0; i < 10; i++) {
    push_command(stack, INSERT_CHAR, i, 0, "test");
  }
  size_t stack_10 = get_memory_stats().current_usage - stack_base;
  printf("  10 commands: %llu bytes\n", (unsigned long long)stack_10);
  
  for (int i = 0; i < 40; i++) {
    push_command(stack, DELETE_CHAR, i, 0, "data");
  }
  size_t stack_50 = get_memory_stats().current_usage - stack_base;
  printf("  50 commands: %llu bytes (ratio: %.2f)\n", (unsigned long long)stack_50, (double)stack_50/stack_10);
  
  free_undo_stack(stack);
  
  // Test TextSearchMap space complexity
  printf("\nTextSearchMap (O(n) avg, O(n²) worst):\n");
  TextSearchMap *map = create_search_map();
  size_t map_base = get_memory_stats().current_usage;
  
  index_text(map, "hello world");
  size_t map_small = get_memory_stats().current_usage - map_base;
  printf("  Small text: %llu bytes\n", (unsigned long long)map_small);
  
  clear_search_map(map);
  index_text(map, "hello world programming language implementation data structures");
  size_t map_large = get_memory_stats().current_usage - map_base;
  printf("  Large text: %llu bytes (ratio: %.2f)\n", (unsigned long long)map_large, (double)map_large/map_small);
  
  free_search_map(map);
  
  printf("\n=== SPACE COMPLEXITY VERIFICATION ===\n");
  ASSERT_TRUE(tf, "StringBuffer linear growth", (double)sb_22/sb_5 < 6.0);
  ASSERT_TRUE(tf, "LineArray linear growth", (double)la_20/la_5 < 6.0);
  ASSERT_TRUE(tf, "UndoStack linear growth", (double)stack_50/stack_10 < 8.0);
  ASSERT_TRUE(tf, "HashMap reasonable growth", (double)map_large/map_small < 15.0);
  
  ASSERT_EQ_INT(tf, "No memory leaks", get_memory_stats().current_usage, 0);
}

void test_worst_case_scenarios(TestFramework *tf) {
  printf("\n=== WORST CASE SPACE ANALYSIS ===\n");
  
  init_memory_tracker();
  
  // Test hash map collision scenario
  TextSearchMap *map = create_search_map();
  size_t map_base = get_memory_stats().current_usage;
  
  // Create text with potential hash collisions
  index_text(map, "aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt uu vv ww xx yy zz");
  size_t collision_memory = get_memory_stats().current_usage - map_base;
  printf("Collision scenario memory: %llu bytes\n", (unsigned long long)collision_memory);
  
  ASSERT_TRUE(tf, "Collision handling reasonable", collision_memory < 10000);
  
  free_search_map(map);
  
  // Test deep undo stack
  UndoStack *deep_stack = create_undo_stack();
  size_t deep_base = get_memory_stats().current_usage;
  
  for (int i = 0; i < 1000; i++) {
    push_command(deep_stack, INSERT_CHAR, i, 0, "x");
  }
  size_t deep_memory = get_memory_stats().current_usage - deep_base;
  printf("Deep stack (1000 commands): %llu bytes\n", (unsigned long long)deep_memory);
  
  ASSERT_TRUE(tf, "Deep stack manageable", deep_memory < 100000);
  
  free_undo_stack(deep_stack);
  
  ASSERT_EQ_INT(tf, "Worst case cleanup", get_memory_stats().current_usage, 0);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "Space Complexity Analysis");
  
  test_comparative_space_complexity(&tf);
  test_worst_case_scenarios(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}