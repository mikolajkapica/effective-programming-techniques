#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Errors.h"

std::pair<std::map<std::string, double>, E_ERROR_TYPE> mapValuesToVariables(std::vector<std::string> vec_vars, std::string s_values) {
	std::vector<double> vec_values;

	if (s_values.length() != 0) {
		// SEPERATE VALUES BY SPACES
		std::string s_current_value;
		for (int i = 0; i < s_values.length(); i++) {
			if (s_values[i] == ' ') {
				vec_values.push_back(std::stod(s_current_value));
				s_current_value = "";
			} else {
				s_current_value += s_values[i];
			}
		}

		// ADD LAST VALUE
		vec_values.push_back(std::stod(s_current_value));
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
