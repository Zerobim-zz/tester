/*
 * Tester.h
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <iostream>
#include <vector>
using namespace std;

namespace tester {

void assert(const bool&);
void assertf(const bool&);

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
	void add(Tester&a) {
		a.level=level+1;
		testers.push_back(a);
	}
	void run();
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
