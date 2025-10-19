# TextEditor

A hands-on learning project where you'll implement fundamental data structures in C from scratch. This project teaches computer science concepts through practical implementation and space complexity analysis.

## Project Overview

You'll build a text editor simulator by implementing core data structures and analyzing their space complexity characteristics:

- **Week 1**: String manipulation and memory management (String Buffer)
- **Week 2**: Dynamic arrays and space trade-offs (Line Array)  
- **Week 3**: Stacks and queues for command management (Undo Stack & Command Queue)
- **Week 4**: Hash maps for efficient text search (Text Search Map)

## Architecture

### Core Components

1. **StringBuffer** (`src/main/strings/`)
   - Dynamic string management with automatic resizing
   - Operations: append, prepend, insert, remove, clear
   - Space complexity: O(n) where n is string length

2. **LineArray** (`src/main/arrays/`)
   - Dynamic array for storing editor lines
   - Operations: add, insert, remove lines
   - Space complexity: O(n) where n is number of lines

3. **UndoStack** (`src/main/stacks/`)
   - LIFO stack for undo/redo functionality
   - Stores command history for reversible operations
   - Space complexity: O(k) where k is number of commands

4. **CommandQueue** (`src/main/queues/`)
   - FIFO queue for command processing
   - Manages editor operation sequencing
   - Space complexity: O(m) where m is queued commands

5. **TextSearchMap** (`src/main/hashmaps/`)
   - Hash map for efficient text search and replace
   - Collision handling with chaining
   - Space complexity: O(n) average, O(n²) worst case

6. **TextEditor** (`src/main/`)
   - Main editor integrating all data structures
   - Provides unified interface for text editing operations

## Building the Project

### Prerequisites
- GCC compiler
- Make utility
- Windows environment (cmd.exe)

### Build Commands

```bash
# Build everything (main program and tests)
make all

# Build only the main text editor
make main

# Build only tests
make test

# Run all tests
make run_tests

# Clean build artifacts
make clean
```

### Individual Test Building
```bash
make test_string_buffer
make test_line_array
make test_undo_stack
make test_command_queue
make test_text_search
make test_text_editor
```

## Usage

### Running the Text Editor
```bash
bin/text_editor.exe
```

### Available Commands (once implemented)
- `insert <text>` - Insert text at cursor position
- `newline` - Create a new line
- `undo` - Undo last operation
- `find <text>` - Search for text in editor
- `replace <find> <replace>` - Replace all occurrences
- `print` - Display editor content
- `quit` - Exit the editor

### Example Session
```
> insert Hello World
> newline
> insert Second line
> print
1: Hello World
2: Second line
> find World
Found 1 occurrences
> replace World Universe
> print
1: Hello Universe
2: Second line
```

## Testing & Space Complexity Analysis

The project includes comprehensive unit tests with **space complexity verification** for each component:

- **test_string_buffer**: String manipulation, memory management, and O(n) space verification
- **test_line_array**: Dynamic array operations and O(n) space complexity testing
- **test_undo_stack**: LIFO stack operations and O(k) space analysis
- **test_command_queue**: FIFO queue operations and O(m) space verification
- **test_text_search**: Hash map functionality and O(n)/O(n²) space analysis
- **test_text_editor**: Integration testing with memory efficiency verification
- **test_space_analysis**: Comprehensive space complexity comparison and analysis

### Memory Tracking Features
- Real-time memory allocation tracking
- Peak memory usage monitoring
- Memory leak detection
- Space complexity ratio verification
- Worst-case scenario testing

Run individual tests:
```bash
bin/test_string_buffer.exe    # O(n) space verification
bin/test_line_array.exe       # O(n) space with line count
bin/test_undo_stack.exe       # O(k) space with command count
bin/test_space_analysis.exe   # Complete space analysis
```

## Space Complexity Analysis

| Component | Space Complexity | Measured Growth | Verification Method |
|-----------|------------------|-----------------|---------------------|
| StringBuffer | O(n) | Linear with string length | Memory tracking per character |
| LineArray | O(n) | Linear with line count | Memory tracking per line |
| UndoStack | O(k) | Linear with command count | Memory tracking per command |
| CommandQueue | O(m) | Linear with queued commands | Memory tracking per node |
| TextSearchMap | O(n) avg, O(n²) worst | Sublinear to quadratic | Collision scenario testing |

### Space Complexity Testing Features

1. **Memory Allocation Tracking**: Every malloc/realloc/free is monitored
2. **Growth Ratio Analysis**: Compares memory usage at different data sizes
3. **Peak Usage Monitoring**: Tracks maximum memory consumption
4. **Leak Detection**: Verifies all allocated memory is properly freed
5. **Worst-Case Scenarios**: Tests hash collisions and deep recursion

### Understanding Space Complexity Through Testing

- **O(1) Constant**: Memory usage doesn't change with input size
- **O(n) Linear**: Memory grows proportionally with input (strings, arrays)
- **O(k) Linear**: Memory grows with operation count (undo commands)
- **O(n²) Quadratic**: Memory can grow quadratically in worst case (hash collisions)

## Memory Optimization Features

1. **Dynamic Resizing**: All structures grow/shrink as needed
2. **Efficient String Operations**: Minimal memory copying
3. **Command Batching**: Queue operations for efficiency
4. **Hash Map Indexing**: Fast text search without full scans
5. **Stack-based Undo**: Memory-efficient command reversal

## Project Structure

```
TextEditor/
├── src/
│   ├── main/
│   │   ├── strings/          # String buffer implementation
│   │   ├── arrays/           # Dynamic line array
│   │   ├── stacks/           # Undo stack
│   │   ├── queues/           # Command queue
│   │   ├── hashmaps/         # Text search hash map
│   │   ├── text_editor.h/c   # Main editor integration
│   │   └── main.c            # Program entry point
│   └── tests/
│       ├── test_framework/   # Custom testing framework
│       └── test_*.c          # Individual component tests
├── Makefile                  # Build configuration
└── README.md                 # This file
```

## Learning Objectives

By completing this project, you'll learn:
- **Memory Management**: Manual allocation, reallocation, and deallocation with tracking
- **Data Structure Implementation**: Building fundamental structures from scratch in C
- **Space Complexity**: Measuring, analyzing, and verifying actual memory usage
- **Memory Optimization**: Understanding dynamic resizing strategies and efficiency
- **Testing Methodology**: Writing tests that verify space complexity quantitatively
- **Performance Analysis**: Observing memory usage patterns and growth characteristics
- **Modular Design**: Creating clean interfaces between components
- **Build Systems**: Using Makefiles for compilation and testing

### Weekly Learning Path

1. **Week 1 (Strings)**: Implement dynamic strings, understand O(n) space with string length
2. **Week 2 (Arrays)**: Build dynamic arrays, analyze O(n) space with element count and resizing
3. **Week 3 (Stacks/Queues)**: Create LIFO/FIFO structures, measure O(k) and O(m) space
4. **Week 4 (Hash Maps)**: Implement hash tables, explore O(n) average vs O(n²) worst-case scenarios

## Getting Started

1. Start with Week 1: Implement the StringBuffer functions in `src/main/strings/string_buffer.c`
2. Run tests to verify your implementation: `make test_string_buffer`
3. Use the space complexity tests to understand memory usage patterns
4. Move to Week 2 and continue through each component
5. Finally, integrate everything in the TextEditor component

## Implementation Hints

Each source file contains detailed comments explaining:
- What concepts to learn
- Key implementation considerations
- Questions to think about
- Space complexity implications

The comments guide you without giving away the exact solution, encouraging learning through discovery.

## Extension Ideas

Once you've completed the core implementation, consider adding:
- File I/O operations for loading/saving documents
- Syntax highlighting and language-specific features
- Multi-level undo/redo with branching
- Regular expression search and replace
- Performance profiling and memory usage analysis
- Optimized search indexing that doesn't rebuild every time