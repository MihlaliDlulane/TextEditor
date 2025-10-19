#include "text_editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  TextEditor *editor = create_text_editor();
  
  printf("Text Editor Simulator\n");
  printf("Commands: insert <text>, newline, undo, find <text>, replace <find> <replace>, print, quit\n\n");
  
  char command[256];
  while (1) {
    printf("> ");
    if (!fgets(command, sizeof(command), stdin)) break;
    
    if (strncmp(command, "insert ", 7) == 0) {
      command[strlen(command) - 1] = '\0';
      insert_text(editor, command + 7);
    } else if (strncmp(command, "newline", 7) == 0) {
      new_line(editor);
    } else if (strncmp(command, "undo", 4) == 0) {
      undo_last_command(editor);
    } else if (strncmp(command, "find ", 5) == 0) {
      command[strlen(command) - 1] = '\0';
      int count;
      int *positions = find_text(editor, command + 5, &count);
      printf("Found %d occurrences\n", count);
      if (positions) free(positions);
    } else if (strncmp(command, "replace ", 8) == 0) {
      command[strlen(command) - 1] = '\0';
      char *find = strtok(command + 8, " ");
      char *replace = strtok(NULL, " ");
      if (find && replace) {
        replace_text(editor, find, replace);
      }
    } else if (strncmp(command, "print", 5) == 0) {
      print_editor_content(editor);
    } else if (strncmp(command, "quit", 4) == 0) {
      break;
    }
  }
  
  free_text_editor(editor);
  return 0;
}