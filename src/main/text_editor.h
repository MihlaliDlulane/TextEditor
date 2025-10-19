#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "strings/string_buffer.h"
#include "arrays/line_array.h"
#include "stacks/undo_stack.h"
#include "queues/command_queue.h"
#include "hashmaps/text_search.h"

typedef struct {
  LineArray *lines;
  UndoStack *undo_stack;
  CommandQueue *command_queue;
  TextSearchMap *search_map;
  int cursor_line;
  int cursor_position;
} TextEditor;

TextEditor *create_text_editor();
void insert_text(TextEditor *editor, const char *text);
void delete_text(TextEditor *editor, int count);
void new_line(TextEditor *editor);
void undo_last_command(TextEditor *editor);
void execute_queued_commands(TextEditor *editor);
int *find_text(TextEditor *editor, const char *text, int *count);
void replace_text(TextEditor *editor, const char *find, const char *replace);
void print_editor_content(TextEditor *editor);
void free_text_editor(TextEditor *editor);

#endif