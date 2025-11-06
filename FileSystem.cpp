#include "FileSystem.h"
#include <iostream>

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling) {
	// IMPLEMENT ME
    name_ = name;
    isDir_ = isDir;
    parent_ = parent;
    leftmostChild_ = leftmostChild;
    rightSibling_ = rightSibling;

    // ROOT
    if(parent == nullptr) {
        // This is the root.
        if(name != "" || isDir != true) {
            // Comment out the following line when running tests.
            std::cerr << "Error: Invalid root node (must be directory with empty name)" << std::endl;
        }
    }
    // DIRECTORY

    // FILE

}

Node::~Node() {
	// IMPLEMENT ME

}

Node* Node::leftSibling() const {
	// IMPLEMENT ME

	return nullptr; // dummy
}

FileSystem::FileSystem() {
    // Initailise current directory to be root.
    curr_ = root_ = new Node("", true);

}

// DO NOT CHANGE
FileSystem::FileSystem(const string& testinput) {

	curr_ = root_ = new Node("", true);

	if (testinput == "1") {
		Node* e   = new Node("e"      , true , root_);
		Node* d   = new Node("d.txt"  , false, root_, nullptr, e);
		Node* c   = new Node("c.txt"  , false, root_, nullptr, d);
		Node* b   = new Node("b"      , true , root_, nullptr, c);
		Node* a   = new Node("a.txt"  , false, root_, nullptr, b);
		Node* ee  = new Node("ee.txt" , false, e);
		Node* bb2 = new Node("bb2"    , true , b);
		Node* bb1 = new Node("bb1"    , true , b, nullptr, bb2);
		Node* bbb = new Node("bbb.txt", false, bb1);
		root_->leftmostChild_ = a;
		b->leftmostChild_ = bb1;
		bb1->leftmostChild_ = bbb;
		e->leftmostChild_ = ee;
	}
	else if (testinput == "2") {
		Node* h = new Node("h"    , true , root_);
		Node* g = new Node("g.txt", false, root_, nullptr, h);
		Node* f = new Node("f"    , true , root_, nullptr, g);
		Node* e = new Node("e.txt", false, root_, nullptr, f);
		Node* d = new Node("d"    , true , root_, nullptr, e);
		Node* c = new Node("c.txt", false, root_, nullptr, d);
		Node* b = new Node("b"    , true , root_, nullptr, c);
		Node* a = new Node("a.txt", false, root_, nullptr, b);
		root_->leftmostChild_ = a;
	}
	else if (testinput == "3") {
		Node* c0 = new Node("c0", true, root_);
		Node* b0 = new Node("b0", true, root_, nullptr, c0);
		Node* a0 = new Node("a0", true, root_, nullptr, b0);
		Node* c1 = new Node("c1", true, a0);
		Node* b1 = new Node("b1", true, a0, nullptr, c1);
		Node* a1 = new Node("a1", true, a0, nullptr, b1);
		Node* c2 = new Node("c2", true, b0);
		Node* b2 = new Node("b2", true, b0, nullptr, c2);
		Node* a2 = new Node("a2", true, b0, nullptr, b2);
		Node* c3 = new Node("c3", true, c0);
		Node* b3 = new Node("b3", true, c0, nullptr, c3);
		Node* a3 = new Node("a3", true, c0, nullptr, b3);
		Node* c4 = new Node("c4", true, a1);
		Node* b4 = new Node("b4", true, a1, nullptr, c4);
		Node* a4 = new Node("a4", true, a1, nullptr, b4);
		root_->leftmostChild_ = a0;
		a0->leftmostChild_ = a1;
		b0->leftmostChild_ = a2;
		c0->leftmostChild_ = a3;
		a1->leftmostChild_ = a4;
	}
}

FileSystem::~FileSystem() {
	// IMPLEMENT ME

}

string FileSystem::cd(const string& path) {
	// IMPLEMENT ME

	return ""; // dummy
}

// This is done for you as an example
string FileSystem::ls() const {

	string res;

	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		res += tmp->name_;
		if (tmp->isDir_) res += "/\n";
		else res += "\n";
		tmp = tmp->rightSibling_;
	}
	if (res != "") res.pop_back(); // remove extra \n

	return res;
}

string FileSystem::pwd() const {
	// Opposite of ls, build the path from curr_ to root_.

    string res; 

    Node* tmp = curr_;
    while(tmp != root_) {
        res = "/" + tmp->name_ + res;
        tmp = tmp->parent_;
    }
    if (res == "") res = "/"; // root case.


	return res; 
}

string FileSystem::tree() const {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::touch(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::mkdir(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::rm(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::rmdir(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest) {
	// IMPLEMENT ME

	return ""; // dummy
}
