#pragma once
#include <iostream>


// Add negative numbers
class CNumber
{
public:
	CNumber() {
		const int NUMBER_DEFAULT_LENGTH = 1;
		this->i_length = NUMBER_DEFAULT_LENGTH;
		this->pi_number = new int[i_length];
		this->name = "Default";
	}
	CNumber(int i_length, int *pi_number) {
		this->i_length = i_length;
		this->pi_number = pi_number;
		//this->name = (*this).toString();
	}
	CNumber(const CNumber& pcOther) {
		this->i_length = pcOther.i_length;
		this->pi_number = new int[pcOther.i_length];
		std::copy(pcOther.pi_number, pcOther.pi_number + pcOther.i_length, this->pi_number);
		//this->name = (*this).toString();
	}
	~CNumber() { 
		//std::cout << "Deleting " << this->name << std::endl;
		delete pi_number; }
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
	CNumber operator-();
	std::string toString();
	void setName(std::string name) { this->name = name; }
private:
	int* pi_number;
	int i_length;
	std::string name;
}; //class CNumber 