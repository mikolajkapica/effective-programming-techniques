#pragma once

class CNumber
{
public:
	CNumber() {
		i_length = NUMBER_DEFAULT_LENGTH; 
		pi_number = new int[i_length];
	};
	~CNumber() { delete pi_number; }
	void operator=(const CNumber& pcNewVal);
	CNumber operator+(CNumber& pcNewVal);
	CNumber operator*(CNumber& pcNewVal);
	CNumber operator-(CNumber& pcNewVal);
	CNumber operator/(CNumber& pcNewVal);
	CNumber operator+(int iNewVal);
	CNumber operator*(int iNewVal);
	CNumber operator-(int iNewVal);
	CNumber operator/(int iNewVal);
	CNumber CNumber::print();
private:
	int* pi_number;
	int i_length;
}//class CNumber 