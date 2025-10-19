#ifndef UNDO_STACK_H
#define UNDO_STACK_H

typedef enum {
  INSERT_CHAR,
  DELETE_CHAR,
  INSERT_LINE,
  DELETE_LINE
} CommandType;

typedef struct {
  CommandType type;
  int line;
  int position;
  char *data;
} Command;

typedef struct {
  Command *commands;
  int top;
  int capacity;
} UndoStack;

UndoStack *create_undo_stack();
void push_command(UndoStack *stack, CommandType type, int line, int position, const char *data);
Command *pop_command(UndoStack *stack);
int is_empty(UndoStack *stack);
void clear_stack(UndoStack *stack);
void free_undo_stack(UndoStack *stack);

#endif