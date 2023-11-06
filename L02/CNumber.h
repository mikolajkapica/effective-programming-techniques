#pragma once
#include <string>
#include <utility>

const int I_BASE = 10;
const int I_NUMBER_DEFAULT_LENGTH = 1;


class CNumber {
public:
	CNumber() {
		this->i_length = I_NUMBER_DEFAULT_LENGTH;
		this->pi_table = new int[I_NUMBER_DEFAULT_LENGTH];
	}
	CNumber(int i_length, int* pi_table);
	CNumber(const CNumber& pc_other);
	CNumber(const int i_val);
	~CNumber() { delete this->pi_table; }

	void operator=(const CNumber& pc_other);
	void operator=(const int i_val);

	CNumber operator+(CNumber& pc_other);
	CNumber operator*(CNumber& pc_other);
	CNumber operator-(CNumber& pc_other);
	CNumber operator/(CNumber& pc_other);

	CNumber operator+=(CNumber& pc_other);

	CNumber operator+(int i_val);
	CNumber operator*(int i_val);
	CNumber operator-(int i_val);
	CNumber operator/(int i_val);

	CNumber operator+=(int i_val);

	CNumber operator-();
	CNumber operator+();


	bool operator==(CNumber& pc_other);
	bool operator<(CNumber& pc_other);
	bool operator<=(CNumber& pc_other);
	bool operator>(CNumber& pc_other);
	bool operator>=(CNumber& pc_other);

	bool operator==(int i_val);
	bool operator<(int i_val);
	bool operator<=(int i_val);
	bool operator>(int i_val);
	bool operator>=(int i_val);

	int sgn();
	CNumber abs();
	CNumber cGetWithoutSign(CNumber& pc_other);
	std::string toString();

	std::pair<CNumber, CNumber> pDiv(CNumber& pc_other);
	CNumber cMod(CNumber& pc_other, CNumber** pcRes);

private:
	int* pi_table;
	int i_length;
};