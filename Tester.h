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


static bool exit = true;

void assert(bool);
void assertf(bool);
void autoExit(bool);

class Test {
private:
	string name, expected, result;
	bool msg = true;
	void (*test)();
	bool pased;
public:
	Test(void (*f)(), const char* n, const char* sol);
	void run() ;
	~Test();
	friend ostream & operator<<(ostream& os, const Test&);
};

class Tester {
public:
	Tester();
	~Tester();
};
}

#endif /* TESTER_H_ */
