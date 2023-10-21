#include "CNumber.h"
#include <iostream>
#include <string>

CNumber intToCNumber(int i_val) {
	int sign = i_val < 0 ? -1 : 1;
	int i_val_abs = sign * i_val;
	int i_length = 1; // 1 for the sign
	while (i_val_abs > 0) {
		i_val_abs /= 10;
		i_length++;
	}

	int* pi_table = new int[i_length];
	if (sign == -1) {
		i_val = -i_val;
		for (int i = i_length - 1; i >= 0; i--) {
			pi_table[i] = 9 - (i_val % 10);
			i_val /= 10;
		}
		pi_table[i_length - 1]++;
	}
	else {
		for (int i = i_length - 1; i >= 0; i--) {
			pi_table[i] = i_val % 10;
			i_val /= 10;
		}
	}

	return CNumber(i_length, pi_table);
}

void CNumber::operator=(const CNumber &pc_other) { 
	this->i_length = pc_other.i_length;
	this->pi_table = new int[pc_other.i_length];
	std::copy(pc_other.pi_table, pc_other.pi_table + pc_other.i_length, this->pi_table);
}

void CNumber::operator=(const int i_val) { 
	*this = intToCNumber(i_val);
}

CNumber CNumber::operator+(CNumber& pc_new_val) {
	int i_max_digit = 9;

	int i_length_a = this->i_length;
	int i_length_b = pc_new_val.i_length;
	int i_sign_b = pc_new_val.pi_table[0] == i_max_digit ? 1 : -1;
	int i_sign_a = this->pi_table[0] == i_max_digit ? 1 : -1;

	int i_length_result = i_length_a > i_length_b ? i_length_a : i_length_b;
	int *pi_table_result = new int[i_length_result];

	int i_curr_pos_a = this->i_length;
	int i_curr_pos_b = pc_new_val.i_length;
	int i_carry = 0;

	for (int i = i_length_result - 1; i >= 0; i--) {
		int i_a_digit = i_curr_pos_a > 0 ? this->pi_table[--i_curr_pos_a] : 0;
		int i_b_digit = i_curr_pos_b > 0 ? pc_new_val.pi_table[--i_curr_pos_b] : 0;
		int i_sum = i_a_digit + i_b_digit + i_carry;
		i_carry = i_sum / 10;
		pi_table_result[i] = i_sum % 10;
	}
	// in case of overflow (e.g. 0999 + 01 = 1000 or 08 + 02 = 10 or 92 + 98 = 
	if (pi_table_result[0] != 0 && i_length_result != 9) {
		int *new_pi_table_result = new int[i_length_result + 1];
		for (int i = i_length_result; i > 0; i--) {
			new_pi_table_result[i] = pi_table_result[i - 1];
		}
		new_pi_table_result[0] = 0;
		int new_i_length_result = i_length_result + 1;
		return CNumber(new_i_length_result, new_pi_table_result);
	}

	return CNumber(i_length_result, pi_table_result);
}

CNumber CNumber::operator*(CNumber& pc_new_val) {
	int max_digit = 9;

	int i_length_a = this->i_length;
	int i_length_b = pc_new_val.i_length;
	int i_sign_a = this->pi_table[0] == max_digit;    // negative then 1
	int i_sign_b = pc_new_val.pi_table[0] == max_digit; // negative then 1

	int i_length_result = i_length_a + i_length_b - 1;

	int *pi_result = new int[i_length_result];
	for (int i = 0; i < i_length_result; i++) {
		pi_result[i] = 0;
	}

	for (int i = 0; i < i_length_result; i++) {
		int i_carry = 0;
		int multiplier = i < i_length_a ? this->pi_table[i_length_a-i-1] : max_digit * i_sign_a;
		if (multiplier == 0) continue;
		for (int j = 0; j < i_length_result; j++) {
			if (i_length_result - i - j - 1 < 0) break;
			int i_multiplicand = j < i_length_b ? pc_new_val.pi_table[i_length_b-j-1] : max_digit * i_sign_b;
			if (i_multiplicand == 0 && i_carry == 0) {
				continue;
			}
			int i_product = multiplier * i_multiplicand;
			int i_sum = pi_result[i_length_result - i - j - 1] + i_product + i_carry;
			int i_digit = i_sum % 10;
			i_carry = i_sum / 10;
			pi_result[i_length_result - i - j - 1] = i_digit;
		}
		i_length_b = pc_new_val.i_length;
	}
	return CNumber(i_length_result, pi_result);
}

CNumber CNumber::operator-(CNumber& pc_new_val) {
	return *this + (-pc_new_val);
}

CNumber CNumber::operator/(CNumber& pc_new_val) {
	int i_result = 0;
	CNumber i_accumulator;

	i_accumulator = 0;
	while (i_accumulator < *this) {
		i_accumulator = i_accumulator + pc_new_val;
		i_result++;
	}

	CNumber c_result;
	c_result = i_result;

	return c_result;
}

CNumber CNumber::operator+(int i_new_val) {
	return *this + intToCNumber(i_new_val);
}

CNumber CNumber::operator*(int i_new_val) {
	return *this * intToCNumber(i_new_val);
}

CNumber CNumber::operator-(int i_new_val) {
	return *this + intToCNumber(-i_new_val);
}

CNumber CNumber::operator/(int i_new_val) {
	return *this / intToCNumber(i_new_val);
}

CNumber CNumber::operator-() {
	int i_max_digit = 9;
	int *pi_table = new int[this->i_length];
	for (int i = 0; i < this->i_length; i++) {
		pi_table[i] = i_max_digit - this->pi_table[i];
	}
	pi_table[this->i_length - 1]++;
	return CNumber(this->i_length, pi_table);
}

CNumber CNumber::operator+() {
	return *this;
}

CNumber CNumber::operator+=(CNumber& pc_other) {
	return *this + pc_other; // why!!???
}

CNumber CNumber::operator+=(int i_val) {
	return *this + i_val;
}

bool CNumber::operator<(CNumber& pc_other) {
	int i_max_digit = 9;
	int i_sign_a = this->pi_table[0] == i_max_digit ? 1 : -1;
	int i_sign_b = pc_other.pi_table[0] == i_max_digit ? 1 : -1;
	if (i_sign_a != i_sign_b) {
		return i_sign_a > i_sign_b;
	}
	if (this->i_length != pc_other.i_length) {
		return this->i_length < pc_other.i_length;
	}
	for (int i = 1; i < this->i_length; i++) {
		if (this->pi_table[i] != pc_other.pi_table[i]) {
			return this->pi_table[i] < pc_other.pi_table[i];
		}
	}
	return false;
}

bool CNumber::operator>(CNumber& pc_other) {
	return pc_other < *this;
}

bool CNumber::operator==(CNumber& pc_other) {
	int i_max_digit = 9;
	int i_sign_a = this->pi_table[0] == i_max_digit ? 1 : -1;
	int i_sign_b = pc_other.pi_table[0] == i_max_digit ? 1 : -1;
	if (i_sign_a != i_sign_b) {
		return false;
	}
	if (this->i_length != pc_other.i_length) {
		return false;
	}
	for (int i = 1; i < this->i_length; i++) {
		if (this->pi_table[i] != pc_other.pi_table[i]) {
			return false;
		}
	}
	return true;
}

std::string CNumber::toString() {
	int i_max_digit = 9;
	if (this->pi_table[0] == i_max_digit) {
		return "-" + (- (*this)).toString();
	}
	std::string out = "";
	int i_prefix_zeros_count = 0;
	for (int i = 0; this->pi_table[i] == 0; i++) {
		i_prefix_zeros_count++;
	}
	for (int i = i_prefix_zeros_count; i < this->i_length; i++) {
		out += std::to_string(this->pi_table[i]);
	}
	if (out == "") {
		out = "0";
	}
	return out; 
}
