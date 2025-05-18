# In-Memory File System

A C++ implementation of an in-memory file system using tree-based data structures.

## Overview

This project implements a virtual file system in memory that supports various file operations:
- Creating files, folders, and symbolic links
- Reading from and writing to files
- Copying, moving, and removing nodes
- File system traversal
- Mounting and unmounting external file systems

The implementation uses a tree structure with different node types:
- **File**: Stores text content
- **Folder**: Contains other nodes (files, folders, links)
- **Link**: References another node

## Building the Project

### Prerequisites

- CMake (3.10 or higher)
- C++ compiler with C++14 support
- Git (for fetching dependencies)

### Build Steps

1. Clone the repository:
   ```bash
   git clone git@github.com:adnanhd/213-pa2.git in-memory-filesystem
   cd in-memory-filesystem
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure with CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

This will create two executables:
- `FileSystem_Main`: The main program
- `FileSystem_Tests`: The test suite

## Running the Program

After building, you can run the main program:

```bash
./FileSystem_Main
```

This will execute the sample code that demonstrates file system operations.

## Running Tests

To run the test suite:

```bash
./FileSystem_Tests
```

Or use CTest:

```bash
ctest
```

For verbose test output:

```bash
ctest --verbose
```

To run the tests with the custom target:

```bash
cmake --build . --target run_tests
```

## Project Structure

```
.
├── include/               # Header files
│   ├── Node.h             # Base class for nodes
│   ├── File.h             # File node
│   ├── Folder.h           # Folder node
│   ├── Link.h             # Link node
│   └── FileSystem.h       # FileSystem implementation
├── src/                   # Source files
│   ├── Node.cpp
│   ├── File.cpp
│   ├── Folder.cpp
│   ├── Link.cpp
│   ├── FileSystem.cpp
│   └── main.cpp           # Main program entry point
├── tests/                 # Test files
│   └── FileSystemTests.cpp
├── CMakeLists.txt         # CMake build configuration
└── README.md              # This file
```

## Generating Documentation

This project uses Doxygen for documentation generation. The source code already contains Doxygen-compatible comments.

### Prerequisites

- Doxygen
- Graphviz (optional, for generating diagrams)

### Steps to Generate Documentation

1. Install Doxygen:
   ```bash
   # Ubuntu/Debian
   sudo apt install doxygen graphviz

   # macOS
   brew install doxygen graphviz

   # Windows
   # Download and install from https://www.doxygen.nl/download.html
   ```

2. Create a Doxyfile:
   ```bash
   doxygen -g
   ```

3. Edit the Doxyfile to configure documentation:
   ```
   PROJECT_NAME           = "In-Memory File System"
   INPUT                  = ../include ../src
   OUTPUT_DIRECTORY       = ./docs
   RECURSIVE              = YES
   EXTRACT_ALL            = YES
   EXTRACT_PRIVATE        = YES
   EXTRACT_STATIC         = YES
   HAVE_DOT               = YES  # Set to NO if Graphviz is not installed
   UML_LOOK               = YES
   CALL_GRAPH             = YES
   CALLER_GRAPH           = YES
   ```

4. Generate documentation:
   ```bash
   doxygen Doxyfile
   ```

5. The documentation will be available in the `docs` directory. Open `docs/html/index.html` in a web browser to view it.

## Common Issues and Solutions

### Double Deletion in `recursive_delete`

A common issue occurs when implementing the `recursive_delete` function, which can lead to double deletion of memory. This happens because:

1. `recursive_delete` deletes a node and all its descendants
2. `Folder::~Folder()` already deletes all children in the folder's destructor

The solution is to:
- First remove child nodes from their parent's list
- Then recursively delete them individually
- This prevents double deletion since each node is removed from its parent before being deleted

### Memory Management

This project heavily relies on proper memory management. Some tips:
- Always use `delete` to free memory you've allocated with `new`
- Be careful with ownership semantics, especially for links (which refer to nodes but don't own them)
- Use smart pointers where appropriate if you extend the project

## Extensions and Enhancements

Here are some potential enhancements for the project:

1. **Add file permissions system**
2. **Support for binary file content**
3. **Implementing a search functionality**
4. **Adding a journaling system for operations**
5. **Converting to use smart pointers instead of raw pointers**
6. **Adding serialization to persist the file system**

## License

MIT
