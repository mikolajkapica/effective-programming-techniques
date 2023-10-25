#pragma once
#include <string>
#include <iostream>

const int I_BASE = 10;
const int I_NUMBER_DEFAULT_LENGTH = 1;

class CNumber {
public:
	CNumber() {
		this->i_length = I_NUMBER_DEFAULT_LENGTH;
		this->pi_table = new int[I_NUMBER_DEFAULT_LENGTH];
	}
	CNumber(int i_length, int *pi_table) {
		if (i_length == 1) {
			if (pi_table[0] == 0 || pi_table[0] == I_BASE - 1) {
				this->i_length = 2;
				this->pi_table = new int[2];
				this->pi_table[0] = 0;
				this->pi_table[1] = 0;
				return;
			}
			std::cout << "here!" << std::endl;
			throw "Invalid number";
		}
		this->i_length = i_length;
		this->pi_table = pi_table;
	}
	CNumber(const CNumber& pc_other) {
		this->i_length = pc_other.i_length;
		this->pi_table = new int[pc_other.i_length];
		std::copy(pc_other.pi_table, pc_other.pi_table + pc_other.i_length, this->pi_table);
	}
	~CNumber() { delete this->pi_table; }

	void operator=(const CNumber& pc_other);
	void operator=(const int i_val);
	void operator=(const long i_val);

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
	bool operator<=(CNumber& pc_other);
	bool operator>(CNumber& pc_other);
	bool operator>=(CNumber& pc_other);
	bool operator==(CNumber& pc_other);
	bool operator<(int i_val);
	bool operator<=(int i_val);
	bool operator>(int i_val);
	bool operator>=(int i_val);
	bool operator==(int i_val);
	int sgn();
	CNumber cGetWithoutSign(CNumber& pc_other);
	std::string toString();

private:
	int* pi_table;
	int i_length;
};