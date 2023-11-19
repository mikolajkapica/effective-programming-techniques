#include "UserInterface.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Evaluator.h"
#include "Node.h"
#include "VariablesUtitlities.h"

std::pair<std::pair<Tree*, std::vector<std::string>>, E_ERROR_TYPE> enter(Parser* parser, std::string s_input, std::string& s_out) {
	std::pair<std::vector<Token*>, E_ERROR_TYPE> tokens = (*parser).vecTokenize(s_input, s_out);
	if (tokens.second == E_ERROR_TYPE::INVALID_TOKEN) {
		return std::make_pair(std::make_pair(new Tree(), std::vector<std::string>()), E_ERROR_TYPE::INVALID_TOKEN);
	} else {
		std::pair<Tree *, E_ERROR_TYPE> pc_parsed_tree = (*parser).pcParse(tokens.first);
		return std::make_pair(std::make_pair(pc_parsed_tree.first, (*parser).vecGetVariables()), pc_parsed_tree.second);
	}
}

std::string UserInterface::run(Tree*& pc_tree, std::vector<std::string>& vec_vars, Parser*& parser, bool &b_run) {
	std::string s_out;

	// Get user input
	std::string s_user_input;
	std::getline(std::cin, s_user_input);
	std::string s_action = s_user_input.substr(0, s_user_input.find(" "));
	std::string s_input = s_user_input.substr(s_user_input.find(" ") + 1, s_user_input.length());
	if (s_action == s_input) s_input = "";

	// ENTER
	if (s_action == "enter" && s_input != "") {
		std::pair<std::pair<Tree*, std::vector<std::string>>, E_ERROR_TYPE> pair_enter_result = enter(parser, s_input, s_out);
		if (pair_enter_result.second == E_ERROR_TYPE::INVALID_TOKEN) {
			s_out += "Invalid expression\n";
		} else {
			if (pair_enter_result.second == E_ERROR_TYPE::PARSING_PROBLEM) {
				s_out += "Parsing problem, some tokens were cut off\n";
			}
			if (pair_enter_result.second == E_ERROR_TYPE::TREE_CORRECTED) {
				s_out += "Tree had to be corrected\n";
			}
			pc_tree = pair_enter_result.first.first;
			vec_vars = pair_enter_result.first.second;
			s_out += pc_tree->sToString();
		}
	}

	// VARS
	else if (s_action == "vars") {
		if (pc_tree == NULL) {
			s_out += "No tree entered\n";
		} else if (vec_vars.size() == 0) {
			s_out += "No variables\n";
		} else {
			s_out += "Variables:";
			for (int i = 0; i < vec_vars.size(); i++) {
				s_out += " " + vec_vars[i];
			}
			s_out += "\n";
		}
	}

	// PRINT
	else if (s_action == "print") {
		if (pc_tree == NULL) {
			s_out += "No tree entered\n";
		} else {
			s_out += pc_tree->sToString();
		}
	}

	// COMP
	else if (s_action == "comp") {
		if (pc_tree == NULL) {
			s_out += "No tree entered\n";
		} else {
			std::pair<std::map<std::string, double>, E_ERROR_TYPE> map_values = mapValuesToVariables(vec_vars, s_input);
			if (map_values.second == E_ERROR_TYPE::INVALID_NUMBER_OF_VALUES) {
				s_out += "Invalid number of values\n";
			} else if (map_values.second == E_ERROR_TYPE::INVALID_VALUE) {
				s_out += "Invalid value\n";
			} else {
				s_out += "Result: " + std::to_string(Evaluator().dEvaluateTree(pc_tree, map_values.first)) + "\n";
			}
		}
	}

	// JOIN
	else if (s_action=="join" && s_input != "") {
		if (pc_tree == NULL) {
			s_out = "No tree entered\n";
		} else {
			Tree* pc_tree_to_add = pc_tree;
			std::vector<std::string> vec_vars_to_add;

			// PARSE AND ASSIGN
			std::pair<std::pair<Tree*, std::vector<std::string>>, E_ERROR_TYPE> pair_enter_result = enter(parser, s_input, s_out);
			if (pair_enter_result.second == E_ERROR_TYPE::INVALID_TOKEN) {
				s_out += "Invalid expression\n";
			} else {
				pc_tree_to_add = pair_enter_result.first.first;
				vec_vars_to_add = pair_enter_result.first.second;
				// JOIN THIS TREE WITH THE OTHER TREE (RIGHTMOST LEAF)
				*pc_tree = *pc_tree + pc_tree_to_add;
				vec_vars = pc_tree->vecGetVariables();
			}
		}
	}

	// EXIT
	else if (s_user_input.substr(0, 4) == "exit") {
		s_out = "Exiting...\n";
		b_run = false;
	}

	// INVALID
	else {
		s_out = "Invalid command\n";
	}

	// FLUSH OUTPUT
	return s_out;
}
