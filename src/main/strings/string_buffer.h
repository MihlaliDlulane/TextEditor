#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

typedef struct {
  char *buffer;
  int size;
  int capacity;
} StringBuffer;

StringBuffer *create_string_buffer();

void append_string(StringBuffer *sb, const char *text);

void prepend_string(StringBuffer *sb, const char *text);

void insert_string(StringBuffer *sb, int Position, const char *text);

void remove_substring(StringBuffer *sb, int startPosition, int endPosition);

char *get_content(StringBuffer *sb);

int get_length(StringBuffer *sb);

int get_capacity(StringBuffer *sb);

void clear_buffer(StringBuffer *sb);

void free_string_buffer(StringBuffer *sb);

#endif
