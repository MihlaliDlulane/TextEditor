#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/queues/command_queue.h"

void test_queue_creation(TestFramework *tf) {
  CommandQueue *queue = create_command_queue();
  ASSERT_NOT_NULL(tf, "Queue creation", queue);
  ASSERT_TRUE(tf, "Queue is empty", queue_is_empty(queue));
  ASSERT_EQ_INT(tf, "Queue size", get_queue_size(queue), 0);
  free_command_queue(queue);
}

void test_enqueue_dequeue(TestFramework *tf) {
  CommandQueue *queue = create_command_queue();
  enqueue_command(queue, "insert:hello");
  ASSERT_FALSE(tf, "Queue not empty after enqueue", queue_is_empty(queue));
  ASSERT_EQ_INT(tf, "Queue size after enqueue", get_queue_size(queue), 1);
  
  char *cmd = dequeue_command(queue);
  ASSERT_EQ_STR(tf, "Dequeued command", cmd, "insert:hello");
  ASSERT_TRUE(tf, "Queue empty after dequeue", queue_is_empty(queue));
  
  free(cmd);
  free_command_queue(queue);
}

void test_fifo_order(TestFramework *tf) {
  CommandQueue *queue = create_command_queue();
  enqueue_command(queue, "first");
  enqueue_command(queue, "second");
  enqueue_command(queue, "third");
  
  char *cmd1 = dequeue_command(queue);
  char *cmd2 = dequeue_command(queue);
  char *cmd3 = dequeue_command(queue);
  
  ASSERT_EQ_STR(tf, "First out", cmd1, "first");
  ASSERT_EQ_STR(tf, "Second out", cmd2, "second");
  ASSERT_EQ_STR(tf, "Third out", cmd3, "third");
  
  free(cmd1);
  free(cmd2);
  free(cmd3);
  free_command_queue(queue);
}

void test_space_complexity_queue(TestFramework *tf) {
  init_memory_tracker();
  
  CommandQueue *queue = create_command_queue();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Enqueue 25 commands
  for (int i = 0; i < 25; i++) {
    enqueue_command(queue, "insert:test");
  }
  size_t memory_25_commands = get_memory_stats().current_usage - base_memory;
  
  // Enqueue 25 more commands (50 total)
  for (int i = 0; i < 25; i++) {
    enqueue_command(queue, "newline");
  }
  size_t memory_50_commands = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(tf, "Queue memory grows with commands", memory_50_commands > memory_25_commands);
  ASSERT_TRUE(tf, "Queue space O(m)", memory_50_commands <= memory_25_commands * 3);
  
  free_command_queue(queue);
  ASSERT_EQ_INT(tf, "Queue memory freed", get_memory_stats().current_usage, 0);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "CommandQueue Tests");
  
  test_queue_creation(&tf);
  test_enqueue_dequeue(&tf);
  test_fifo_order(&tf);
  test_space_complexity_queue(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}