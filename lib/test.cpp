#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "../include/test.h"
using namespace std;

namespace tester {

static bool isFile(const char *fileName) {
	ifstream infile(fileName);
	return infile.good();
}

Test::Test(void (*f)(), const char* n, const char* sol) {
	test = f;
	name = n;
	msg = false;
	pased = false;
	if (isFile(sol)) {
		expected = "";
		ifstream s(sol);
		string temp;
		bool nl = false;
		while (getline(s, temp)) {
			bool aux = false;
			if (temp.find("\r") != string::npos) {
				replace(temp.begin(), temp.end(), '\r', '\n');
				aux = true;
			}
			expected += temp;
			if (!aux && !s.eof())
				expected += "\n";
		}
	} else
		expected = sol;
}

void Test::runAssertions() {
	if (msg)
		cout << "Test " << name << "Assertions:";
	// Redirect cout.
	streambuf* oldCoutStreamBuf = cout.rdbuf();
	stringstream strCout;
	cout.rdbuf(strCout.rdbuf());
	try {
		test();
	} catch (const char*& c) {
		// Restore old cout.
		cout.rdbuf(oldCoutStreamBuf);
		if (msg) {
			cerr << c << " at " << name << endl;
			cout << "NOT Passed";
		}
		return;
	}
	// Restore old cout.
	cout.rdbuf(oldCoutStreamBuf);
	if (msg)
		cout << "Passed";
}
void Test::runOutput() {
	if (msg)
		cout << "Test " << name << "Output:";
	// Redirect cout.
	streambuf* oldCoutStreamBuf = cout.rdbuf();
	stringstream strCout;
	cout.rdbuf(strCout.rdbuf());
	try {
		test();
	} catch (const char*& c) {
		if (msg)
			cerr << c << " at " << name << endl;
	}
	// Restore old cout.
	cout.rdbuf(oldCoutStreamBuf);
	result = strCout.str();
	pased = result.compare(expected) == 0;
	if (pased && msg)
		cout << "Passed";
	else if (msg)
		cout << "NOT Passed";

}

ostream & operator<<(ostream & os, const Test& t) {

	os << t.name << ":" << (t.pased ? "passed" : "not passed");
	if (!t.pased && t.msg) {
		os << "\nExpected:\n[" << t.expected << "]" << "\nReceived:\n["
				<< t.result << "]";
	}
	return os;
}
}
