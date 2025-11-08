#include "FileSystem.h"
#include <iostream>
#include <string>


/* 
==================================
// My private helper methods.
==================================
*/

// Used by cd() to handle special navigation cases like "..", ".", "/", "~".
// For commands that need to interpret special paths.
// Future use: extended for more complex path parsing.
string FileSystem::handleSpecialPaths(const string& path) {
    if (path == "..") {
        if (curr_ == root_) {
            return "invalid path";
        }
        curr_ = curr_->parent_;
        return "";
    }

    if (path == "/" || path == "~") {
        curr_ = root_;
        return "";
    }

    if (path == ".") {
        return "";
    }

    return "continue";  // Signal to continue with child search.
}

// Used by navigateToChild(), mkdir(), touch(), rm()  to search for child nodes by name
// For commands that need to find specific child nodes.
Node* FileSystem::findChild(const string& name) const {
    Node* tmp = curr_->leftmostChild_;
    while(tmp != nullptr) {
        if(tmp->name_ == name) {
            return tmp;
        }
        tmp = tmp->rightSibling_;
    }
    return nullptr;
}

// Used by cd() to move to a child directory by name
// For commands that need to validate directory paths.
string FileSystem::navigateToChild(const string& path) {
    Node* child = findChild(path);
    if (child == nullptr) {
        return "invalid path";
    }

    if (!child->isDir_) {
        return "invalid path";
    }

    curr_ = child;
    return ""; // success.
}

// by mkdir() and touch() to insert new child nodes in alphabetical order.
// Future use: any command that adds new files/directories.
void FileSystem::insertChildAlphabetical(Node* newNode){
    if(curr_->leftmostChild_ == nullptr || curr_->leftmostChild_->name_ > newNode->name_)
    {
        // Insert as the leftmost child.
        newNode->rightSibling_ = curr_->leftmostChild_;
        curr_->leftmostChild_ = newNode;
    } else {
        // Find alphabetical location to insert.
        Node* prev = curr_->leftmostChild_;
        Node* next = prev->rightSibling_;
        while(next != nullptr && next->name_ < newNode->name_) {
            prev = next;
            next = next->rightSibling_;
        }
        // Insert at the location found (with prev and next set).
        newNode-> rightSibling_ = next;
        prev->rightSibling_ = newNode;
    }
}

// Used by tree() to recursively traverse and format directory structure.
// Future use: any command that needs hierarchical directory display.
string FileSystem::treeRecursion(Node* node, int nestCount) const {
    string res = "";
    Node* tmp = node->leftmostChild_;

    while(tmp != nullptr) {
        // Indent and add current node.
        res += std::string(nestCount + 1, ' ') + tmp->name_;
        if (tmp->isDir_ ) {
            res += "/";
        } 
        res += "\n";
        
        // Traverse into leftmost child.
        if(tmp->leftmostChild_ != nullptr) {
            string childRes = treeRecursion(tmp, nestCount + 1);
            if(!childRes.empty()) {
                res += childRes + "\n";
            }
        }
        tmp = tmp->rightSibling_;
    }
    // remove extra \n like in predefined ls().
    if (res != "") res.pop_back(); 
    return res; // return tree path from curr_.

}

// Used by rm() and rmdir() to remove child nodes from the current directory.
// For any command that deletes files/directories.
void FileSystem::deleteChild(Node* removeTarget) {
    // This function handles recursive deletion of nodes (files and dirs).
    
    if (curr_->leftmostChild_ == removeTarget){
        // Remove the target from the list. Becomes the leftmost child.
        curr_->leftmostChild_ = removeTarget->rightSibling_;
        } else {
            // prev points to the sibling before removeTarget.
            Node* prev = curr_->leftmostChild_;
            while (prev->rightSibling_ != removeTarget) {
                prev = prev->rightSibling_;
            }
            prev->rightSibling_ = removeTarget->rightSibling_;
        }
        delete removeTarget; // Free memory.
}
// Used by mv() to detach a node from current position in file system before reattaching it elsewhere.
// For commands that move files/directories.
void FileSystem::detachChild(Node* node){
    if (curr_->leftmostChild_ == node) {
            curr_->leftmostChild_ = node->rightSibling_;
        } else {
            Node* prev = curr_->leftmostChild_;
            while (prev->rightSibling_ != node) {
                prev = prev->rightSibling_;
            }
            prev->rightSibling_ = node->rightSibling_;
        }
}


// Used by mv() to rename nodes without changing their location.
// For commands that rename files/directories.
string FileSystem::renameChild(const string& src, const string& dest){
    Node* srcNode = findChild(src);
    if (findChild(dest)) return "file/directory already exists";
    detachChild(srcNode);
    srcNode->name_ = dest;
    insertChildAlphabetical(srcNode);
    return ""; // success
}

// Used by mv() to move nodes between directories.
// For commands that move files/directories.
string FileSystem::moveChild(const string& src, const string& dest){
    Node* srcNode = findChild(src);
    if(!srcNode){return "source does not exist";} // Null check.

    Node* destNode = findChild(dest);
    // Catch .. case earlier in mv().
    if (dest == "..")
    {
        destNode = curr_->parent_;
    } else {
        if(!destNode){return "destination does not exist";} // Null check.
        if(!destNode->isDir_){return "destination is not a directory";} // Dir check.
    }
    
    // Check for conflicts before detaching.
    Node* originalCurr = curr_;
    curr_ = destNode;
    if (findChild(srcNode->name_)) {
        curr_ = originalCurr;
        return "destination already has file/directory of same name";
    }
    curr_ = originalCurr;

    detachChild(srcNode);
    srcNode->parent_ = destNode;

    // Insert into destination directory in alphabetical order.
    curr_ = destNode;
    insertChildAlphabetical(srcNode);
    curr_ = originalCurr; // Restore curr_.
    return ""; // success
}

/* 
==================================
// Where predefined methods start.
==================================
*/

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling) {
    // Initialise attributes.
    name_ = name;
    isDir_ = isDir;
    parent_ = parent;
    leftmostChild_ = leftmostChild;
    rightSibling_ = rightSibling;
}

Node::~Node() {
	// IMPLEMENT ME

}

Node* Node::leftSibling() const {
	/*
    /   Not implemented.
    /   I assume this was intended to be used as a potential helper function for other methods.
    /   My guess i was intended to help similar to insertChildAlphabetical() to find the previous sibling.
    */

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
    // should delete all children nodes of root_ recursively AFTER we implement recurive node deletiion
    //delete root_;  // Now this triggers recursive deletion

}

string FileSystem::cd(const string& path) {
    // navigate to the directory specified by path and update curr_.
    string result = handleSpecialPaths(path);
    if (result != "continue") return result;

    return navigateToChild(path);
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
	// Append right sibling and leftmost child strings recursively to result.

    string res = "";
    // Determine if at root.
    if(curr_ == root_ && curr_->leftmostChild_ == nullptr) {
        res += "/";
    }else if(curr_ == root_) {
        res += + "/\n" + treeRecursion(curr_, 0);
    }else
    {
        res += curr_->name_ + "/\n" + treeRecursion(curr_, 0);
    }
    return res;
}

string FileSystem::touch(const string& name) {
	// Create new file node as child of curr_, keeping alphabetical ordering.
    
    if(name == "" ) {
        return "invalid name";
    }

    // Traverse list and check for existing file/directory with same name.
    Node* existing = findChild(name);
    if(existing != nullptr) {
        return "file/directory already exists";
    }

    Node* newFile = newFile = new Node(name, false, curr_);
    // Insert new File node in alphabetical order among siblings.
    insertChildAlphabetical(newFile);
	return ""; // success.
}

string FileSystem::mkdir(const string& name) {
	// Create new directory node as child of curr_, keeping alphabetical ordering.
    
    if(name == "" ) {
        return "invalid name";
    }

    // Traverse list and check for existing file/directory with same name.
    Node* existing = findChild(name);
    if(existing != nullptr) {
        return "file/directory already exists";
    }

    Node* newDir = new Node(name, true, curr_);
    // Insert new Dir node in alphabetical order among siblings.
    insertChildAlphabetical(newDir);

	return ""; // success.
}

string FileSystem::rm(const string& name) {
	// Search for node by name and remove it if it's a file.

    Node* removeTargetFile = findChild(name);
    if (removeTargetFile == nullptr) {
        return "file not found";
    }

    if (removeTargetFile->isDir_) {
        return "not a file";
    }
    
    // Remove target from sibling list.
    deleteChild(removeTargetFile);
	return ""; // success.
}

string FileSystem::rmdir(const string& name) {
	// Search for dir by name and remove if it's a directory and empty.

    Node* removeTargetDir = findChild(name);
    if (removeTargetDir == nullptr) {
        return "directory not found";
    }

    if (!removeTargetDir->isDir_) {
        return "not a directory";
    }

    if (removeTargetDir->leftmostChild_ != nullptr) {
        return "directory not empty";
    }

    // Remove target from sibling list.
    deleteChild(removeTargetDir);
	return ""; // success.
}

string FileSystem::mv(const string& src, const string& dest) {
	// move or rename a file/directory from src to dest.

    if(src == dest) {
        return "source and destination are the same";
    }

    if (dest == ".." && curr_ == root_) {
        return "invalid path";
    }
    
    // Traverse children to find source node.
    Node* srcNode = findChild(src);
    if (!srcNode) { return "source does not exist";} // Null check.

    // Move.

    // Traverse children to find destination node.
    Node* destNode = findChild(dest);
    if (dest == "..") {
        Node* parentNode = curr_->parent_;
        // Move to parent directory and detach source node from current location.
        string res = moveChild(src, "..");
        return res;
    } else if (destNode != nullptr && !destNode->isDir_) {
        if (srcNode->isDir_){
            return "source is a directory but destination is an existing file";
        }else{
            return "destination already has file of same name";
        }
    } else if (destNode != nullptr && destNode->isDir_) {
        string res = moveChild(src, dest);
        return res;
    }
    
    // Rename.

    // Check if destination in the same directory as source (rename case).
    if (destNode == nullptr) {
        return renameChild(src, dest);
    }

    return "destination already has file/directory of same name";
}