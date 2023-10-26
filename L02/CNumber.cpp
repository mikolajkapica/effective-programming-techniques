#include "CNumber.h"
#include <iostream>
#include <string>

void print_table(int* pi_table, int i_length) {
	for (int i = 0; i < i_length; i++) {
		std::cout << pi_table[i] << " ";
	}
	std::cout << std::endl;
}

CNumber CNumber::cGetWithoutSign(CNumber& c_number) {
	CNumber c_result = c_number;
	c_result.i_length--;
	int* pi_old_table = new int[c_number.i_length];
	std::copy(c_number.pi_table, c_number.pi_table + c_number.i_length, pi_old_table);
	c_result.pi_table = new int[c_result.i_length];
	std::copy(pi_old_table + 1, pi_old_table + c_number.i_length, c_result.pi_table);
	return c_result;
}

CNumber intToCNumber(int i_val) {
	int i_base = 10;
	int i_sign = i_val < 0 ? -1 : 1;
	int i_val_abs = i_sign * i_val;
	int i_length = 1; // 1 for the i_sign
	while (i_val_abs > 0) {
		i_val_abs /= i_base;
		i_length++;
	}
	int* pi_table = new int[i_length];
	i_val_abs = i_sign * i_val;
	for (int i = i_length - 1; i >= 0; i--) {
		pi_table[i] = i_val_abs % i_base;
		i_val_abs /= i_base;
	}
	if (i_sign == -1) return -CNumber(i_length, pi_table);
	return CNumber(i_length, pi_table);
}

void clearRedundantPrefix(int* &pi_table, int& i_length) {	
	if (i_length > 2) {
		int i_prefix_signs_count = 1; // skip sign
		int i_first_digit = pi_table[0];
		while (pi_table[i_prefix_signs_count] == i_first_digit) {
			i_prefix_signs_count++;
		}
		i_prefix_signs_count--; // decrement for the sign

		if (i_prefix_signs_count == 0) return;

		i_prefix_signs_count = std::min(i_length - 2, i_prefix_signs_count); // we have to keep at least two digits

		int* pi_table_new = new int[i_length - i_prefix_signs_count];
		for (int i = 0; i < i_length - i_prefix_signs_count; i++) {
			pi_table_new[i] = pi_table[i + i_prefix_signs_count];
		}
		delete pi_table; // nie wiem czy musze? bez deletowania nie mam tez bledu // dziwne
		pi_table = pi_table_new;
		i_length = i_length - i_prefix_signs_count;
	}
}

void CNumber::operator=(const CNumber &pc_other) { 
	if (this->pi_table != nullptr) {
		delete this->pi_table;
	}
	this->i_length = pc_other.i_length;
	this->pi_table = new int[pc_other.i_length];
	std::copy(pc_other.pi_table, pc_other.pi_table + pc_other.i_length, this->pi_table);
}

void CNumber::operator=(const int i_val) { 
	*this = intToCNumber(i_val);
}

void CNumber::operator=(const long i_val)
{
	*this = intToCNumber(i_val);
}

CNumber CNumber::operator+(CNumber& pc_new_val) {
	int i_length_a = this->i_length;
	int i_length_b = pc_new_val.i_length;
	int i_first_digit_a = this->pi_table[0];
	int i_first_digit_b = pc_new_val.pi_table[0];

	int i_length_result = i_length_a > i_length_b ? i_length_a: i_length_b;
	i_length_result++; // for the overflow possibility
	int *pi_table_result = new int[i_length_result];

	int i_curr_pos_a = this->i_length;
	int i_curr_pos_b = pc_new_val.i_length;
	int i_carry = 0;

	for (int i = i_length_result - 1; i >= 0; i--) {
		int i_a_digit = i_curr_pos_a > 0 ? this->pi_table[--i_curr_pos_a] : i_first_digit_a;
		int i_b_digit = i_curr_pos_b > 0 ? pc_new_val.pi_table[--i_curr_pos_b] : i_first_digit_b;
		int i_sum = i_a_digit + i_b_digit + i_carry;
		i_carry = i_sum / I_BASE;
		pi_table_result[i] = i_sum % I_BASE;
	}

	clearRedundantPrefix(pi_table_result, i_length_result);

	return CNumber(i_length_result, pi_table_result);
}

CNumber CNumber::operator*(CNumber& pc_new_val) {
	int i_length_a = this->i_length;
	int i_length_b = pc_new_val.i_length;

	int i_length_result = i_length_a + i_length_b - 1;

	int *pi_result = new int[i_length_result];
	for (int i = 0; i < i_length_result; i++) {
		pi_result[i] = 0;
	}

	for (int i = 0; i < i_length_result; i++) {
		int i_carry = 0;
		int multiplier = i < i_length_a ? this->pi_table[i_length_a - i - 1] : this->pi_table[0];
		if (multiplier != 0) {
			for (int j = 0; j < i_length_result && i_length_result - i - j - 1 >= 0; j++) {
				int i_multiplicand = j < i_length_b ? pc_new_val.pi_table[i_length_b-j-1] : pc_new_val.pi_table[0];
				if (!(i_multiplicand == 0 && i_carry == 0)) {
					int i_product = multiplier * i_multiplicand;
					int i_sum = pi_result[i_length_result - i - j - 1] + i_product + i_carry;
					int i_digit = i_sum % I_BASE;
					i_carry = i_sum / I_BASE;
					pi_result[i_length_result - i - j - 1] = i_digit;
				}
			}
			i_length_b = pc_new_val.i_length;
		}
	}

	clearRedundantPrefix(pi_result, i_length_result);

	return CNumber(i_length_result, pi_result);
}

CNumber CNumber::operator-(CNumber& pc_new_val) {
	return *this + (-pc_new_val);
}

CNumber CNumber::operator/(CNumber& pc_new_val) {
	if ((*this) == 0) {
		CNumber a;
		a = 0;
		return a;
	}
	int i_sign_a = this->sgn();
	int i_sign_b = pc_new_val.sgn();

	// normalize to positive integers
	if (i_sign_a * i_sign_b == 1) {
		if (i_sign_a == -1) {
			return (-(*this)) / (-pc_new_val);
		}
	} else {
		if (i_sign_a == -1) {
			return -((-(*this)) / pc_new_val);
		} else {
			return -((*this) / (-pc_new_val));
		}
	}

	// a / b
	CNumber c_a = *this;
	CNumber c_b = pc_new_val;

	int i_length_a = c_a.i_length;
	int i_length_b = c_b.i_length;

	if (i_length_a < i_length_b || c_a < c_b) {
		CNumber a;
		a = 0;
		return a;
	}

	// find first digit of a and b
	int i_first_digit_a = c_a.pi_table[1];
	int i_first_digit_b = c_b.pi_table[1];	

	bool b_was_smaller;
	bool b_first_iteration = true;

	// make result table
	int i_table_result_length = i_length_a - i_length_b + 1 + 1;
	int *pi_table_result = new int[i_table_result_length];
	int i_current_result_position = 1;
	pi_table_result[0] = 0;


	// make operations table
	int i_table_operations_length = i_length_b - 1;
	int *pi_table_operations = new int[i_table_operations_length];
	for (int i = 0; i < i_table_operations_length; i++) {
		pi_table_operations[i] = c_a.pi_table[i];
	}
	CNumber c_current_operations(i_table_operations_length, pi_table_operations);


	for (; i_current_result_position < i_table_result_length; i_current_result_position++) {
		b_first_iteration = true;
		c_current_operations = c_current_operations * 10 + c_a.pi_table[i_length_b - 1 - 1 + i_current_result_position];
		int i_approximate_division = c_a.pi_table[i_current_result_position] / i_first_digit_b;

		bool b_run = true;
		while (b_run) {
			CNumber c_division_leftover = c_current_operations - c_b * i_approximate_division;

			if (c_division_leftover >= 0 && c_division_leftover < c_b) {
				pi_table_result[i_current_result_position] = i_approximate_division;
				c_current_operations = c_current_operations - c_b * i_approximate_division;
				b_run = false;
			} else {
				if (c_division_leftover < 0) {
					i_approximate_division--;
				} else {
					i_approximate_division++;
				}
			}
		}
	}


	clearRedundantPrefix(pi_table_result, i_table_result_length);

	return CNumber(i_table_result_length, pi_table_result);
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
	if (this->sgn() == 0) {
		return *this;
	}
	int i_max_digit = I_BASE - 1;
	int *pi_table = new int[this->i_length];

	// find last non zero digit
	int i_curr_pos = this->i_length - 1;
	while (this->pi_table[i_curr_pos] == 0) {
		i_curr_pos--;
	}

	for (int i = 0; i < i_curr_pos + 1; i++) {
		pi_table[i] = i_max_digit - this->pi_table[i];
	}
	for (int i = i_curr_pos + 1; i < this->i_length; i++) {
		pi_table[i] = 0;
	}

	pi_table[i_curr_pos]++;

	return CNumber(this->i_length, pi_table);
}

CNumber CNumber::operator+() {
	return *this;
}

CNumber CNumber::operator+=(CNumber& pc_other) {
	return *this + pc_other;
}

CNumber CNumber::operator+=(int i_val) {
	return *this + i_val;
}

bool CNumber::operator<(CNumber& pc_other) {
	int i_sign_a = this->sgn();
	int i_sign_b = pc_other.sgn();
	if (i_sign_a != i_sign_b) {
		return i_sign_a < i_sign_b;
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

bool CNumber::operator<=(CNumber& pc_other) {
	return *this < pc_other || *this == pc_other;
}

bool CNumber::operator>(CNumber& pc_other) {
	return pc_other < *this;
}

bool CNumber::operator>=(CNumber& pc_other) {
	return *this > pc_other || *this == pc_other;
}

bool CNumber::operator==(CNumber& pc_other) {
	int i_sign_a = this->sgn();
	int i_sign_b = pc_other.sgn();
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

bool CNumber::operator<(int i_val) {
	int i_sign_a = this->sgn();
	if (i_val == 0) {
		return (i_sign_a < 0);
	}
	int i_sign_b = i_val < 0 ? -1 : 1;
	if (i_sign_a != i_sign_b) {
		return i_sign_a < i_sign_b;
	}

	return *this < intToCNumber(i_val);
}

bool CNumber::operator<=(int i_val) {
	int i_sign_a = this->sgn();
	if (i_val == 0) {
		return (i_sign_a <= 0);
	}
	int i_sign_b = i_val < 0 ? -1 : 1;
	if (i_sign_a != i_sign_b) {
		return i_sign_a < i_sign_b;
	}

	return *this <= intToCNumber(i_val);
}

bool CNumber::operator>(int i_val) {
	int i_sign_a = this->sgn();
	if (i_val == 0) {
		return (i_sign_a > 0);
	}
	int i_sign_b = i_val < 0 ? -1 : 1;
	if (i_sign_a != i_sign_b) {
		return i_sign_a > i_sign_b;
	}

	return *this > intToCNumber(i_val);
}

bool CNumber::operator>=(int i_val) {
	int i_sign_a = this->sgn();
	if (i_val == 0) {
		return (i_sign_a >= 0);
	}
	int i_sign_b = i_val < 0 ? -1 : 1;
	if (i_sign_a != i_sign_b) {
		return i_sign_a > i_sign_b;
	}

	return *this >= intToCNumber(i_val);
}

bool CNumber::operator==(int i_val) {
	int i_sign_a = this->sgn();
	if (i_val == 0) {
		return (i_sign_a == 0);
	}
	int i_sign_b = i_val < 0 ? -1 : 1;
	if (i_sign_a != i_sign_b) {
		return false;
	}
	return *this == intToCNumber(i_val);
}


int CNumber::sgn() {
	if (this->pi_table[0] == I_BASE - 1) {
		return -1;
	} else if (this->pi_table[0] == 0 && this->pi_table[1] == 0) {
		return 0;
	} else if (this->pi_table[0] == 0) {
		return 1;
	} else {
		// ?????
		std::cout << "Invalid number" << this->pi_table[0] << std::endl;
		throw "Invalid number";
	}
}

CNumber CNumber::abs() {
	return  (*this) * this->sgn();
}

std::string CNumber::toString() {
	if (this->sgn() == -1) {
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
