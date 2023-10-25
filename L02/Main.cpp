#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CNumber.h"

bool testAddition(int a, int b, int c) {
	CNumber c_a;
	CNumber c_b;
	CNumber c_c;
	c_a = a;
	c_b = b;
	c_c = c;
	bool b_result = c_a + c_b == c_c;
	if (!b_result) {
		std::cout << "testAddition failed: " << a << " + " << b << " != " << c << std::endl;
		std::cout << "c_a: " << c_a.toString() << std::endl;
		std::cout << "c_b: " << c_b.toString() << std::endl;
		std::cout << "c_c: " << c_c.toString() << std::endl;
		std::cout << "c_a + c_b: " << (c_a + c_b).toString() << std::endl;
	}
	return b_result;
}

bool testMultiplication(int a, int b, int c) {
	CNumber c_a;
	CNumber c_b;
	CNumber c_c;
	c_a = a;
	c_b = b;
	c_c = c;
	bool b_result = c_a * c_b == c_c;
	if (!b_result) {
		std::cout << "testMultiplication failed: " << a << " * " << b << " != " << c << std::endl;
		std::cout << "c_a: " << c_a.toString() << std::endl;
		std::cout << "c_b: " << c_b.toString() << std::endl;
		std::cout << "c_c: " << c_c.toString() << std::endl;
		std::cout << "c_a * c_b: " << (c_a * c_b).toString() << std::endl;
	}
	return b_result;
}

bool testSubtraction(int a, int b, int c) {
	CNumber c_a;
	CNumber c_b;
	CNumber c_c;
	c_a = a;
	c_b = b;
	c_c = c;
	bool b_result = c_a - c_b == c_c;
	if (!b_result) {
		std::cout << "testSubtraction failed: " << a << " - " << b << " != " << c << std::endl;
		std::cout << "c_a: " << c_a.toString() << std::endl;
		std::cout << "c_b: " << c_b.toString() << std::endl;
		std::cout << "c_c: " << c_c.toString() << std::endl;
		std::cout << "c_a - c_b: " << (c_a - c_b).toString() << std::endl;
	}
	return b_result;
}

bool testDivision(int a, int b, int c) {
	CNumber c_a;
	CNumber c_b;
	CNumber c_c;
	c_a = a;
	c_b = b;
	c_c = c;
	bool b_result = c_a / c_b == c_c;
	if (!b_result) {
		std::cout << "testDivision failed: " << a << " / " << b << " != " << c << std::endl;
		std::cout << "c_a: " << c_a.toString() << std::endl;
		std::cout << "c_b: " << c_b.toString() << std::endl;
		std::cout << "c_c: " << c_c.toString() << std::endl;
		std::cout << "c_a / c_b: " << (c_a / c_b).toString() << std::endl;
	}
	return b_result;
}

int main() {
	bool tests[40] = {
		testAddition(253, -235, 18),
		testAddition(0, -634, -634),
		testAddition(0, 4, 4),
		testAddition(0, 0, 0),
		testAddition(-125, -634, -759),
		testAddition(125, 634, 759),
		testAddition(125, 0, 125),
		testAddition(125, -125, 0),
		testAddition(125, -634, -509),
		testAddition(125, 634, 759),

		testMultiplication(253, -235, -59455),
		testMultiplication(0, -634, 0),
		testMultiplication(0, 0, 0),
		testMultiplication(-125, -634, 79250),
		testMultiplication(125, 634, 79250),
		testMultiplication(125, 0, 0),
		testMultiplication(125, -125, -15625),
		testMultiplication(125, -634, -79250),
		testMultiplication(125, 634, 79250),
		testMultiplication(12335, 2365, 29172275),

		testSubtraction(253, -235, 488),
		testSubtraction(0, -634, 634),
		testSubtraction(0, 0, 0),
		testSubtraction(-125, -634, 509),
		testSubtraction(125, 634, -509),
		testSubtraction(125, 0, 125),
		testSubtraction(125, -125, 250),
		testSubtraction(125, -634, 759),
		testSubtraction(125, 634, -509),
		testSubtraction(12222235, 23562362367, -2075303652),

		testDivision(253, -235, -1),
		testDivision(0, -634, 0),
		testDivision(0, 12, 0),
		testDivision(-125, -634, 0),
		testDivision(125, 634, 0),
		testDivision(253, 125, 2),
		testDivision(235235, 236, 996),
		testDivision(125, -125, -1),
		testDivision(125, -634, 0),
		testDivision(125, 634, 0),
	};

	int passed = 0;
	for (int i = 0; i < 40; i++) {
		if (tests[i]) {
			passed++;
			std::cout << "\033[32m";
			std::cout << "#";
		} else {
			std::cout << "\033[31m";
			std::cout << "#";
		}
	}
	std::cout << "\033[0m" << std::endl;
	std::cout << "Passed " << passed << " out of 40 tests" << std::endl;

}
