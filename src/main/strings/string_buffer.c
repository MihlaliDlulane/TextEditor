#include "string_buffer.h"
#include <stdlib.h>
#include <string.h>

StringBuffer *create_string_buffer() {
  StringBuffer *sb = (StringBuffer *)malloc(sizeof(StringBuffer));
  sb->capacity = 10;
  sb->size = 0;
  sb->buffer = (char *)malloc(sb->capacity);
  sb->buffer[0] = '\0';
  return sb;
}

void append_string(StringBuffer *sb, const char *text) {
  // TODO: Week 1 - String Memory Management
  // Learn: How to calculate string length, when to resize buffer
  // Key concepts: Dynamic memory allocation, buffer overflow prevention
  // Space complexity: O(n) where n is total string length
  // Hint: Check if current capacity can hold new text, resize if needed
}

void prepend_string(StringBuffer *sb, const char *text) {
  // TODO: Week 1 - Memory Movement Operations
  // Learn: Difference between memcpy and memmove for overlapping memory
  // Key concepts: Safe memory operations, shifting existing content
  // Challenge: How to make room at the beginning without losing data?
}

void insert_string(StringBuffer *sb, int Position, const char *text) {
  // TODO: Week 1 - Positional String Operations
  // Learn: Bounds checking, memory shifting for insertion
  // Key concepts: Validate position, shift right portion, insert new text
  // Think: What happens to characters after the insertion point?
}

void remove_substring(StringBuffer *sb, int startPosition, int endPosition) {
  // TODO: Week 1 - String Deletion Operations
  // Learn: Range validation, memory compaction after removal
  // Key concepts: Calculate removal length, shift remaining content left
  // Think: How to close the gap after removing characters?
}

int get_length(StringBuffer *sb) {
  // TODO: Week 1 - Basic Accessor
  // Learn: Simple field access, difference between size and capacity
  // Return the current number of characters in the buffer
}

int get_capacity(StringBuffer *sb) {
  // TODO: Week 1 - Memory Capacity Tracking
  // Learn: Understanding allocated vs used memory
  // Return the total allocated space for the buffer
}

char *get_content(StringBuffer *sb) { return sb->buffer; }

void clear_buffer(StringBuffer *sb) {
  // TODO: Week 1 - Buffer Reset Operations
  // Learn: Efficient clearing without deallocating memory
  // Key concepts: Reset size counter, ensure null termination
  // Think: Do you need to clear all memory or just reset markers?
}

void free_string_buffer(StringBuffer *sb) {
  free(sb->buffer);
  free(sb);
}
