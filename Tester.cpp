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

unsigned int Tester::separation=25;
char Tester::separator='=';

static bool isFile(const char *fileName) {
	ifstream infile(fileName);
	return infile.good();
}

void assert(bool expr) {
	if (!expr)
		throw "Assertion true failed";
}
void assertf(bool expr) {
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

void Tester::printSeparation() {
	for (unsigned int i = 0; i < separation; i++)
		cout << separator;
	cout << endl;
}

void Tester::run() {
	printSeparation();
	cout << "Running Tester " << nombre << endl;
	printSeparation();
	for (unsigned int i = 0; i < tests.size(); i++) {
		tests[i].run();
		cout << tests[i] << endl;
	}
	separation-=2;
	for (unsigned int i = 0; i < testers.size(); i++) {
		testers[i].run();
	}
	separation+=2;
}

void Tester::dbgMsg(const bool& v) {
	for (unsigned int i = 0; i < tests.size(); i++)
		tests[i].dbgMsg(v);
}
}

tester::Tester::Tester(const char*a) {
	nombre = a;
	exit = true;
}

tester::Tester::~Tester() {
}
