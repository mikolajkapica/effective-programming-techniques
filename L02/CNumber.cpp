#include "CNumber.h"
#include <iostream>
#include <string>

CNumber intToCNumber(int iNewVal) {
	int numToFindLength = iNewVal;
	int i_length = 0;
	while (numToFindLength > 0) {
		numToFindLength /= 10;
		i_length++;
	}
	int *pi_number = new int[i_length];
	for (int i = 0; i < i_length; i++) {
		pi_number[i] = iNewVal % 10;
		iNewVal /= 10;
	}
	return CNumber(i_length, pi_number);
}

void CNumber::operator=(const CNumber &pcOther) { 
	//this->pi_number = pcOther.pi_number; 
	// tak byæ nie mo¿e, bo gdy usuniemy pcOther, to usuniemy te¿ this->pi_number
	// a nie mozna dealokowaæ tego co ju¿ dealokowaliœmy, zatem:

	this->pi_number = new int[pcOther.i_length];
	std::copy(pcOther.pi_number, pcOther.pi_number + pcOther.i_length, this->pi_number);
	this->i_length = pcOther.i_length; 
}

void CNumber::operator=(const int iValue) { 
	*this = intToCNumber(iValue);
}

CNumber CNumber::operator+(CNumber& pcNewVal) {
	return CNumber();
}

CNumber CNumber::operator*(CNumber& pcNewVal) {
	return CNumber();
}

CNumber CNumber::operator-(CNumber& pcNewVal) {
	return CNumber();
}

CNumber CNumber::operator/(CNumber& pcNewVal) {
	return CNumber();
}

CNumber CNumber::operator+(int iNewVal) {
	return *this + intToCNumber(iNewVal);
}

CNumber CNumber::operator*(int iNewVal) {
	return *this * intToCNumber(iNewVal);
}

CNumber CNumber::operator-(int iNewVal) {
	return *this - intToCNumber(iNewVal);
}

CNumber CNumber::operator/(int iNewVal) {
	return *this / intToCNumber(iNewVal);
}

std::string CNumber::sToStr() {
	if (this->i_length == 0) { return "0"; }	
	std::string s_result = "";
	for (int i = this->i_length - 1; i >= 0; i--) {
		s_result += std::to_string(this->pi_number[i]);
	}
	return s_result;
}
