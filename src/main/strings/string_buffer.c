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
  // Implement append with resizing
}

void prepend_string(StringBuffer *sb, const char *text) {
  // Implment prepend with resizing
}

void insert_string(StringBuffer *sb, int Position, const char *text) {
  // Implmenet insert string at position with resizing
}

void remove_substring(StringBuffer *sb, int startPosition, int endPosition) {
  // Implement remove substring at start positin and end at end position with
  // resizing
}

int get_length(StringBuffer *sb) {
  // Implement get length of string
}

int get_capacity(StringBuffer *sb) {
  // Implement get capacity
}

char *get_content(StringBuffer *sb) { return sb->buffer; }

void clear_buffer(StringBuffer *sb) {
  // Week 1: Implement clear
}

void free_string_buffer(StringBuffer *sb) {
  free(sb->buffer);
  free(sb);
}
