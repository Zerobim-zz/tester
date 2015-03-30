/*
 * Tester.h
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <iostream>
using namespace std;
namespace tester {

void assert(bool);
void assertf(bool);

class Test {
private:
	string name, expected, result;
	bool msg;
	void (*test)();
	bool pased;
public:
	Test(void (*f)(), const char* n, const char* sol);
	void dbgMsg(const bool&v){msg=v;}
	void run() ;
	~Test(){}
	friend ostream & operator<<(ostream& os, const Test&);
};

class Tester {
private:
	bool exit;
public:
	Tester();
	void setExit(const bool&v){exit=v;}
	~Tester();
};
}

#endif /* TESTER_H_ */
