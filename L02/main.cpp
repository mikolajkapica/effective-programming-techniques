#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CNumber.h"

void testAddition(int a, int b) {
	CNumber c_a;
	CNumber c_b;
	c_a = a;
	c_b = b;
	std::cout << c_a.toString() << " + " << c_b.toString() << " = " << (c_a + c_b).toString() << std::endl;
}

void testMultiplication(int a, int b) {
	CNumber c_a;
	CNumber c_b;
	c_a = a;
	c_b = b;
	std::cout << c_a.toString() << " * " << c_b.toString() << " = " << (c_a * c_b).toString() << std::endl;
}

void testSubtraction(int a, int b) {
	CNumber c_a;
	CNumber c_b;
	c_a = a;
	c_b = b;
	std::cout << c_a.toString() << " - " << c_b.toString() << " = " << (c_a - c_b).toString() << std::endl;
}

void testDivision(int a, int b) {
	CNumber c_a;
	CNumber c_b;
	c_a = a;
	c_b = b;
	std::cout << c_a.toString() << " / " << c_b.toString() << " = " << (c_a / c_b).toString() << std::endl;
}

int main()
{
	//testAddition(-1,1);
	//testMultiplication(-45, -5);
	//testSubtraction(1, 2);
	testDivision(100, 2);
}

