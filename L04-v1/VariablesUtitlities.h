#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Errors.h"

inline bool hasALetter(std::string t) {
	for (int i = 0; i < t.length(); i++) {
		if (isalpha(t[i])) {
			return true;
		}
	}
	return false;
}

inline bool isInt(std::string t) {
	if (t.length() == 0) {
		return false;
	}
	if (t[0] == '-') {
		t = t.substr(1, t.length() - 1);
	}
	for (int i = 0; i < t.length(); i++) {
		if (!isdigit(t[i])) {
			return false;
		}
	}
	return true;
}

inline bool isDouble(std::string t) {
	if (t.length() == 0) {

		return false;
	}
	if (t[0] == '-') {
		t = t.substr(1, t.length() - 1);
	}
	bool has_decimal = false;
	for (int i = 0; i < t.length(); i++) {
		if (t[i] == '.') {
			if (has_decimal) {
				return false;
			}
			has_decimal = true;
		} else if (!isdigit(t[i])) {
			return false;
		}
	}
	return true;
}

inline bool isString(std::string t) {
	if (t.length() < 2) {
		return false;
	}
	if (t[0] != '"' || t[t.length() - 1] != '"') {
		return false;
	}
	return true;
}
	

inline bool isOnlyWhitespace(std::string t) {
for (int i = 0; i < t.length(); i++) {
		if (!isspace(t[i])) {
			return false;
		}
	}
	return true;
}

inline E_ERROR_TYPE isVariable(std::string &t) {
	if (!hasALetter(t)) {
		return E_ERROR_TYPE::NOT_VARIABLE;
	}
	std::string s_copy = t;
	if (isString(s_copy)) {
		return E_ERROR_TYPE::NOT_VARIABLE;
	}
	int current_letter = 0;
	E_ERROR_TYPE e_type = E_ERROR_TYPE::NO_ERROR;
	for (int i = 0; current_letter < t.length(); i++) {
		if (!isalpha(t[i]) && !isdigit(t[i])) {
			t = t.substr(0, i) + t.substr(i + 1, t.length() - i - 1);
			e_type = E_ERROR_TYPE::INVALID_CHARACTERS;
			i--;
		} else {
			current_letter++;
		}
	}
	return e_type;
}

bool push_back(std::vector<std::string> &vec, std::string t) {
	if (isString(t)) {
		vec.push_back(t);
		return true;
	}
	return false;
}

bool push_back(std::vector<int> &vec, std::string t) {	
	if (isInt(t)) {
		vec.push_back(std::stoi(t));
		return true;
	}
	return false;
}

bool push_back(std::vector<double> &vec, std::string t) {
	if (isDouble(t)) {
		vec.push_back(std::stod(t));
		return true;
	}
	return false;
}

template <typename T>
inline std::pair<std::map<std::string, T>, E_ERROR_TYPE> mapValuesToVariables(std::vector<std::string> vec_vars, std::string s_values) {
	std::vector<T> vec_values;

	if (s_values.length() != 0) {
		// SEPERATE VALUES BY SPACES
		std::string s_current_value;
		for (int i = 0; i < s_values.length(); i++) {
			if (s_values[i] == ' ') {
				if (!isOnlyWhitespace(s_current_value)) {
					if (isString(s_current_value)) {
						s_current_value = s_current_value.substr(1, s_current_value.length() - 2);
					}
					bool b_success_push = push_back(vec_values, s_current_value);
					if (!b_success_push) {
						return std::make_pair(std::map<std::string, T>(), E_ERROR_TYPE::INVALID_VALUE);
					}
				}
				s_current_value = "";
			} else {
				s_current_value += s_values[i];
			}
		}

		// ADD LAST VALUE
		if (s_current_value != "") {
			bool b_success_push = push_back(vec_values, s_current_value);
			if (!b_success_push) {
				return std::make_pair(std::map<std::string, T>(), E_ERROR_TYPE::INVALID_VALUE);
			}
		}
	}

	if (vec_values.size() != vec_vars.size()) {
		return std::make_pair(std::map<std::string, T>(), E_ERROR_TYPE::INVALID_NUMBER_OF_VALUES);
	}
	
	// CREATE MAP
	std::map<std::string, T> map_out;

	for (int i = 0; i < vec_vars.size(); i++) {
		map_out[vec_vars[i]] = vec_values[i];
	}
	return std::make_pair(map_out, E_ERROR_TYPE::NO_ERROR);
}

