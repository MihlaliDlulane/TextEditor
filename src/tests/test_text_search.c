#include "test_framework/test_framework.h"
#include "test_framework/memory_tracker.h"
#include "../main/hashmaps/text_search.h"

void test_search_map_creation(TestFramework *tf) {
  TextSearchMap *map = create_search_map();
  ASSERT_NOT_NULL(tf, "SearchMap creation", map);
  free_search_map(map);
}

void test_index_and_search(TestFramework *tf) {
  TextSearchMap *map = create_search_map();
  index_text(map, "hello world hello");
  
  int count;
  int *positions = search_text(map, "hello", &count);
  ASSERT_EQ_INT(tf, "Search result count", count, 2);
  ASSERT_EQ_INT(tf, "First position", positions[0], 0);
  ASSERT_EQ_INT(tf, "Second position", positions[1], 12);
  
  free(positions);
  free_search_map(map);
}

void test_substring_search(TestFramework *tf) {
  TextSearchMap *map = create_search_map();
  index_text(map, "programming");
  
  int count;
  int *positions = search_text(map, "gram", &count);
  ASSERT_EQ_INT(tf, "Substring found", count, 1);
  ASSERT_EQ_INT(tf, "Substring position", positions[0], 3);
  
  free(positions);
  free_search_map(map);
}

void test_space_complexity_hashmap(TestFramework *tf) {
  init_memory_tracker();
  
  TextSearchMap *map = create_search_map();
  size_t base_memory = get_memory_stats().current_usage;
  
  // Index small text
  index_text(map, "hello world test");
  size_t memory_small_text = get_memory_stats().current_usage - base_memory;
  
  clear_search_map(map);
  
  // Index larger text (roughly 4x size)
  index_text(map, "hello world test programming language implementation data structures algorithms");
  size_t memory_large_text = get_memory_stats().current_usage - base_memory;
  
  ASSERT_TRUE(tf, "HashMap memory grows with text size", memory_large_text > memory_small_text);
  // Hash map can have O(n²) worst case due to collision chains
  ASSERT_TRUE(tf, "HashMap space complexity", memory_large_text <= memory_small_text * 20);
  
  free_search_map(map);
  ASSERT_EQ_INT(tf, "HashMap memory freed", get_memory_stats().current_usage, 0);
}

void test_collision_handling(TestFramework *tf) {
  init_memory_tracker();
  
  TextSearchMap *map = create_search_map();
  
  // Test with strings that might cause collisions
  index_text(map, "aaa bbb ccc ddd eee fff ggg hhh iii jjj");
  
  int count;
  int *positions = search_text(map, "aaa", &count);
  ASSERT_EQ_INT(tf, "Find in collision scenario", count, 1);
  if (positions) free(positions);
  
  free_search_map(map);
}

int main() {
  TestFramework tf;
  init_test_framework(&tf);
  begin_test_suite(&tf, "TextSearch Tests");
  
  test_search_map_creation(&tf);
  test_index_and_search(&tf);
  test_substring_search(&tf);
  test_space_complexity_hashmap(&tf);
  test_collision_handling(&tf);
  
  print_summary(&tf);
  return get_exit_code(&tf);
}