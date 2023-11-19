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

inline E_ERROR_TYPE isVariable(std::string &t) {
	if (!hasALetter(t)) {
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

inline bool isNumber(std::string t) {
	bool has_dot = false;
	for (int i = 0; i < t.length(); i++) {
		if (t[i] == '.') {
			if (has_dot) return false;
			has_dot = true;
		} else if (!isdigit(t[i])) {
			return false;
		}
	}
	return true;
}


inline std::pair<std::map<std::string, double>, E_ERROR_TYPE> mapValuesToVariables(std::vector<std::string> vec_vars, std::string s_values) {
	std::vector<double> vec_values;

	if (s_values.length() != 0) {
		// SEPERATE VALUES BY SPACES
		std::string s_current_value;
		for (int i = 0; i < s_values.length(); i++) {
			if (s_values[i] == ' ') {
				if (isNumber(s_current_value)) {
					vec_values.push_back(std::stod(s_current_value));
				} else {
					return std::make_pair(std::map<std::string, double>(), E_ERROR_TYPE::INVALID_VALUE);
				}
				s_current_value = "";
			} else {
				s_current_value += s_values[i];
			}
		}

		// ADD LAST VALUE
		if (isNumber(s_current_value)) {
			vec_values.push_back(std::stod(s_current_value));
		} else {
			return std::make_pair(std::map<std::string, double>(), E_ERROR_TYPE::INVALID_VALUE);
		}
	}

	if (vec_values.size() != vec_vars.size()) {
		return std::make_pair(std::map<std::string, double>(), E_ERROR_TYPE::INVALID_NUMBER_OF_VALUES);
	}
	
	// CREATE MAP
	std::map<std::string, double> map_out;

	for (int i = 0; i < vec_vars.size(); i++) {
		map_out[vec_vars[i]] = vec_values[i];
	}
	return std::make_pair(map_out, E_ERROR_TYPE::NO_ERROR);
}
