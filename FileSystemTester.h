#ifndef FILESYSTEMTESTER_H_
#define FILESYSTEMTESTER_H_
#include <string>

class FileSystemTester {
public:
	FileSystemTester();

	// ctor, pwd
	void testa();
	void testb();

	// cd, pwd
	void testc();
	void testd();
	void teste();

	// tree
	void testf();
	void testg();

	// touch, mkdir
	void testh();
	void testi();
	void testj();

	// rm, rmdir
	void testk();
	void testl();
	void testm();
	void testn();

	// mv
	void testo();
	void testp();
	void testq();
	void testr();
	void tests();
	void testt();
	void testu();

	// hidden
	void testv();
	void testw();
	void testx();
	void testy();

	// unused
	void testz();

private:

	// four overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& expRes, const std::string& errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* FILESYSTEMTESTER_H_ */
