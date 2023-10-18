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
	int iLengthLeftA = this->i_length;
	int iLengthLeftB = pcNewVal.i_length;

	int iLengthResult = iLengthLeftA > iLengthLeftB ? 1 + iLengthLeftA : 1 + iLengthLeftB;
	int* pi_result = new int[iLengthResult];
	int carry = 0;

	for (int i = iLengthResult - 1; i >= 0; i--) {
		int a = iLengthLeftA > 0 ? this->pi_number[iLengthLeftA - 1] : 0;
		int b = iLengthLeftB > 0 ? pcNewVal.pi_number[iLengthLeftB - 1] : 0;
		iLengthLeftA--;
		iLengthLeftB--;
		int sum = a + b + carry;
		carry = sum / 10;
		pi_result[i] = sum % 10;
	}

	if (pi_result[0] == 0) {
		int* pi_result_without_first = new int[iLengthResult - 1];
		for (int i = 0; i < iLengthResult - 1; i++) {
			pi_result_without_first[i] = pi_result[i + 1];
		}
		delete[] pi_result;
		return CNumber(iLengthResult - 1, pi_result_without_first);
	}
	return CNumber(iLengthResult, pi_result);
}

CNumber CNumber::operator*(CNumber& pcNewVal) {
	return CNumber();
}

void print_table(int* table, int length) {
	for (int i = 0; i < length; i++) {
		std::cout << table[i];
	}
	std::cout << std::endl;
}

int* flip_pi_table_to_10s_complement(int* table, int length) {
	int max_decimal_digit = 9;
	for (int i = 0; i < length; i++) {
		table[i] = max_decimal_digit - table[i];
	}
	table[length - 1] += 1;
	return table;
}

CNumber CNumber::operator-(CNumber& pcNewVal) {
	int* pi_newVal10sComplement = flip_pi_table_to_10s_complement(pcNewVal.pi_number, pcNewVal.i_length);
	print_table(this->pi_number, this->i_length);
	print_table(pi_newVal10sComplement, pcNewVal.i_length);

	int iLengthLeftA = this->i_length;
	int iLengthLeftB = pcNewVal.i_length;

	int iLengthResult = iLengthLeftA > iLengthLeftB ? iLengthLeftA : iLengthLeftB;
	int* pi_result = new int[iLengthResult];
	int carry = 0;

	for (int i = iLengthResult - 1; i >= 0; i--) {
		int a = iLengthLeftA > 0 ? this->pi_number[iLengthLeftA - 1] : 0;
		int b = iLengthLeftB > 0 ? pi_newVal10sComplement[iLengthLeftB - 1] : 0;
		iLengthLeftA--;
		iLengthLeftB--;
		int sum = a + b + carry;
		carry = sum / 10;
		pi_result[i] = sum % 10;
		std::cout << "i: " << i << " a: " << a << " b: " << b << " sum: " << sum << " carry: " << carry << std::endl;
	}

	if (carry == 0) {
		std::cout << "here!" << std::endl;
		return CNumber(iLengthResult, flip_pi_table_to_10s_complement(pi_result, iLengthResult));
	}

	return CNumber(iLengthResult, pi_result);
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
	for (int i = 0; i < this->i_length; i++) {
		s_result += std::to_string(this->pi_number[i]);
	}
	return s_result;
}
