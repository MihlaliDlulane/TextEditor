#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <stddef.h>

typedef struct {
  size_t total_allocated;
  size_t peak_usage;
  size_t current_usage;
  int allocation_count;
} MemoryStats;

void init_memory_tracker();
void *tracked_malloc(size_t size);
void *tracked_realloc(void *ptr, size_t size);
void tracked_free(void *ptr);
MemoryStats get_memory_stats();
void reset_memory_stats();

#define malloc(size) tracked_malloc(size)
#define realloc(ptr, size) tracked_realloc(ptr, size)
#define free(ptr) tracked_free(ptr)

#endif