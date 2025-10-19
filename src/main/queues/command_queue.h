#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

typedef struct QueueNode {
  char *command;
  struct QueueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front;
  QueueNode *rear;
  int size;
} CommandQueue;

CommandQueue *create_command_queue();
void enqueue_command(CommandQueue *queue, const char *command);
char *dequeue_command(CommandQueue *queue);
int queue_is_empty(CommandQueue *queue);
int get_queue_size(CommandQueue *queue);
void clear_queue(CommandQueue *queue);
void free_command_queue(CommandQueue *queue);

#endif