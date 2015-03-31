/*
 * Tester.cpp
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#include "Tester.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

namespace tester {

static bool isFile(const char *fileName) {
	ifstream infile(fileName);
	return infile.good();
}

void assert(const bool& expr) {
	if (!expr)
		throw "Assertion true failed";
}
void assertf(const bool& expr) {
	if (expr)
		throw "Assertion false failed";
}
Test::Test(void (*f)(), const char* n, const char* sol) {
	test = f;
	name = n;
	msg = false;
	pased = false;
	if (isFile(sol)) {
		expected = "";
		ifstream s(sol);
		while (!s.eof()) {
			char c = char(s.get());
			if (c > 0 && c < 126)
				expected += c;
		}
	} else
		expected = sol;
}

void Test::run() {
	// Redirect cout.
	streambuf* oldCoutStreamBuf = cout.rdbuf();
	stringstream strCout;
	cout.rdbuf(strCout.rdbuf());

	try {
		test();
	} catch (const char*& c) {
		// Restore old cout.
		cout.rdbuf(oldCoutStreamBuf);
		result = strCout.str();
		if (msg)
			cerr << c << " at " << name << endl;
		return;
	}
	// Restore old cout.
	cout.rdbuf(oldCoutStreamBuf);
	result = strCout.str();
	pased = result.compare(expected) == 0;
}

ostream & operator<<(ostream & os, const Test& t) {

	os << t.name << ":" << (t.pased ? "passed" : "not passed");
	if (!t.pased && t.msg) {
		os << "\nExpected:\n[" << t.expected << "]" << "\nReceived:\n["
				<< t.result << "]";
	}
	return os;
}

void Tester::printLevel() const {
	for (unsigned int i = 0; i < level; i++)
		cout << c_level;
}

void tester::Tester::printTestLevel() const {
	printLevel();
	cout << c_level;
}

void Tester::printInTree(const char*& str)const{
	printLevel();
	cout<<str;
}



void Tester::printHead() const {
	string temp("Running Tester ");
	temp += nombre;
	printSeparation(temp.size());

	printLevel();
	cout << temp << endl;

	printSeparation(temp.size());
}



void Tester::run() {
	if (msg)
		printHead();
	for (unsigned int i = 0; i < tests.size(); i++) {
		tests[i].run();
		if (msg)
			cout << tests[i] << endl;
	}
	for (unsigned int i = 0; i < testers.size(); i++) {
		testers[i].run();
	}
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

	t.printLevel();
	os << "Results of " << t.nombre << " :" << endl;

	for (unsigned int i = 0; i < t.tests.size(); i++) {
		t.printTestLevel();
		os << t.tests[i] << endl;
	}
	for (unsigned int i = 0; i < t.testers.size(); i++) {
		t.printLevel();
		os << t.testers[i];
	}
	return os;
}

tester::Tester::~Tester() {
}
}

