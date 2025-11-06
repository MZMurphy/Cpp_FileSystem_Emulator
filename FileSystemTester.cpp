#include <iostream>
#include "FileSystemTester.h"
#include "FileSystem.h"

using namespace std;

FileSystemTester::FileSystemTester() : error_(false), funcname_("") {}

// default ctor, pwd
void FileSystemTester::testa() {
	funcname_ = "FileSystemTester::testa";
	string s, ans;
	{

	FileSystem fs;

	s = fs.ls();
	ans = "";
	if (s != ans)
		errorOut_("def ctor wrong ls: ", ans, s, 1);

	s = fs.pwd();
	ans = "/";
	if (s != ans)
		errorOut_("def ctor wrong pwd: ", ans, s, 2);

	}
	passOut_();
}

// param ctor, pwd
void FileSystemTester::testb() {
	funcname_ = "FileSystemTester::testb";
	string s, ans;
	{

	FileSystem fs("1");

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("param ctor wrong ls: ", ans, s, 1);

	s = fs.pwd();
	ans = "/";
	if (s != ans)
		errorOut_("param ctor wrong pwd: ", ans, s, 2);

	}
	passOut_();
}

// cd, cd.., pwd
void FileSystemTester::testc() {
	funcname_ = "FileSystemTester::testc";
	string s, ans;
	{

	FileSystem fs("1");

	fs.cd("b");
	s = fs.ls();
	ans = "bb1/\nbb2/";
	if (s != ans)
		errorOut_("cd b wrong ls: ", ans, s, 1);
	s = fs.pwd();
	ans = "/b";
	if (s != ans)
		errorOut_("cd b wrong pwd: ", ans, s, 1);

	fs.cd("..");
	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("cd .. wrong ls: ", ans, s, 2);
	s = fs.pwd();
	ans = "/";
	if (s != ans)
		errorOut_("cd .. wrong pwd: ", ans, s, 2);

	}
	passOut_();
}

// cd deeper, to root
void FileSystemTester::testd() {
	funcname_ = "FileSystemTester::testd";
	string s, ans;
	{

	FileSystem fs("1");

	fs.cd("b");
	fs.cd("bb1");
	s = fs.ls();
	ans = "bbb.txt";
	if (s != ans)
		errorOut_("cd bb1 wrong ls: ", ans, s, 1);
	s = fs.pwd();
	ans = "/b/bb1";
	if (s != ans)
		errorOut_("cd bb1 wrong pwd: ", ans, s, 1);

	fs.cd("/");
	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("cd / wrong ls: ", ans, s, 2);
	s = fs.pwd();
	ans = "/";
	if (s != ans)
		errorOut_("cd / wrong pwd: ", ans, s, 2);

	}
	passOut_();
}

// cd err msg
void FileSystemTester::teste() {
	funcname_ = "FileSystemTester::teste";
	string s, ans;
	{

	FileSystem fs("1");

	// cd into non-directory
	s = fs.cd("c.txt");
	ans = "invalid path";
	if (s != ans)
		errorOut_("cd into file wrong error message: ", ans, s, 1);

	// cd into non-existent directory
	s = fs.cd("zzz");
	if (s != ans)
		errorOut_("cd into non-exist dir wrong error message: ", ans, s, 1);

	// cd .. beyond root
	s = fs.cd("..");
	if (s != ans)
		errorOut_("cd .. beyond root wrong error message: ", ans, s, 1);

	// check pwd unchanged
	s = fs.pwd();
	ans = "/";
	if (s != ans)
		errorOut_("after invalid cd wrong pwd: ", ans, s, 2);

	// normal operation
	s = fs.cd("b");
	ans = "";
	if (s != ans)
		errorOut_("after valid cd wrong return string: ", ans, s, 2);

	}
	passOut_();
}

// tree
void FileSystemTester::testf() {
	funcname_ = "FileSystemTester::testf";
	string s, ans;
	{
	// empty
	FileSystem fs;
	s = fs.tree();
	ans = "/";
	if (s != ans)
		errorOut_("def ctor wrong tree: ", ans, s, 1);

	}
	{
	// flat
	FileSystem fs("2");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n c.txt\n d/\n e.txt\n f/\n g.txt\n h/";
	if (s != ans)
		errorOut_("param ctor 2 wrong tree: ", ans, s, 2);

	}
	passOut_();
}

// deeper tree
void FileSystemTester::testg() {
	funcname_ = "FileSystemTester::testg";
	string s, ans;
	{

	FileSystem fs("1");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt\n e/\n  ee.txt";
	if (s != ans)
		errorOut_("param ctor 1 wrong tree: ", ans, s, 1);

	fs.cd("b");
	s = fs.tree();
	ans = "b/\n bb1/\n  bbb.txt\n bb2/";
	if (s != ans)
		errorOut_("after cd wrong tree: ", ans, s, 2);

	}
	passOut_();
}

// touch/mkdir from empty / as only child
void FileSystemTester::testh() {
	funcname_ = "FileSystemTester::testh";
	string s, ans;
	{

	FileSystem fs;
	fs.mkdir("test");
	s = fs.ls();
	ans = "test/";
	if (s != ans)
		errorOut_("mkdir test wrong ls: ", ans, s, 1);

	fs.cd("test");
	fs.touch("test.txt");
	s = fs.ls();
	ans = "test.txt";
	if (s != ans)
		errorOut_("touch test.txt wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// touch/mkdir alpha order
void FileSystemTester::testi() {
	funcname_ = "FileSystemTester::testi";
	string s, ans;
	{

	FileSystem fs("2");

	fs.touch("i.txt"); // tail
	fs.mkdir("j");
	fs.mkdir("B"); // head
	fs.touch("A.txt");
	s = fs.ls();
	ans = "A.txt\nB/\na.txt\nb/\nc.txt\nd/\ne.txt\nf/\ng.txt\nh/\ni.txt\nj/";
	if (s != ans)
		errorOut_("insert heads/tails wrong ls: ", ans, s, 1);

	fs.touch("d2.txt"); // middle
	fs.mkdir("d3");
	fs.touch("A3.txt"); // second
	fs.mkdir("A2");
	fs.mkdir("i2"); // second from last
	fs.touch("i3.txt");
	s = fs.ls();
	ans = "A.txt\nA2/\nA3.txt\nB/\na.txt\nb/\nc.txt\nd/\nd2.txt\nd3/\ne.txt\nf/\ng.txt\nh/\ni.txt\ni2/\ni3.txt\nj/";
	if (s != ans)
		errorOut_("insert middles wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// touch/mkdir err msg
void FileSystemTester::testj() {
	funcname_ = "FileSystemTester::testj";
	string s, ans;
	{

	FileSystem fs("1");

	ans = "file/directory already exists";
	s = fs.mkdir("e");
	if (s != ans)
		errorOut_("mkdir e wrong error message", ans, s, 1);
	s = fs.touch("c.txt");
	if (s != ans)
		errorOut_("touch c.txt wrong error message", ans, s, 1);

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("after invalid touch/mkdir wrong ls: ", ans, s, 1);

	// normal operation
	ans = "";
	s = fs.touch("f.txt");
	if (s != ans)
		errorOut_("after valid touch wrong return string: ", ans, s, 2);
	s = fs.mkdir("g");
	if (s != ans)
		errorOut_("after valid mkdir wrong return string: ", ans, s, 2);

	}
	passOut_();
}

// basic rm/rmdir
void FileSystemTester::testk() {
	funcname_ = "FileSystemTester::testk";
	string s, ans;
	{

	FileSystem fs("2");
	fs.rm("c.txt");
	s = fs.ls();
	ans = "a.txt\nb/\nd/\ne.txt\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("rm c.txt wrong ls: ", ans, s, 1);

	}
	{

	FileSystem fs("2");
	fs.rmdir("f");
	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd/\ne.txt\ng.txt\nh/";
	if (s != ans)
		errorOut_("rmdir f wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// rm/rmdir other positions
void FileSystemTester::testl() {
	funcname_ = "FileSystemTester::testl";
	string s, ans;
	{
	// head
	FileSystem fs("2");

	fs.rm("a.txt");
	s = fs.ls();
	ans = "b/\nc.txt\nd/\ne.txt\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("rm a.txt wrong ls: ", ans, s, 1);

	fs.rmdir("b");
	s = fs.ls();
	ans = "c.txt\nd/\ne.txt\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("rmdir b wrong ls: ", ans, s, 1);

	}
	{
	// tail
	FileSystem fs("2");

	fs.rmdir("h");
	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd/\ne.txt\nf/\ng.txt";
	if (s != ans)
		errorOut_("rmdir h wrong ls: ", ans, s, 1);

	fs.rm("g.txt");
	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd/\ne.txt\nf/";
	if (s != ans)
		errorOut_("rm g.txt wrong ls: ", ans, s, 1);

	}
	{
	// only child
	FileSystem fs("1");
	fs.cd("b");
	fs.cd("bb1");
	fs.rm("bbb.txt");
	s = fs.ls();
	ans = "";
	if (s != ans)
		errorOut_("rm bbb.txt wrong ls: ", ans, s, 2);

	// head of deeper dir
	fs.cd("..");
	fs.rmdir("bb1");
	s = fs.ls();
	ans = "bb2/";
	if (s != ans)
		errorOut_("rmdir bb1 wrong ls: ", ans, s, 2);

	}

	passOut_();
}

// rm/rmdir err msg
void FileSystemTester::testm() {
	funcname_ = "FileSystemTester::testm";
	string s, ans;
	{

	FileSystem fs("1");

	// wrong type
	s = fs.rm("e");
	ans = "not a file";
	if (s != ans)
		errorOut_("rm e wrong error message: ", ans, s, 1);

	s = fs.rmdir("a.txt");
	ans = "not a directory";
	if (s != ans)
		errorOut_("rmdir a.txt wrong error message: ", ans, s, 1);

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("after invalid rm/rmdir wrong ls: ", ans, s, 1);

	// normal operation
	s = fs.rm("c.txt");
	ans = "";
	if (s != ans)
		errorOut_("after valid rm wrong return string: ", ans, s, 2);
	fs.cd("b");
	s = fs.rmdir("bb2");
	if (s != ans)
		errorOut_("after valid rmdir wrong return string: ", ans, s, 2);

	}
	passOut_();
}

// rm/rmdir err msg 2
void FileSystemTester::testn() {
	funcname_ = "FileSystemTester::testn";
	string s, ans;
	{
	// not exist
	FileSystem fs("1");
	s = fs.rm("ee.txt");
	ans = "file not found";
	if (s != ans)
		errorOut_("rm ee.txt wrong error message: ", ans, s, 1);

	s = fs.rmdir("bb1");
	ans = "directory not found";
	if (s != ans)
		errorOut_("rmdir bb1 wrong error message: ", ans, s, 1);

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("rm/rmdir non-existent wrong ls: ", ans, s, 1);

	}
	{
	// non-empty dir
	FileSystem fs("1");
	s = fs.rmdir("e");
	ans = "directory not empty";
	if (s != ans)
		errorOut_("rmdir e wrong error message: ", ans, s, 2);

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("rmdir non-empty wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// rename leaves w/o changing ordering
void FileSystemTester::testo() {
	funcname_ = "FileSystemTester::testo";
	string s, ans;
	{
	// file
	FileSystem fs("2");
	fs.mv("c.txt", "c2.txt");
	s = fs.ls();
	ans = "a.txt\nb/\nc2.txt\nd/\ne.txt\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("mv c.txt c2.txt wrong ls: ", ans, s, 1);

	}
	{
	// dir and deeper (and head)
	FileSystem fs("1");
	fs.cd("b");
	fs.mv("bb1", "bb0");
	s = fs.ls();
	ans = "bb0/\nbb2/";
	if (s != ans)
		errorOut_("mv bb1 bb0 wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// mv leaves within same dir, alpha ordering
void FileSystemTester::testp() {
	funcname_ = "FileSystemTester::testp";
	string s, ans;
	{
	// file
	FileSystem fs("2");
	fs.mv("e.txt", "A.txt");
	s = fs.ls();
	ans = "A.txt\na.txt\nb/\nc.txt\nd/\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("mv e.txt A.txt wrong ls: ", ans, s, 1);

	fs.mv("A.txt", "a2.txt");
	s = fs.ls();
	ans = "a.txt\na2.txt\nb/\nc.txt\nd/\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("mv A.txt a2.txt wrong ls: ", ans, s, 1);

	fs.mv("a2.txt", "b2.txt");
	s = fs.ls();
	ans = "a.txt\nb/\nb2.txt\nc.txt\nd/\nf/\ng.txt\nh/";
	if (s != ans)
		errorOut_("mv a2.txt b2.txt wrong ls: ", ans, s, 1);

	}
	{
	// directory
	FileSystem fs("2");
	fs.mv("b", "f2");
	s = fs.ls();
	ans = "a.txt\nc.txt\nd/\ne.txt\nf/\nf2/\ng.txt\nh/";
	if (s != ans)
		errorOut_("mv b f2 wrong ls: ", ans, s, 2);

	fs.mv("f2", "g2");
	s = fs.ls();
	ans = "a.txt\nc.txt\nd/\ne.txt\nf/\ng.txt\ng2/\nh/";
	if (s != ans)
		errorOut_("mv f2 g2 wrong ls: ", ans, s, 2);

	fs.mv("g2", "i");
	s = fs.ls();
	ans = "a.txt\nc.txt\nd/\ne.txt\nf/\ng.txt\nh/\ni/";
	if (s != ans)
		errorOut_("mv g2 i wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// mv leaves into subdir
void FileSystemTester::testq() {
	funcname_ = "FileSystemTester::testq";
	string s, ans;
	{

	FileSystem fs("1");
	fs.mv("a.txt", "e");
	s = fs.tree();
	ans = "/\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt\n e/\n  a.txt\n  ee.txt";
	if (s != ans)
		errorOut_("mv a.txt e wrong tree: ", ans, s, 1);

	}
	{

	FileSystem fs("2");
	fs.mv("h", "f");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n c.txt\n d/\n e.txt\n f/\n  h/\n g.txt";
	if (s != ans)
		errorOut_("mv h f wrong tree: ", ans, s, 2);

	}
	passOut_();
}

// move/rename whole subdir
void FileSystemTester::testr() {
	funcname_ = "FileSystemTester::testr";
	string s, ans;
	{

	FileSystem fs("1");
	fs.mv("b", "e");
	s = fs.tree();
	ans = "/\n a.txt\n c.txt\n d.txt\n e/\n  b/\n   bb1/\n    bbb.txt\n   bb2/\n  ee.txt";
	if (s != ans)
		errorOut_("mv b e wrong tree: ", ans, s, 1);

	}
	{

	FileSystem fs("1");
	fs.mv("b", "f");
	s = fs.tree();
	ans = "/\n a.txt\n c.txt\n d.txt\n e/\n  ee.txt\n f/\n  bb1/\n   bbb.txt\n  bb2/";
	if (s != ans)
		errorOut_("mv b f wrong tree: ", ans, s, 2);

	}
	passOut_();
}

// move to parent
void FileSystemTester::tests() {
	funcname_ = "FileSystemTester::tests";
	string s, ans;
	{
	// file
	FileSystem fs("1");
	fs.cd("e");
	fs.mv("ee.txt", "..");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt\n e/\n ee.txt";
	if (s != ans)
		errorOut_("mv ee.txt .. wrong tree output: ", ans, s, 1);

	}
	{
	// whole subdir
	FileSystem fs("1");
	fs.cd("b");
	fs.mv("bb1", "..");
	fs.cd("..");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb2/\n bb1/\n  bbb.txt\n c.txt\n d.txt\n e/\n  ee.txt";
	if (s != ans)
		errorOut_("mv bb1 .. wrong tree output: ", ans, s, 2);

	}
	passOut_();
}

// mv error msg
void FileSystemTester::testt() {
	funcname_ = "FileSystemTester::testt";
	string s, ans;
	{

	FileSystem fs("1");

	s = fs.mv("f", "e");
	ans = "source does not exist";
	if (s != ans)
		errorOut_("mv f e wrong error message: ", ans, s, 1);

	s = fs.mv("c.txt", "c.txt");
	ans = "source and destination are the same";
	if (s != ans)
		errorOut_("mv c.txt c.txt wrong error message: ", ans, s, 1);

	s = fs.mv("a.txt", "..");
	ans = "invalid path";
	if (s != ans)
		errorOut_("mv a.txt .. wrong error message: ", ans, s, 1);

	s = fs.ls();
	ans = "a.txt\nb/\nc.txt\nd.txt\ne/";
	if (s != ans)
		errorOut_("after invalid mv wrong ls: ", ans, s, 2);

	}
	{

	// normal operation
	FileSystem fs("1");
	s = fs.mv("c.txt", "f.txt");
	ans = "";
	if (s != ans)
		errorOut_("after valid mv wrong return string: ", ans, s, 2);

	}
	passOut_();
}

// mv err msg 2
void FileSystemTester::testu() {
	funcname_ = "FileSystemTester::testu";
	{

	FileSystem fs("1");
	string s, ans;

	fs.touch("ee.txt");
	s = fs.mv("ee.txt", "e");
	ans = "destination already has file/directory of same name";
	if (s != ans)
		errorOut_("mv ee.txt e wrong error message: ", ans, s, 1);

	fs.mkdir("bb1");
	fs.cd("b");
	s = fs.mv("bb1", "..");
	if (s != ans)
		errorOut_("mv bb1 .. wrong error message: ", ans, s, 1);

	fs.cd("..");
	s = fs.mv("c.txt", "d.txt");
	ans = "destination already has file of same name";
	if (s != ans)
		errorOut_("mv c.txt d.txt wrong error message: ", ans, s, 1);

	s = fs.mv("e", "d.txt");
	ans = "source is a directory but destination is an existing file";
	if (s != ans)
		errorOut_("mv e d.txt wrong error message: ", ans, s, 2);

	s = fs.ls();
	ans = "a.txt\nb/\nbb1/\nc.txt\nd.txt\ne/\nee.txt";
	if (s != ans)
		errorOut_("after invalid operation wrong ls: ", ans, s, 2);

	}
	passOut_();
}

// hidden
void FileSystemTester::testv() {
	funcname_ = "FileSystemTester::testv";
	string s, ans;
	{

	}

	passOut_();
}

void FileSystemTester::testw() {
	funcname_ = "FileSystemTester::testw";
	string s, ans;
	{

	}

	passOut_();
}

void FileSystemTester::testx() {
	funcname_ = "FileSystemTester::testx";
	string s, ans;
	{

	}
	passOut_();
}

void FileSystemTester::testy() {
	funcname_ = "FileSystemTester::testy";
	string s, ans, ans2;
	{

	}
	passOut_();
}

// Well done for reading to this point!
// Have you noticed that what you are asked to implement is a very limited
// version of what Linux commands actually do? In reality, all those commands
// accept absolute paths or relative paths as arguments.
// In case you want to challenge yourself, consider how you can implement
// the functions to handle those more general arguments.
// The following test case shows some examples for illustration purposes only.
// A maximum of 5 bonus marks may be awarded if you attempt it (but the total
// mark cannot go above 100). The marks are given on a discretionary basis
// and NOT based on the test case alone, as they are definitely NOT exhaustive.
// A lot of crazy situations can arise. Good luck...
//
// This test case will not be used by default.
// If you attempt this, please leave a note somewhere so I notice it.
void FileSystemTester::testz() {
	funcname_ = "FileSystemTester::testz";
	string s, ans;
	{

	FileSystem fs("1");
	fs.cd("b/bb1");
	s = fs.pwd();
	ans = "/b/bb1";
	if (s != ans)
		errorOut_("wrong cd b/bb1: ", ans, s, 1);

	fs.cd("../../e");
	s = fs.pwd();
	ans = "/e";
	if (s != ans)
		errorOut_("wrong cd ../../e: ", ans, s, 1);

	s = fs.cd("/B/bb1");
	ans = "invalid path"; // or some other error message
	if (s != ans)
		errorOut_("cd /B/bb1 error message: ", ans, s, 1);

	}
	{

	FileSystem fs("1");
	fs.cd("b");
	fs.touch("/e/ee2.txt");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt\n e/\n  ee.txt\n  ee2.txt";
	if (s != ans)
		errorOut_("wrong touch /e/ee2.txt: ", ans, s, 2);

	fs.cd("e");
	fs.mkdir("../b/bb3");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n  bb3/\n c.txt\n d.txt\n e/\n  ee.txt\n  ee2.txt";
	if (s != ans)
		errorOut_("wrong mkdir ../b/bb3: ", ans, s, 2);

	s = fs.mkdir("/b/bb3");
	ans = "file/directory already exists";
	if (s != ans)
		errorOut_("duplicate mkdir wrong error message: ", ans, s, 2);

	s = fs.touch("b/bb4/bbb.txt");
	ans = "invalid path"; // or some other error message
	if (s != ans)
		errorOut_("touch b/bb4/bbb.txt error message: ", ans, s, 2);

	}
	{

	FileSystem fs("1");
	fs.cd("b");
	fs.rm("/e/ee.txt");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt\n e/";
	if (s != ans)
		errorOut_("wrong rm /e/ee.txt: ", ans, s, 3);

	fs.cd("b/bb1");
	fs.rmdir("../../e");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n c.txt\n d.txt";
	if (s != ans)
		errorOut_("wrong rmdir ../../e: ", ans, s, 3);

	FileSystem fs0;
	s = fs0.rmdir("/");
	ans = "cannot remove root directory"; // or some other error message
	if (s != ans)
		errorOut_("rmdir / error message: ", ans, s, 3);

	}
	{

	FileSystem fs("1");
	fs.cd("b");
	fs.mv("../e/ee.txt", "bb2");
	fs.cd("/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb2/\n   ee.txt\n c.txt\n d.txt\n e/";
	if (s != ans)
		errorOut_("wrong mv ../e/ee.txt bb2: ", ans, s, 4);

	fs.mv("/b/bb2", "b/bb3");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb1/\n   bbb.txt\n  bb3/\n   ee.txt\n c.txt\n d.txt\n e/";
	if (s != ans)
		errorOut_("wrong mv /b/bb2 b/bb3: ", ans, s, 4);

	fs.mv("/b/bb1", "/");
	s = fs.tree();
	ans = "/\n a.txt\n b/\n  bb3/\n   ee.txt\n bb1/\n  bbb.txt\n c.txt\n d.txt\n e/";
	if (s != ans)
		errorOut_("wrong mv /b/bb1 /: ", ans, s, 4);

	}

	// There are also new error cases that now appears, e.g. you cannot move a
	// directory inside its own subdirectory, or the source of mv cannot be
	// an ancestor of the current directory. You are not required to reproduce
	// the exact same error messages.
	{

	FileSystem fs("1");
	s = fs.mv("b", "b/bb1");
	ans = "cannot move source into a subdirectory of itself"; // or some other error message
	if (s != ans)
		errorOut_("mv b b/bb1 error message: ", ans, s, 5);

	fs.cd("b/bb1");
	s = fs.mv("..", "B");
	ans = "cannot move or rename while current directory is inside source"; // or some other error message
	if (s != ans)
		errorOut_("mv .. B error message: ", ans, s, 5);

	fs.cd("/");
	s = fs.mv("/", "root");
	ans = "cannot move or rename root directory"; // or some other error message
	if (s != ans)
		errorOut_("mv / root error message: ", ans, s, 5);
	fs.cd("b");
	s = fs.mv("..", "root");
	ans = "cannot move or rename root directory"; // or some other error message
	if (s != ans)
		errorOut_("mv .. root error message: ", ans, s, 5);

	}

	passOut_();
}

void FileSystemTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void FileSystemTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void FileSystemTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void FileSystemTester::errorOut_(const string& errMsg, const string& expResult, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	cerr << "Expected output:\n" << expResult << endl;
	cerr << "Your output:\n" << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void FileSystemTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}
