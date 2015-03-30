/*
 * Tester_test.cpp
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#include "Tester.h"
using namespace tester;

void prueba() {
	assert(true);
	cout << "line1" << endl << "Line2\nline3" << endl;
	assertf(false);
}

int main() {
	try {
		assert(true);
		assertf(false);
		Test t1(prueba, "test1", "./test1");
		t1.dbgMsg(false);
		Test t2(prueba, "test2", "line1\nLine2\nline3\n");
		t2.dbgMsg(false);
		t1.run();
		t2.run();
		cout << t1 << endl << t2 << endl;

		cout << "OK" << endl;

	} catch (const char*& c) {
		cerr << c;
	}

	return 0;
}
