#ifndef TEXT_SEARCH_H
#define TEXT_SEARCH_H

#define HASH_SIZE 101

typedef struct HashNode {
  char *key;
  int *positions;
  int count;
  int capacity;
  struct HashNode *next;
} HashNode;

typedef struct {
  HashNode *buckets[HASH_SIZE];
  int total_entries;
} TextSearchMap;

TextSearchMap *create_search_map();
void index_text(TextSearchMap *map, const char *text);
int *search_text(TextSearchMap *map, const char *key, int *result_count);
void clear_search_map(TextSearchMap *map);
void free_search_map(TextSearchMap *map);

#endif