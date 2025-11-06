#include <iostream>
#include <sstream>
#include <string>
#include "FileSystem.h"
using namespace std;

int main() {

	FileSystem* fs = new FileSystem();

	string input, output, cmd, arg1, arg2;

	while(true) {
		cmd = arg1 = arg2 = "";
		cout << fs->pwd() << "> ";
		getline(cin, input);
		stringstream ss(input);
		ss >> cmd >> arg1 >> arg2;

		if (cmd == "exit") break;
		else if (cmd == "cd") output = fs->cd(arg1);
		else if (cmd == "ls") output = fs->ls();
		else if (cmd == "pwd") output = fs->pwd();
		else if (cmd == "tree") output = fs->tree();
		else if (cmd == "touch") output = fs->touch(arg1);
		else if (cmd == "mkdir") output = fs->mkdir(arg1);
		else if (cmd == "rm") output = fs->rm(arg1);
		else if (cmd == "rmdir") output = fs->rmdir(arg1);
		else if (cmd == "mv") output = fs->mv(arg1, arg2);
		else if (cmd == "load") {
			delete fs;
			fs = new FileSystem(arg1);
			output = "";
		}
		else output = "command not found";

		if (output != "") cout << output << endl;
	}

	delete fs;
}

