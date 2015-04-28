/*
 * Tester.h
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
using namespace std;

#include "test.h"

namespace tester {

void assert(const bool&);
template<class T>
void assert_ostream(const T &o, const char * str) {
	stringstream ss;
	ss << o;
	assert(ss.str().compare(str) == 0);
}

class Tester {
friend ostream & operator<<(ostream&, const Tester&);
private:
	bool exit, msg;
	unsigned int level;
	char c_level;
	string nombre;
	vector<Test> tests;
	vector<Tester> testers;
	string separator;
	void printInTree(const char*&)const;
	void printLevel()const;
	void printTestLevel()const;
	void printSeparation(const int&)const;
	void printHead()const;

public:
	Tester(const char*);
	void add(const Test&a) {
		tests.push_back(a);
	}
	void add(Tester&a);
	void runAssertions();
	void runOutput();
	void run(){runAssertions();runOutput();}
	void dbgMsg(const bool&);
	void setExit(const bool&v){
		exit = v;
	}
	void setSeparator(const char* c) {
		separator = c;
	}
	~Tester();
};
}

#endif /* TESTER_H_ */
