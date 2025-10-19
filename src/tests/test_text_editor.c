#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/text_editor.h"
#include <stdio.h>

void test_editor_creation(TestFramework *tf) {
  TextEditor *editor = create_text_editor();
  ASSERT_NOT_NULL(tf, "Editor creation", editor);
  ASSERT_EQ_INT(tf, "Initial line count", get_line_count(editor->lines), 1);
  free_text_editor(editor);
}

void test_insert_text(TestFramework *tf) {
  TextEditor *editor = create_text_editor();
  insert_text(editor, "Hello");
  insert_text(editor, " World");
  
  StringBuffer *line = get_line(editor->lines, 0);
  ASSERT_EQ_STR(tf, "Inserted text", get_content(line), "Hello World");
  ASSERT_EQ_INT(tf, "Cursor position", editor->cursor_position, 11);
  
  free_text_editor(editor);
}

void test_new_line(TestFramework *tf) {
  TextEditor *editor = create_text_editor();
  insert_text(editor, "Line 1");
  new_line(editor);
  insert_text(editor, "Line 2");
  
  ASSERT_EQ_INT(tf, "Line count", get_line_count(editor->lines), 2);
  ASSERT_EQ_STR(tf, "First line", get_content(get_line(editor->lines, 0)), "Line 1");
  ASSERT_EQ_STR(tf, "Second line", get_content(get_line(editor->lines, 1)), "Line 2");
  
  free_text_editor(editor);
}

void test_undo_functionality(TestFramework *tf) {
  TextEditor *editor = create_text_editor();
  insert_text(editor, "Hello");
  undo_last_command(editor);
  
  StringBuffer *line = get_line(editor->lines, 0);
  ASSERT_EQ_STR(tf, "After undo", get_content(line), "");
  ASSERT_EQ_INT(tf, "Cursor after undo", editor->cursor_position, 0);
  
  free_text_editor(editor);
}

void test_integrated_space_complexity(TestFramework *tf) {
  init_memory_tracker();
  
  TextEditor *editor = create_text_editor();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Add content and measure memory growth
  insert_text(editor, "Line 1");
  new_line(editor);
  insert_text(editor, "Line 2");
  new_line(editor);
  
  size_t memory_2_lines = get_memory_stats().current_usage - base_memory;
  
  // Add more content
  for (int i = 3; i <= 10; i++) {
    insert_text(editor, "Line ");
    char num[10];
    sprintf(num, "%d", i);
    insert_text(editor, num);
    new_line(editor);
  }
  
  size_t memory_10_lines = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(tf, "Editor memory grows with content", memory_10_lines > memory_2_lines);
  ASSERT_TRUE(tf, "Integrated space complexity", memory_10_lines <= memory_2_lines * 8);
  
  // Test undo operations don't cause memory leaks
  for (int i = 0; i < 5; i++) {
    undo_last_command(editor);
  }
  
  size_t memory_after_undo = get_memory_stats().current_usage - base_memory;
  ASSERT_TRUE(tf, "Undo doesn't increase memory", memory_after_undo <= memory_10_lines);
  
  free_text_editor(editor);
  ASSERT_EQ_INT(tf, "All editor memory freed", get_memory_stats().current_usage, 0);
}

void test_memory_efficiency_operations(TestFramework *tf) {
  init_memory_tracker();
  
  TextEditor *editor = create_text_editor();
  
  // Test that repeated operations don't cause excessive memory growth
  for (int i = 0; i < 100; i++) {
    insert_text(editor, "x");
    if (i % 10 == 0) {
      undo_last_command(editor);
    }
  }
  
  MemoryStats stats = get_memory_stats();
  ASSERT_TRUE(tf, "Reasonable memory usage", stats.current_usage < 50000); // Reasonable limit
  
  free_text_editor(editor);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "TextEditor Tests");
  
  test_editor_creation(&tf);
  test_insert_text(&tf);
  test_new_line(&tf);
  test_undo_functionality(&tf);
  test_integrated_space_complexity(&tf);
  test_memory_efficiency_operations(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}