#include "memory_tracker.h"
#include <string.h>

#undef malloc
#undef realloc
#undef free

#include <stdlib.h>

static MemoryStats stats = {0, 0, 0, 0};

void init_memory_tracker() {
  memset(&stats, 0, sizeof(MemoryStats));
}

void *tracked_malloc(size_t size) {
  void *ptr = malloc(size + sizeof(size_t));
  if (ptr) {
    *(size_t*)ptr = size;
    stats.total_allocated += size;
    stats.current_usage += size;
    stats.allocation_count++;
    if (stats.current_usage > stats.peak_usage) {
      stats.peak_usage = stats.current_usage;
    }
    return (char*)ptr + sizeof(size_t);
  }
  return NULL;
}

void *tracked_realloc(void *ptr, size_t size) {
  if (!ptr) return tracked_malloc(size);
  
  size_t old_size = *((size_t*)((char*)ptr - sizeof(size_t)));
  void *new_ptr = realloc((char*)ptr - sizeof(size_t), size + sizeof(size_t));
  
  if (new_ptr) {
    *(size_t*)new_ptr = size;
    stats.current_usage = stats.current_usage - old_size + size;
    stats.total_allocated += size;
    if (stats.current_usage > stats.peak_usage) {
      stats.peak_usage = stats.current_usage;
    }
    return (char*)new_ptr + sizeof(size_t);
  }
  return NULL;
}

void tracked_free(void *ptr) {
  if (ptr) {
    size_t size = *((size_t*)((char*)ptr - sizeof(size_t)));
    stats.current_usage -= size;
    free((char*)ptr - sizeof(size_t));
  }
}

MemoryStats get_memory_stats() {
  return stats;
}

void reset_memory_stats() {
  memset(&stats, 0, sizeof(MemoryStats));
}