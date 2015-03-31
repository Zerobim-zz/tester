/*
 * Tester_test.cpp
 *
 *  Created on: 27/3/2015
 *      Author: daniel
 */

#include "Test.h"
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
		Test t1(prueba, "test1", "./testing_the_tester/test1");
		Test t2(prueba, "test2", "line1\nLine2\nline3\n");
		t1.run();
		t2.run();
		//cout << t1 << endl << t2 << endl;

		Tester bigGroup("The Group");
		Tester smallGroup("little Group");
		Tester group("group1"),gr2("grupete");

		group.add(t1);
		group.add(t2);
		group.setSeparator("_");

		gr2.add(t1);
		gr2.add(t2);
		gr2.setSeparator("_");

		smallGroup.add(gr2);
		smallGroup.add(group);
		smallGroup.setSeparator("\\\\//");

		bigGroup.add(smallGroup);
		bigGroup.add(smallGroup);
		//bigGroup.dbgMsg(true);
		bigGroup.run();

		cout<<bigGroup<<endl;
		cout << "OK" << endl;

	} catch (const char*& c) {
		cerr << c;
	}

	return 0;
}
