#ifndef TEST_H_
#define TEST_H_

#include <iostream>
using namespace std;


namespace tester {
class Test {
	friend class Tester;

private:
	string name, expected, result;
	bool msg;
	void (*test)();
	bool pased;
public:
	Test(void (*f)(), const char* n, const char* sol);
	void dbgMsg(const bool&v) {
		msg = v;
	}
	void run();
	~Test() {
	}
	friend ostream & operator<<(ostream&, const Test&);
};
}
#endif
