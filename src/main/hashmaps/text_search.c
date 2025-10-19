#include "text_search.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *key) {
  // TODO: Week 4 - Hash Function Implementation
  // Learn: Converting string to array index, collision minimization
  // Key concepts: djb2 algorithm, bit shifting, modulo operation
  // Think: Why use 5381? What does (hash << 5) + hash accomplish?
}

TextSearchMap *create_search_map() {
  // TODO: Week 4 - Hash Map Initialization
  // Learn: Array of linked list heads, collision handling preparation
  // Key concepts: Initialize all buckets to NULL, why HASH_SIZE buckets?
  // Space complexity: O(1) initially, grows to O(n) with entries
}

void add_position(HashNode *node, int position) {
  // TODO: Week 4 - Dynamic Array within Hash Node
  // Learn: Each hash node can store multiple positions
  // Key concepts: Why store multiple positions? Dynamic resizing
}

void index_text(TextSearchMap *map, const char *text) {
  // TODO: Week 4 - Text Indexing with Substrings
  // Learn: Generate all substrings, hash each one, handle collisions
  // Key concepts: Nested loops for substrings, collision chaining
  // Think: Why limit substring length to 20? How does chaining work?
  // Space complexity: Can be O(n²) in worst case due to many substrings
}

int *search_text(TextSearchMap *map, const char *key, int *result_count) {
  // TODO: Week 4 - Hash Map Search Operation
  // Learn: Hash key to bucket, traverse collision chain, return results
  // Key concepts: Linear probing through chain, deep copy results
  // Think: Why copy positions instead of returning direct pointer?
}

void clear_search_map(TextSearchMap *map) {
  // TODO: Week 4 - Hash Map Cleanup
  // Learn: Traverse each bucket's collision chain, free all nodes
  // Key concepts: Linked list traversal, multiple memory frees per node
  // Think: Why save next pointer before freeing current node?
}

void free_search_map(TextSearchMap *map) {
  // TODO: Week 4 - Complete Hash Map Deallocation
  // Learn: Clear all buckets first, then free structure
  // Key concepts: Order of cleanup operations
}