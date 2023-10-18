#include "CNumber.h"
#include <iostream>
#include <string>

CNumber intToCNumber(int iNewVal) {
	// find length of number
	int sign = iNewVal < 0 ? -1 : 1;
	int numToFindLength = sign * iNewVal;
	int i_length = 1; // 1 cell for sign
	while (numToFindLength > 0) {
		numToFindLength /= 10;
		i_length++;
	}

	// convert int to 10s complement table
	int *pi_number = new int[i_length];
	if (sign == -1) {
		iNewVal = -iNewVal;
		for (int i = i_length - 1; i >= 0; i--) {
			pi_number[i] = 9 - (iNewVal % 10);
			iNewVal /= 10;
		}
		pi_number[i_length - 1]++;
	} else {
		for (int i = i_length - 1; i >= 0; i--) {
			pi_number[i] = iNewVal % 10;
			iNewVal /= 10;
		}
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
	this->name = pcOther.name;
}

void CNumber::operator=(const int iValue) { 
	*this = intToCNumber(iValue);
}

CNumber CNumber::operator+(CNumber& pcNewVal) {
	int iLengthLeftA = this->i_length;
	int iLengthLeftB = pcNewVal.i_length;
	
	int max_decimal_digit = 9;

	int aSign = this->pi_number[0] == max_decimal_digit;    // negative then 1
	int bSign = pcNewVal.pi_number[0] == max_decimal_digit; // negative then 1

	int iLengthResult = iLengthLeftA > iLengthLeftB ?  iLengthLeftA : iLengthLeftB;
	int* pi_result = new int[iLengthResult];
	int carry = 0;

	for (int i = iLengthResult - 1; i >= 0; i--) {
		int a = iLengthLeftA > 0 ? this->pi_number[iLengthLeftA - 1] : max_decimal_digit * aSign;
		int b = iLengthLeftB > 0 ? pcNewVal.pi_number[iLengthLeftB - 1] : max_decimal_digit * bSign;
		iLengthLeftA--;
		iLengthLeftB--;
		int sum = a + b + carry;
		carry = sum / 10;
		pi_result[i] = sum % 10;
	}

	return CNumber(iLengthResult, pi_result);
}

CNumber CNumber::operator*(CNumber& pcNewVal) {
	int max_length = this->i_length > pcNewVal.i_length ? this->i_length : pcNewVal.i_length;
	int iLengthResult = this->i_length + pcNewVal.i_length - 1;

	int* pi_result = new int[iLengthResult];
	for (int i = 0; i < iLengthResult; i++) {
		pi_result[i] = 0;
	}

	int max_decimal_digit = 9;
	int aSign = this->pi_number[0] == 9;    // negative then 1
	int bSign = pcNewVal.pi_number[0] == 9; // negative then 1

	int aLength = this->i_length;
	int bLength = pcNewVal.i_length;

	for (int i = max_length; i >= 0; i--) {
		int carry = 0;
		int a = aLength > 0 ? this->pi_number[aLength - 1] : max_decimal_digit * aSign;
		aLength--;
		bLength = pcNewVal.i_length;
		for (int j = max_length; j > 0; j--) {
			if (i + j - max_length > 0) continue;
			int b = bLength > 0 ? pcNewVal.pi_number[bLength - 1] : max_decimal_digit * bSign;
			bLength--;
			int product = a * b + carry;
			carry = (product + pi_result[i - (max_length - j - 1)]) / 10;
			pi_result[i - (max_length - j - 1)] += product;
			pi_result[i - (max_length - j - 1)] %= 10;
		}
	}

	if (aSign + bSign == 1) {
		for (int i = 0; i < iLengthResult; i++) {
			pi_result[i] = max_decimal_digit - pi_result[i];
		}
		pi_result[iLengthResult]++;
	}
	return CNumber(iLengthResult, pi_result);
}

CNumber CNumber::operator-(CNumber& pcNewVal) {
	return *this + (-pcNewVal);
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
	return *this + intToCNumber(-iNewVal);
}

CNumber CNumber::operator/(int iNewVal) {
	return *this / intToCNumber(iNewVal);
}

CNumber CNumber::operator-() {
	int max_decimal_digit = 9;
	int* new_pi_number = new int[this->i_length];
	for (int i = 0; i < this->i_length; i++) {
		new_pi_number[i] = max_decimal_digit - this->pi_number[i];
	}
	new_pi_number[this->i_length - 1] += 1;
	return CNumber(this->i_length, new_pi_number);
}

std::string CNumber::toString() {
	int negative_number_sign = 9;
	if (this->pi_number[0] == negative_number_sign) {
		return "-" + (- (*this)).toString();
	}
	std::string out = "";
	int prefix_zeros = 0;
	for (int i = 0; this->pi_number[i] == 0; i++) {
		prefix_zeros++;
	}
	for (int i = prefix_zeros; i < this->i_length; i++) {
		out += std::to_string(this->pi_number[i]);
	}
	return out;
}
