#include "undo_stack.h"
#include <stdlib.h>
#include <string.h>

UndoStack *create_undo_stack() {
  // TODO: Week 3 - Stack Data Structure Initialization
  // Learn: Stack uses array with top pointer, LIFO principle
  // Key concepts: Why top = -1? How does stack grow?
  // Space complexity: O(k) where k is number of commands stored
}

void push_command(UndoStack *stack, CommandType type, int line, int position, const char *data) {
  // TODO: Week 3 - Stack Push Operation
  // Learn: LIFO insertion, dynamic resizing, deep copying strings
  // Key concepts: Increment top first or after? Handle NULL data safely
  // Think: Why copy the string data instead of storing the pointer?
}

Command *pop_command(UndoStack *stack) {
  // TODO: Week 3 - Stack Pop Operation
  // Learn: LIFO removal, empty stack handling, pointer arithmetic
  // Key concepts: Check empty condition, return pointer to top element
  // Think: Why return pointer instead of copying the command?
}

int is_empty(UndoStack *stack) {
  // TODO: Week 3 - Stack State Checking
  // Learn: How to determine if stack is empty
  // Key concepts: What does top = -1 mean?
}

void clear_stack(UndoStack *stack) {
  // TODO: Week 3 - Stack Memory Cleanup
  // Learn: Proper cleanup of dynamically allocated command data
  // Key concepts: Free string data before removing command
  // Think: Why use pop_command instead of just resetting top?
}

void free_undo_stack(UndoStack *stack) {
  // TODO: Week 3 - Complete Stack Deallocation
  // Learn: Order of cleanup operations
  // Key concepts: Clean contents, then array, then structure
}