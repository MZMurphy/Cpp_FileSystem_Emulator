makefile ran but failed with linker errors because the FileSystem class methods are not implemented in FileSystem.cpp. The makefile is working correctly - it's compiling the code but failing
   at the linking stage because all the FileSystem methods referenced in main.cpp and the test files are missing their implementations.

  The undefined symbols show that these FileSystem methods need to be implemented:
  - Constructor FileSystem()
  - Constructor FileSystem(const std::string&)
  - Destructor ~FileSystem()
  - cd(const std::string&)
  - mv(const std::string&, const std::string&)
  - rm(const std::string&)
  - mkdir(const std::string&)
  - rmdir(const std::string&)
  - touch(const std::string&)
  - ls() const
  - pwd() const
  - tree() const

## Test Case Explanations

### Constructor and Basic Operations Tests (testa, testb)
- **testa()**: Tests default constructor - creates empty filesystem, checks ls() returns empty string and pwd() returns "/"
- **testb()**: Tests parameterized constructor with "1" - loads predefined filesystem structure, verifies ls() shows correct files/directories and pwd() returns "/"

### Directory Navigation Tests (testc, testd, teste)
- **testc()**: Tests basic cd operations - cd into "b" directory, verify ls/pwd, then cd back to parent with "..", verify correct state
- **testd()**: Tests deeper navigation - cd through multiple levels (b/bb1), then cd to root with "/", verify correct directory listing
- **teste()**: Tests cd error handling - attempts to cd into files, non-existent directories, and beyond root, ensures proper error messages and pwd remains unchanged

### Tree Display Tests (testf, testg)
- **testf()**: Tests tree() function on empty filesystem and flat structure ("2"), verifies proper tree formatting with indentation
- **testg()**: Tests tree() on deeper structure ("1"), verifies hierarchical display with proper indentation, tests tree from subdirectory

### File/Directory Creation Tests (testh, testi, testj)
- **testh()**: Tests mkdir and touch on empty filesystem - creates directory, navigates into it, creates file, verifies listings
- **testi()**: Tests alphabetical ordering - creates multiple files/directories with various names, verifies they appear in correct alphabetical order
- **testj()**: Tests creation error handling - attempts to create duplicate files/directories, ensures proper error messages and no changes to filesystem

### File/Directory Removal Tests (testk, testl, testm, testn)
- **testk()**: Basic rm/rmdir operations - removes files and directories, verifies they disappear from listings
- **testl()**: Tests removal from different positions - head, tail, and only child scenarios, verifies correct remaining structure
- **testm()**: Tests removal error handling - attempts to rm directories and rmdir files, ensures proper error messages
- **testn()**: Tests removal error handling continued - attempts to remove non-existent items and non-empty directories, verifies error messages

### Move/Rename Operations Tests (testo, testp, testq, testr, tests, testt, testu)
- **testo()**: Tests simple rename operations - renames files and directories without changing their position in hierarchy
- **testp()**: Tests rename with alphabetical reordering - renames items that change their alphabetical position, verifies new ordering
- **testq()**: Tests moving files/directories into subdirectories, verifies tree structure changes
- **testr()**: Tests moving entire subdirectories into other subdirectories, verifies complex tree restructuring
- **tests()**: Tests moving items to parent directory using "..", verifies upward movement in hierarchy
- **testt()**: Tests mv error handling - non-existent source, same source/destination, invalid paths, verifies error messages
- **testu()**: Tests mv error handling continued - destination conflicts, directory vs file conflicts, verifies appropriate error messages

### Hidden Tests (testv, testw, testx, testy)
- **testv-testy()**: These are placeholder "hidden" tests with empty implementations, likely for instructor use

### Bonus Advanced Path Test (testz)
- **testz()**: Advanced test for absolute/relative path handling - tests complex path operations like "b/bb1", "../../e", "/e/ee2.txt", etc. This is an optional bonus feature that handles more sophisticated path parsing similar to actual Linux commands