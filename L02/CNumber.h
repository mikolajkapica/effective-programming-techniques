#pragma once
#include <iostream>


// Add negative numbers
class CNumber
{
public:
	CNumber() {
		const int NUMBER_DEFAULT_LENGTH = 0;
		this->i_length = NUMBER_DEFAULT_LENGTH;
		this->pi_number = new int[i_length];
	}
	CNumber(int i_length, int *pi_number) {
		this->i_length = i_length;
		this->pi_number = pi_number;
	}
	CNumber(const CNumber& pcOther) {
		this->i_length = pcOther.i_length;
		this->pi_number = new int[pcOther.i_length];
		std::copy(pcOther.pi_number, pcOther.pi_number + pcOther.i_length, this->pi_number);
	}
	~CNumber() { delete pi_number; }
	void operator=(const CNumber& pcNewVal);
	void operator=(const int iValue);
	CNumber operator+(CNumber& pcNewVal);
	CNumber operator*(CNumber& pcNewVal);
	CNumber operator-(CNumber& pcNewVal);
	CNumber operator/(CNumber& pcNewVal);
	CNumber operator+(int iNewVal);
	CNumber operator*(int iNewVal);
	CNumber operator-(int iNewVal);
	CNumber operator/(int iNewVal);
	std::string sToStr();
private:
	int* pi_number;
	int i_length;
}; //class CNumber 