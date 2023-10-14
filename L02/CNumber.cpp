#include "CNumber.h"
#include <iostream>

bool debug = true;

void CNumber::operator=(const CNumber &pcOther) 
{ 
	this->pi_number = pcOther.pi_number; 
	this->i_length = pcOther.i_length; 
}//void CTable::operator=(CTable &pcOther)

CNumber CNumber::operator+(CNumber& pcNewVal)
{
	CNumber c_result;
	if (this->i_length > pcNewVal.i_length) {
		c_result.i_length = this->i_length;
		c_result.pi_number = new int[c_result.i_length];

		int i = 0;
		for (; i < this->i_length - pcNewVal.i_length; i++) {
			c_result.pi_number[i] = this->pi_number[i];
		}
		for (int j = 0; i < c_result.i_length; i++, j++) {
			c_result.pi_number[i] = this->pi_number[i] + pcNewVal.pi_number[j];
		}
	} 
	else {
		c_result.i_length = pcNewVal.i_length;
		c_result.pi_number = new int[c_result.i_length];

		int i = 0;
		for (; i < pcNewVal.i_length - this->i_length; i++) {
			c_result.pi_number[i] = pcNewVal.pi_number[i];
		}
		for (int j = 0; i < c_result.i_length; i++, j++) {
			c_result.pi_number[i] = this->pi_number[i] + pcNewVal.pi_number[j];
		}
	}

	if (debug) c_result.print();

	return c_result;
}


CNumber CNumber::operator+(int iNewVal) {
	CNumber newCNumber = CNumber();
	int numToFindLength = iNewVal;
	int i_length = 0;
	while (numToFindLength > 0) {
		numToFindLength /= 10;
		i_length++;
	}
	newCNumber.i_length = i_length;
	newCNumber.pi_number = new int[i_length];
	for (int i = 0; i < i_length; i++) {
		newCNumber.pi_number[i] = iNewVal % 10;
		iNewVal /= 10;
	}

	return *this + newCNumber;
}

void CNumber::print() {
	// newline
	std::cout << std::endl;
	for (int i = 0; i < this->i_length; i++) {
		std::cout << this->pi_number[i];
	}
}
