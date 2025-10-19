#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/stacks/undo_stack.h"

void test_stack_creation(TestFramework *tf) {
  UndoStack *stack = create_undo_stack();
  ASSERT_NOT_NULL(tf, "Stack creation", stack);
  ASSERT_TRUE(tf, "Stack is empty", is_empty(stack));
  free_undo_stack(stack);
}

void test_push_pop_commands(TestFramework *tf) {
  UndoStack *stack = create_undo_stack();
  push_command(stack, INSERT_CHAR, 0, 5, "test");
  ASSERT_FALSE(tf, "Stack not empty after push", is_empty(stack));
  
  Command *cmd = pop_command(stack);
  ASSERT_NOT_NULL(tf, "Popped command", cmd);
  ASSERT_EQ_INT(tf, "Command type", cmd->type, INSERT_CHAR);
  ASSERT_EQ_INT(tf, "Command line", cmd->line, 0);
  ASSERT_EQ_INT(tf, "Command position", cmd->position, 5);
  ASSERT_EQ_STR(tf, "Command data", cmd->data, "test");
  
  ASSERT_TRUE(tf, "Stack empty after pop", is_empty(stack));
  free_undo_stack(stack);
}

void test_multiple_commands(TestFramework *tf) {
  UndoStack *stack = create_undo_stack();
  push_command(stack, INSERT_CHAR, 0, 0, "first");
  push_command(stack, DELETE_CHAR, 1, 5, "second");
  
  Command *cmd2 = pop_command(stack);
  ASSERT_EQ_STR(tf, "Second command data", cmd2->data, "second");
  
  Command *cmd1 = pop_command(stack);
  ASSERT_EQ_STR(tf, "First command data", cmd1->data, "first");
  
  free_undo_stack(stack);
}

void test_space_complexity_stack(TestFramework *tf) {
  init_memory_tracker();
  
  UndoStack *stack = create_undo_stack();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Push 50 commands
  for (int i = 0; i < 50; i++) {
    push_command(stack, INSERT_CHAR, i, 0, "test");
  }
  size_t memory_50_commands = get_memory_stats().current_usage - base_memory;
  
  // Push 50 more commands (100 total)
  for (int i = 0; i < 50; i++) {
    push_command(stack, DELETE_CHAR, i, 0, "data");
  }
  size_t memory_100_commands = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(tf, "Stack memory grows with commands", memory_100_commands > memory_50_commands);
  ASSERT_TRUE(tf, "Stack space O(k)", memory_100_commands <= memory_50_commands * 3);
  
  free_undo_stack(stack);
  ASSERT_EQ_INT(tf, "Stack memory freed", get_memory_stats().current_usage, 0);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "UndoStack Tests");
  
  test_stack_creation(&tf);
  test_push_pop_commands(&tf);
  test_multiple_commands(&tf);
  test_space_complexity_stack(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}