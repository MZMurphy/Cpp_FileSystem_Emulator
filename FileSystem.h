#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>
using std::string;

class Node {

	string name_;         // name of the file/directory
	bool isDir_;          // is this node a directory or not
	Node* parent_;        // pointer to parent
	Node* leftmostChild_; // pointer to leftmost child
	Node* rightSibling_;  // pointer to next (right side) sibling

	// return pointer to previous (left side) sibling
	// (if your compiler is too old to understand [[nodiscard]],
	// you can remove this keyword, and same for other functions below)
	[[nodiscard]] Node* leftSibling() const;

	// you are allowed to add other members

public:
	// parameterised constructor
	// The "= nullptr" notation means by default the argument is nullptr
	// if not supplied by the caller. There is nothing special you need
	// to do about this syntax: just implement the function as if they
	// are not there.
	Node(const string& name, bool isDir, Node* parent = nullptr, Node* leftmostChild = nullptr, Node* rightSibling = nullptr);

	// destructor
	~Node();

friend class FileSystem; // allow FileSystem to access private members
};

class FileSystem {

	Node* root_; // pointer to root directory
	Node* curr_; // pointer to current directory

	// you are allowed to add other members

public:
	// default constructor
	FileSystem();

	// parameterised constructor
	FileSystem(const string& testinput);

	// destructor
	~FileSystem();

	// change directory
	string cd(const string& path);

	// list directory contents
	[[nodiscard]] string ls() const;

	// display subtree contents
	[[nodiscard]] string tree() const;

	// print working directory
	[[nodiscard]] string pwd() const;

	// create new file
	string touch(const string& name);

	// create new directory
	string mkdir(const string& name);

	// remove file
	string rm(const string& name);

	// remove directory
	string rmdir(const string& name);

	// move file/directory from src to dest
	string mv(const string& src, const string& dest);
};

#endif
