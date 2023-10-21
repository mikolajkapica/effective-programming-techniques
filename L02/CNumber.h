#pragma once
#include <string>

class CNumber
{
public:
	CNumber() {
		const int NUMBER_DEFAULT_LENGTH = 1;
		this->i_length = NUMBER_DEFAULT_LENGTH;
		this->pi_table = new int[i_length];
	}
	CNumber(int i_length, int *pi_number) {
		this->i_length = i_length;
		this->pi_table = pi_number;
	}
	CNumber(const CNumber& pc_other) {
		this->i_length = pc_other.i_length;
		this->pi_table = new int[pc_other.i_length];
		std::copy(pc_other.pi_table, pc_other.pi_table + pc_other.i_length, this->pi_table);
	}
	~CNumber() { delete this->pi_table; }

	void operator=(const CNumber& pc_other);
	void operator=(const int i_val);

	CNumber operator+(CNumber& pc_other);
	CNumber operator*(CNumber& pc_other);
	CNumber operator-(CNumber& pc_other);
	CNumber operator/(CNumber& pc_other);
	CNumber operator+(int i_val);
	CNumber operator*(int i_val);
	CNumber operator-(int i_val);
	CNumber operator/(int i_val);

	CNumber operator-();
	CNumber operator+();
	CNumber operator+=(CNumber& pc_other);
	CNumber operator+=(int i_val);
	bool operator<(CNumber& pc_other);
	bool operator>(CNumber& pc_other);
	bool operator==(CNumber& pc_other);
	std::string toString();
private:
	int* pi_table;
	int i_length;
};