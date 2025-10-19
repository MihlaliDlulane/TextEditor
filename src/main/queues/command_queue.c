#include "command_queue.h"
#include <stdlib.h>
#include <string.h>

CommandQueue *create_command_queue() {
  // TODO: Week 3 - Queue Data Structure Initialization
  // Learn: Queue uses linked list, FIFO principle, front/rear pointers
  // Key concepts: Why NULL for both front and rear initially?
  // Space complexity: O(m) where m is number of queued commands
}

void enqueue_command(CommandQueue *queue, const char *command) {
  // TODO: Week 3 - Queue Enqueue Operation
  // Learn: FIFO insertion at rear, linked list node creation
  // Key concepts: Handle empty queue case, update rear pointer
  // Think: Why check if rear exists? What if queue is empty?
}

char *dequeue_command(CommandQueue *queue) {
  // TODO: Week 3 - Queue Dequeue Operation
  // Learn: FIFO removal from front, linked list node removal
  // Key concepts: Handle empty queue, update front pointer, clean up node
  // Think: Why set rear to NULL when front becomes NULL?
}

int queue_is_empty(CommandQueue *queue) {
  // TODO: Week 3 - Queue State Checking
  // Learn: How to determine if queue is empty
  // Key concepts: What does front == NULL indicate?
}

int get_queue_size(CommandQueue *queue) {
  // TODO: Week 3 - Queue Size Tracking
  // Learn: Maintaining count vs calculating on demand
  // Return the current number of commands in queue
}

void clear_queue(CommandQueue *queue) {
  // TODO: Week 3 - Queue Bulk Cleanup
  // Learn: Proper cleanup of all queued commands
  // Key concepts: Dequeue and free each command string
  // Think: Why use dequeue instead of direct node traversal?
}

void free_command_queue(CommandQueue *queue) {
  // TODO: Week 3 - Complete Queue Deallocation
  // Learn: Clean all nodes first, then structure
  // Key concepts: Order of cleanup operations
}