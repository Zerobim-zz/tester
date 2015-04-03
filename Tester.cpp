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
	msg = true;
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
	/*cout << "=========================" << endl << "Running Tests" << endl
	 << "=========================" << endl;*/
	os << t.name << ":" << (t.pased ? "passed" : "not passed");
	if (!t.pased && t.msg) {
		os << "\nExpected:\n[" << t.expected << "]" << "\nReceived:\n["
				<< t.result << "]";
	}
	return os;
}
}
