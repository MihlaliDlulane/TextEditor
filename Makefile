CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = src/main
TESTDIR = src/tests
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/strings/string_buffer.c \
          $(SRCDIR)/arrays/line_array.c \
          $(SRCDIR)/stacks/undo_stack.c \
          $(SRCDIR)/queues/command_queue.c \
          $(SRCDIR)/hashmaps/text_search.c \
          $(SRCDIR)/text_editor.c

# Test files
TEST_FRAMEWORK = $(TESTDIR)/test_framework/test_framework.c $(TESTDIR)/test_framework/memory_tracker.c
TESTS = test_string_buffer test_line_array test_undo_stack test_command_queue test_text_search test_text_editor test_space_analysis

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJECTS = $(OBJDIR)/test_framework.o $(OBJDIR)/memory_tracker.o

.PHONY: all clean test main dirs

all: dirs main test

dirs:
	@if not exist "$(OBJDIR)" mkdir $(OBJDIR)
	@if not exist "$(OBJDIR)\strings" mkdir $(OBJDIR)\strings
	@if not exist "$(OBJDIR)\arrays" mkdir $(OBJDIR)\arrays
	@if not exist "$(OBJDIR)\stacks" mkdir $(OBJDIR)\stacks
	@if not exist "$(OBJDIR)\queues" mkdir $(OBJDIR)\queues
	@if not exist "$(OBJDIR)\hashmaps" mkdir $(OBJDIR)\hashmaps
	@if not exist "$(BINDIR)" mkdir $(BINDIR)

main: dirs $(BINDIR)/text_editor.exe

$(BINDIR)/text_editor.exe: $(OBJECTS) $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/test_framework.o: $(TESTDIR)/test_framework/test_framework.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/memory_tracker.o: $(TESTDIR)/test_framework/memory_tracker.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: dirs $(TEST_OBJECTS) $(addprefix $(BINDIR)/, $(addsuffix .exe, $(TESTS)))

$(BINDIR)/test_%.exe: $(TESTDIR)/test_%.c $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

run_tests: test
	@echo Running all tests...
	@for %%t in ($(TESTS)) do (echo Running %%t... && $(BINDIR)\%%t.exe)

clean:
	@if exist "$(OBJDIR)" rmdir /s /q $(OBJDIR)
	@if exist "$(BINDIR)" rmdir /s /q $(BINDIR)

# Individual test targets
test_string_buffer: $(BINDIR)/test_string_buffer.exe
test_line_array: $(BINDIR)/test_line_array.exe
test_undo_stack: $(BINDIR)/test_undo_stack.exe
test_command_queue: $(BINDIR)/test_command_queue.exe
test_text_search: $(BINDIR)/test_text_search.exe
test_text_editor: $(BINDIR)/test_text_editor.exe
test_space_analysis: $(BINDIR)/test_space_analysis.exe