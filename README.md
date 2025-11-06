# C++ File System Emulator

## Overview 

Terminal file system emulator implementing a tree-based directory structure utilising left-child and right-child representations as part of CO3105 Assignment 1.


## Implementation

### Core Classes:
- **Node**: Represents files/directories with pointers to parent, leftmost child, and right sibling.
- **FileSystem**: Manages the tree structure with root and current directory pointers.

### Key Functions

#### FileSystem Class
- **Navigation**: `cd()`, `pwd(), `ls()`, `tree()`
- **File Operations**:  `touch()`, `rm()`
- **Directory operations**: `mkdir()`, `rmdir()`
- **Move/Rename**: `mv()` with source/destination handling


## Technical Constraints
- No STL containers or smart pointers
- Maintain alphabetical ordering of siblings
- Proper memory management required
- Left-child right-sibling tree representation

## Project Structure
```
Cpp_FileSystem_Emulator/
├── README.md
├── FileSystem.h          (to implement)
├── FileSystem.cpp        (to implement)
├── main.cpp              (provided)
├── FileSystemTester.h    (provided)
├── FileSystemTester.cpp  (provided)
├── FileSystemTesterMain.cpp (provided)
└── makefile              (provided)
```

## Files
- `FileSystem.h` / `FileSystem.cpp` - Your implementation
- `main.cpp` - Terminal emulator (provided)
- Test suite and makefile (provided)


## Running the Project

### Terminal Emulator
```bash
make
./main
```

### Testing
```bash
make
./FileSystemTesterMain [test_cases]
```

## File System Structure Exampleto
```
/
├── a.txt
├── b/
│   ├── bb1/
│   │   └── bbb.txt
│   └── bb2/
├── c.txt
├── d.txt
└── e/
    └── ee.txt
```

**Tree Representation (Left-Child Right-Sibling):**
```
Root → a.txt → b → c.txt → d.txt → e
       ↓       ↓              ↓
      null    bb1 → bb2      ee.txt
              ↓     ↓         ↓
             bbb.txt null    null
             ↓
            null
```

## Key Features
- Hierarchical file/directory structure
- Path navigation (absolute/relative)
- Tree visualization with proper indentation
- File/directory creation, deletion, and movement
- Alphabetical ordering maintenance