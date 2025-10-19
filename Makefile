CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = src/main
TESTDIR = src/tests
OBJDIR = obj
BINDIR = bin

# Detect OS
ifeq ($(OS),Windows_NT)
    EXE_EXT = .exe
    MKDIR = mkdir
    RM = rmdir /s /q
    PATH_SEP = \\
    RUN_TEST = $(BINDIR)\\$$t.exe
else
    EXE_EXT =
    MKDIR = mkdir -p
    RM = rm -rf
    PATH_SEP = /
    RUN_TEST = ./$(BINDIR)/$$t
endif

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
	@$(MKDIR) $(OBJDIR) $(OBJDIR)/strings $(OBJDIR)/arrays $(OBJDIR)/stacks $(OBJDIR)/queues $(OBJDIR)/hashmaps $(BINDIR)

main: dirs $(BINDIR)/text_editor$(EXE_EXT)

$(BINDIR)/text_editor$(EXE_EXT): $(OBJECTS) $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/test_framework.o: $(TESTDIR)/test_framework/test_framework.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/memory_tracker.o: $(TESTDIR)/test_framework/memory_tracker.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: dirs $(TEST_OBJECTS) $(addprefix $(BINDIR)/, $(addsuffix $(EXE_EXT), $(TESTS)))

$(BINDIR)/test_%$(EXE_EXT): $(TESTDIR)/test_%.c $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

run_tests: test
	@echo "Running all tests..."
ifeq ($(OS),Windows_NT)
	@for %%t in ($(TESTS)) do (echo Running %%t... && $(BINDIR)\\%%t.exe)
else
	@for t in $(TESTS); do echo "Running $$t..."; $(RUN_TEST); done
endif

clean:
	@$(RM) $(OBJDIR) $(BINDIR) 2>/dev/null || true

# Individual test targets
test_string_buffer: $(BINDIR)/test_string_buffer$(EXE_EXT)
test_line_array: $(BINDIR)/test_line_array$(EXE_EXT)
test_undo_stack: $(BINDIR)/test_undo_stack$(EXE_EXT)
test_command_queue: $(BINDIR)/test_command_queue$(EXE_EXT)
test_text_search: $(BINDIR)/test_text_search$(EXE_EXT)
test_text_editor: $(BINDIR)/test_text_editor$(EXE_EXT)
test_space_analysis: $(BINDIR)/test_space_analysis$(EXE_EXT)