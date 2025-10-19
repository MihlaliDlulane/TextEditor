#include "../main/strings/string_buffer.h"
#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include <stdlib.h>
#include <string.h>

int main(void) {
  TestFramework tf;
  StringBuffer *sb;

  init_test_framework(&tf);

  /* Test Suite 1: Basic Creation and Initialization */
  begin_test_suite(&tf, "Creation and Initialization");

  sb = create_string_buffer();
  ASSERT_NOT_NULL(&tf, "create_string_buffer returns non-null", sb);
  ASSERT_EQ_STR(&tf, "initial buffer is empty", get_content(sb), "");

  /* Test length if you have a get_length function */
  /* ASSERT_EQ_INT(&tf, "initial length is 0", get_length(sb), 0); */

  free_string_buffer(sb);

  /* Test Suite 2: Basic Append Operations */
  begin_test_suite(&tf, "Basic Append Operations");

  sb = create_string_buffer();

  /* Test 1: Append single word */
  append_string(sb, "Hello");
  ASSERT_EQ_STR(&tf, "append single word", get_content(sb), "Hello");

  /* Test 2: Append to existing content */
  append_string(sb, " World");
  ASSERT_EQ_STR(&tf, "append to existing content", get_content(sb),
                "Hello World");

  /* Test 3: Append empty string */
  append_string(sb, "");
  ASSERT_EQ_STR(&tf, "append empty string", get_content(sb), "Hello World");

  /* Test 4: Multiple consecutive appends */
  append_string(sb, "!");
  append_string(sb, " How");
  append_string(sb, " are");
  append_string(sb, " you?");
  ASSERT_EQ_STR(&tf, "multiple consecutive appends", get_content(sb),
                "Hello World! How are you?");

  free_string_buffer(sb);

  /* Test Suite 3: Edge Cases and Error Handling */
  begin_test_suite(&tf, "Edge Cases and Error Handling");

  sb = create_string_buffer();

  /* Test with NULL string (should handle gracefully) */
  append_string(sb, NULL);
  ASSERT_EQ_STR(&tf, "append NULL string", get_content(sb), "");

  /* Test with very long string */
  {
    char long_string[1000];
    int i;
    for (i = 0; i < 999; i++) {
      long_string[i] = 'A';
    }
    long_string[999] = '\0';

    append_string(sb, long_string);
    ASSERT_EQ_STR(&tf, "append very long string", get_content(sb), long_string);
  }

  free_string_buffer(sb);

  /* Test Suite 4: Clear Buffer Operations */
  begin_test_suite(&tf, "Clear Buffer Operations");

  sb = create_string_buffer();

  /* Add content first */
  append_string(sb, "This will be cleared");
  ASSERT_EQ_STR(&tf, "content before clear", get_content(sb),
                "This will be cleared");

  /* Clear and verify */
  clear_buffer(sb);
  ASSERT_EQ_STR(&tf, "content after clear", get_content(sb), "");

  /* Test that we can append after clearing */
  append_string(sb, "New content");
  ASSERT_EQ_STR(&tf, "append after clear", get_content(sb), "New content");

  /* Test clearing empty buffer */
  clear_buffer(sb);
  clear_buffer(sb); /* Clear again - should not crash */
  ASSERT_EQ_STR(&tf, "clear empty buffer", get_content(sb), "");

  free_string_buffer(sb);

  /* Test Suite 5: Special Characters and Formatting */
  begin_test_suite(&tf, "Special Characters");

  sb = create_string_buffer();

  /* Test with newlines */
  append_string(sb, "Line 1\nLine 2");
  ASSERT_EQ_STR(&tf, "append with newlines", get_content(sb), "Line 1\nLine 2");

  /* Test with tabs */
  clear_buffer(sb);
  append_string(sb, "Column1\tColumn2");
  ASSERT_EQ_STR(&tf, "append with tabs", get_content(sb), "Column1\tColumn2");

  /* Test with quotes */
  clear_buffer(sb);
  append_string(sb, "He said \"Hello\"");
  ASSERT_EQ_STR(&tf, "append with quotes", get_content(sb),
                "He said \"Hello\"");

  /* Test with numbers and special chars */
  clear_buffer(sb);
  append_string(sb, "Price: $19.99 (50% off!)");
  ASSERT_EQ_STR(&tf, "append numbers and symbols", get_content(sb),
                "Price: $19.99 (50% off!)");

  free_string_buffer(sb);

  /* Test Suite 6: Memory Management */
  begin_test_suite(&tf, "Memory Management");

  /* Test multiple create/free cycles */
  {
    int i;
    for (i = 0; i < 10; i++) {
      sb = create_string_buffer();
      append_string(sb, "Test");
      ASSERT_EQ_STR(&tf, "create/free cycle", get_content(sb), "Test");
      free_string_buffer(sb);
    }
  }

  /* Test with NULL pointer to free (should handle gracefully) */
  free_string_buffer(NULL); /* Should not crash */
  ASSERT_TRUE(&tf, "free NULL pointer",
              true); /* If we get here, it didn't crash */

  /* Test Suite 7: Stress Testing */
  begin_test_suite(&tf, "Stress Testing");

  sb = create_string_buffer();

  /* Test many small appends */
  {
    int i;
    char expected[1000] = "";
    for (i = 0; i < 100; i++) {
      append_string(sb, "x");
      strcat(expected, "x");
    }
    ASSERT_EQ_STR(&tf, "many small appends", get_content(sb), expected);
  }

  /* Test alternating append and clear */
  clear_buffer(sb);
  append_string(sb, "Test1");
  clear_buffer(sb);
  append_string(sb, "Test2");
  clear_buffer(sb);
  append_string(sb, "Final");
  ASSERT_EQ_STR(&tf, "alternating append/clear", get_content(sb), "Final");

  free_string_buffer(sb);

  /* Test Suite 8: Additional Operations (if supported) */
  begin_test_suite(&tf, "Additional Operations");

  sb = create_string_buffer();

  append_string(sb, "Hello");
  ASSERT_EQ_INT(&tf, "length after append", get_length(sb), 5);
  clear_buffer(sb);
  ASSERT_EQ_INT(&tf, "length after clear", get_length(sb), 0);

  int initial_capacity = get_capacity(sb);
  ASSERT_TRUE(&tf, "initial capacity > 0", initial_capacity > 0);

  append_string(sb, "World");
  prepend_string(sb, "Hello ");
  ASSERT_EQ_STR(&tf, "prepend string", get_content(sb), "Hello World");

  clear_buffer(sb);
  append_string(sb, "Hello World");
  insert_string(sb, 6, "Beautiful ");
  ASSERT_EQ_STR(&tf, "insert string", get_content(sb), "Hello Beautiful World");

  clear_buffer(sb);
  append_string(sb, "Hello World");
  remove_substring(sb, 5, 6); // Remove " World"
  ASSERT_EQ_STR(&tf, "remove substring", get_content(sb), "Hello");

  free_string_buffer(sb);

  /* Test Suite 9: Space Complexity Analysis */
  begin_test_suite(&tf, "Space Complexity O(n)");
  
  init_memory_tracker();
  
  sb = create_string_buffer();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Test O(n) space - memory should grow linearly with string length
  append_string(sb, "Hello");
  size_t memory_5_chars = get_memory_stats().current_usage - base_memory;
  
  append_string(sb, " World Test String");
  size_t memory_23_chars = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(&tf, "Memory grows with content", memory_23_chars > memory_5_chars);
  ASSERT_TRUE(&tf, "Space complexity O(n)", memory_23_chars <= memory_5_chars * 6);
  
  free_string_buffer(sb);
  
  MemoryStats final_stats = get_memory_stats();
  ASSERT_EQ_INT(&tf, "No memory leaks", final_stats.current_usage, 0);

  /* Final Summary */
  print_summary(&tf);
  return get_exit_code(&tf);
}
