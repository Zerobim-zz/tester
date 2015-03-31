#ifndef TESTER_H_
#define TESTER_H_

#include <iostream>
using namespace std;

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

#endif
