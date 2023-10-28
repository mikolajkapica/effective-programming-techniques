#include "UserInterface.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Evaluator.h"

#define DEBUG true 

UserInterface::~UserInterface() {
	delete this->pc_tree;
}

std::map<std::string, double> mapValuesToVariables(std::vector<std::string> vars, std::vector<double> values) {
	std::map<std::string, double> map_out;
	for (int i = 0; i < vars.size(); i++) {
		map_out[vars[i]] = values[i];
	}
	return map_out;
}

std::vector<double> valuesStringToDoubles(std::string s_values) {
	std::vector<double> vec_out;
	if (s_values.length() == 0) {
		return vec_out;
	}
	std::string s_current_value;
	for (int i = 0; i < s_values.length(); i++) {
		if (s_values[i] == ' ') {
			vec_out.push_back(std::stod(s_current_value));
			s_current_value = "";
		}
		else {
			s_current_value += s_values[i];
		}
	}
	vec_out.push_back(std::stod(s_current_value));
	return vec_out;
}

void UserInterface::run() {
	while (this->b_run) {
		std::string s_user_input;
		std::getline(std::cin, s_user_input);
		// ENTER
		if (s_user_input.substr(0, 5) == "enter" && s_user_input.length() - 5 != 0) {
			Parser parser = Parser(s_user_input.substr(6, s_user_input.length() - 6));
			std::pair<std::vector<Token*>, E_ERROR_TYPE> tokens = parser.vecTokenize();
			if (tokens.second != E_ERROR_TYPE::NO_ERROR) {
				std::cout << "Invalid expression" << std::endl;
			} else {
				this->pc_tree = parser.pcParse(tokens.first);
				if (pc_tree == NULL) std::cout << "Invalid expression" << std::endl;
				else this->vec_vars = parser.vecGetVariables();
			}
		// VARS
		} else if (s_user_input.substr(0, 4) == "vars") {
			if (this->pc_tree == NULL) std::cout << "" << std::endl;
			else {
				std::vector<std::string> vars = this->vec_vars;
				std::string s_out = "Variables:";
				for (int i = 0; i < vars.size(); i++) {
					s_out += " " + vars[i];
				}
				std::cout << s_out << std::endl;
			}
		// PRINT
		} else if (s_user_input.substr(0, 5) == "print") {
			if (this->pc_tree == NULL) std::cout << "No tree entered" << std::endl;
			else std::cout << this->pc_tree->sToString() << std::endl;
		// COMP
		} else if (s_user_input.substr(0, 4) == "comp") {
			std::string s_variable_values;
			if (s_user_input.length() - 4 > 0) s_variable_values = s_user_input.substr(5, s_user_input.length() - 4);
			std::map<std::string, double> mapValues;
			if (this->pc_tree != NULL) {
				std::vector<double> vecValues = valuesStringToDoubles(s_variable_values);
				if (vecValues.size() != this->vec_vars.size()) std::cout << "Invalid number of values" << std::endl;
				else {
					mapValues = mapValuesToVariables(this->vec_vars, vecValues);
					double d_result = Evaluator().dEvaluateTree(this->pc_tree, mapValues);
					std::cout << "Result: " << d_result << std::endl;
				}
			} else std::cout << "No tree entered" << std::endl;
		// JOIN
		} else if (s_user_input.substr(0, 4) == "join") {
			throw "Unimplemented";
		// EXIT
		} else if (s_user_input.substr(0, 4) == "exit") {
			this->b_run = false;
		// INVALID
		} else {
			std::cout << "Invalid command" << std::endl;
		}
	}
}
