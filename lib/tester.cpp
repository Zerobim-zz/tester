/*
 * Tester.cpp
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#include <iostream>
#include <cstring>

#include "tester.h"
using namespace std;

namespace tester {

void assert(const bool& expr) {
	if (!expr)
		throw "Assertion true failed";
}

void Tester::printLevel() const {
	for (unsigned int i = 0; i < level; i++)
		cout << c_level;
}

void Tester::printTestLevel() const {
	printLevel();
	cout << c_level;
}

void Tester::printInTree(const char*& str) const {
	printLevel();
	cout << str;
}

void Tester::printHead() const {
	string temp("Running Tester ");
	temp += nombre;
	//printSeparation(temp.size());

	printLevel();
	cout << temp << endl;

	//printSeparation(temp.size());
}
void Tester::add(Tester&a) {
	a.level = level + 1;
	for (int i = 0; i < a.testers.size(); i++)
		++a.testers[i].level;
	testers.push_back(a);
}

void Tester::runOutput() {
	if (msg)
		printHead();
	for (unsigned int i = 0; i < tests.size(); i++) {
		if (msg)
			printTestLevel();
		tests[i].runOutput();
	}
	for (unsigned int i = 0; i < testers.size(); i++)
		testers[i].runOutput();

}
void Tester::runAssertions() {
	if (msg)
		printHead();
	for (unsigned int i = 0; i < tests.size(); i++) {
		if (msg)
			printTestLevel();
		tests[i].runAssertions();
	}

	for (unsigned int i = 0; i < testers.size(); i++)
		testers[i].runAssertions();

}

void Tester::dbgMsg(const bool& v) {
	msg = v;
	for (unsigned int i = 0; i < tests.size(); i++)
		tests[i].dbgMsg(v);
	for (unsigned int i = 0; i < testers.size(); i++)
		testers[i].dbgMsg(v);
}

tester::Tester::Tester(const char*a) {
	level = 0;
	c_level = '|';
	separator = '=';
	msg = false;
	nombre = a;
	exit = true;
}

ostream& operator<<(ostream& os, const Tester& t) {
	// Redirect cout.
	streambuf* oldCoutStreamBuf = cout.rdbuf();
	cout.rdbuf(os.rdbuf());

	t.printLevel();
	cout << "Results of " << t.nombre << " :" << endl;

	for (unsigned int i = 0; i < t.tests.size(); i++) {
		t.printTestLevel();
		cout << t.tests[i] << endl;
	}
	for (unsigned int i = 0; i < t.testers.size(); i++) {
		cout << t.testers[i];
	}
	cout.rdbuf(oldCoutStreamBuf);
	return os;
}

tester::Tester::~Tester() {
}
}

