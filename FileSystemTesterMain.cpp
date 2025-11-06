#include <iostream>
#include "FileSystemTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { FileSystemTester t; t.testa(); } break;
		case 'b': { FileSystemTester t; t.testb(); } break;
		case 'c': { FileSystemTester t; t.testc(); } break;
		case 'd': { FileSystemTester t; t.testd(); } break;
		case 'e': { FileSystemTester t; t.teste(); } break;
		case 'f': { FileSystemTester t; t.testf(); } break;
		case 'g': { FileSystemTester t; t.testg(); } break;
		case 'h': { FileSystemTester t; t.testh(); } break;
		case 'i': { FileSystemTester t; t.testi(); } break;
		case 'j': { FileSystemTester t; t.testj(); } break;
		case 'k': { FileSystemTester t; t.testk(); } break;
		case 'l': { FileSystemTester t; t.testl(); } break;
		case 'm': { FileSystemTester t; t.testm(); } break;
		case 'n': { FileSystemTester t; t.testn(); } break;
		case 'o': { FileSystemTester t; t.testo(); } break;
		case 'p': { FileSystemTester t; t.testp(); } break;
		case 'q': { FileSystemTester t; t.testq(); } break;
		case 'r': { FileSystemTester t; t.testr(); } break;
		case 's': { FileSystemTester t; t.tests(); } break;
		case 't': { FileSystemTester t; t.testt(); } break;
		case 'u': { FileSystemTester t; t.testu(); } break;
		case 'v': { FileSystemTester t; t.testv(); } break;
		case 'w': { FileSystemTester t; t.testw(); } break;
		case 'x': { FileSystemTester t; t.testx(); } break;
		case 'y': { FileSystemTester t; t.testy(); } break;
		case 'z': { FileSystemTester t; t.testz(); } break;
		default: { cout << "Options are a -- z." << endl; } break;
	       	}
	}
	return 0;
}

