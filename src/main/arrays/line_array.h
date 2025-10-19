#ifndef LINE_ARRAY_H
#define LINE_ARRAY_H

#include "../strings/string_buffer.h"

typedef struct {
  StringBuffer **lines;
  int count;
  int capacity;
} LineArray;

LineArray *create_line_array();
void add_line(LineArray *la, const char *text);
void insert_line(LineArray *la, int index, const char *text);
void remove_line(LineArray *la, int index);
StringBuffer *get_line(LineArray *la, int index);
int get_line_count(LineArray *la);
void clear_lines(LineArray *la);
void free_line_array(LineArray *la);

#endif