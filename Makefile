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

.PHONY: all clean test main dirs help run_tests

# Default target
all: dirs main test

# Help command
help:
	@echo "TextEditor Build System"
	@echo "======================"
	@echo ""
	@echo "Main Targets:"
	@echo "  all          - Build everything (main program and tests)"
	@echo "  main         - Build only the text editor executable"
	@echo "  test         - Build all test executables"
	@echo "  run_tests    - Build and run all tests"
	@echo "  clean        - Remove all build artifacts"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Individual Test Targets:"
	@echo "  test_string_buffer   - Build string buffer tests (Week 1)"
	@echo "  test_line_array     - Build line array tests (Week 2)"
	@echo "  test_undo_stack     - Build undo stack tests (Week 3)"
	@echo "  test_command_queue  - Build command queue tests (Week 3)"
	@echo "  test_text_search    - Build text search tests (Week 4)"
	@echo "  test_text_editor    - Build integration tests"
	@echo "  test_space_analysis - Build space complexity analysis"
	@echo ""
	@echo "Usage Examples:"
	@echo "  make                 # Build everything"
	@echo "  make main            # Build just the text editor"
	@echo "  make test_string_buffer  # Build and test Week 1"
	@echo "  make run_tests       # Run all tests"
	@echo "  make clean           # Clean up build files"
	@echo ""
ifeq ($(OS),Windows_NT)
	@echo "Running Programs (Windows):"
	@echo "  bin\\text_editor.exe        # Run the text editor"
	@echo "  bin\\test_string_buffer.exe # Run string buffer tests"
else
	@echo "Running Programs (Linux/Unix):"
	@echo "  ./bin/text_editor           # Run the text editor"
	@echo "  ./bin/test_string_buffer    # Run string buffer tests"
endif
	@echo ""

dirs:
ifeq ($(OS),Windows_NT)
	@if not exist "$(OBJDIR)" $(MKDIR) "$(OBJDIR)"
	@if not exist "$(OBJDIR)\strings" $(MKDIR) "$(OBJDIR)\strings"
	@if not exist "$(OBJDIR)\arrays" $(MKDIR) "$(OBJDIR)\arrays"
	@if not exist "$(OBJDIR)\stacks" $(MKDIR) "$(OBJDIR)\stacks"
	@if not exist "$(OBJDIR)\queues" $(MKDIR) "$(OBJDIR)\queues"
	@if not exist "$(OBJDIR)\hashmaps" $(MKDIR) "$(OBJDIR)\hashmaps"
	@if not exist "$(BINDIR)" $(MKDIR) "$(BINDIR)"
else
	@$(MKDIR) $(OBJDIR) $(OBJDIR)/strings $(OBJDIR)/arrays $(OBJDIR)/stacks $(OBJDIR)/queues $(OBJDIR)/hashmaps $(BINDIR)
endif

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

$(BINDIR)/test_%$(EXE_EXT): dirs $(TESTDIR)/test_%.c $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out dirs,$^)

run_tests: test
	@echo "Running all tests..."
ifeq ($(OS),Windows_NT)
	@for %%t in ($(TESTS)) do (echo Running %%t... && $(BINDIR)\\%%t.exe)
else
	@for t in $(TESTS); do echo "Running $$t..."; $(RUN_TEST); done
endif

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(OBJDIR)" $(RM) "$(OBJDIR)"
	@if exist "$(BINDIR)" $(RM) "$(BINDIR)"
else
	@$(RM) $(OBJDIR) $(BINDIR) 2>/dev/null || true
endif

# Individual test targets
test_string_buffer: dirs $(BINDIR)/test_string_buffer$(EXE_EXT)
test_line_array: dirs $(BINDIR)/test_line_array$(EXE_EXT)
test_undo_stack: dirs $(BINDIR)/test_undo_stack$(EXE_EXT)
test_command_queue: dirs $(BINDIR)/test_command_queue$(EXE_EXT)
test_text_search: dirs $(BINDIR)/test_text_search$(EXE_EXT)
test_text_editor: dirs $(BINDIR)/test_text_editor$(EXE_EXT)
test_space_analysis: dirs $(BINDIR)/test_space_analysis$(EXE_EXT)