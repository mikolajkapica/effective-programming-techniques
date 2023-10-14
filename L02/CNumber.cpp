#include "CNumber.h"

void CNumber::operator=(const CNumber &pcOther) 
{ 
	pi_table = pcOther.pi_table; 
	i_length = pcOther. i_length; 
}//void CTable::operator=(CTable &pcOther)

CNumber CNumber::operator+(CNumber& pcNewVal)
{
	CNumber c_result;
	if (this.i_length > pcNewVal.i_length) {
		c_result.i_length = this->i_length;
		c_result.pi_number = new int[c_result.i_length];

		int i = 0;
		for (; i < this->i_length - pcNewVal.i_length; i++) {
			c_result.pi_number[i] = this.pi_number[i];
		}
		for (int j = 0; i < c_result.i_length; i++, j++) {
			c_result.pi_number[i] = this.pi_number[i] + pcNewVal.pi_number[j];
		}
	} else {
		c_result.i_length = pcNewVal.i_length;
		c_result.pi_number = new int[c_result.i_length];

		int i = 0;
		for (; i < pcNewVal->i_length - this.i_length; i++) {
			c_result.pi_number[i] = pcNewVal.pi_number[i];
		}
		for (int j = 0; i < c_result.i_length; i++, j++) {
			c_result.pi_number[i] = this.pi_number[i] + pcNewVal.pi_number[j];
		}
	}
	return c_result;
}

CNumber CNumber::operator*(CNumber& pcNewVal);
CNumber CNumber::operator-(CNumber& pcNewVal);
CNumber CNumber::operator/(CNumber& pcNewVal);

CNumber CNumber::operator+(int iNewVal) {
	CNumber c_newVal = new CNumber();
	int numToCheckLength = iNewVal;
	int i_length = 0;
	while (numToCheckLength > 0) {
		numToCheckLength /= 10;
		i_length++;
	}
	c_newVal.i_length = i_length;
	c_newVal.pi_number = new int[i_length];

	return *this + c_newVal;
}
CNumber CNumber::operator*(int iNewVal);
CNumber CNumber::operator-(int iNewVal);
CNumber CNumber::operator/(int iNewVal);

CNumber CNumber::print() {
	for (int i = 0; i < this.i_length; i++) {
		std::cout << this.pi_number[i];
	}
}
