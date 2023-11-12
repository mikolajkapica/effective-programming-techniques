#include "UserInterface.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Evaluator.h"
#include "VariablesUtitlities.h"
#include "Node.h"

std::pair<std::pair<Tree*, std::vector<std::string>>, E_ERROR_TYPE> enter(Parser& parser, std::string s_input, std::string& s_out) {
	std::pair<std::vector<Token*>, E_ERROR_TYPE> tokens = parser.vecTokenize(s_input);
	if (tokens.second == E_ERROR_TYPE::INVALID_TOKEN) {
		return std::make_pair(std::make_pair(new Tree(), std::vector<std::string>()), E_ERROR_TYPE::INVALID_TOKEN);
	} else {
		std::pair<Tree *, E_ERROR_TYPE> pc_parsed_tree = parser.pcParse(tokens.first);
		return std::make_pair(std::make_pair(pc_parsed_tree.first, parser.vecGetVariables()), E_ERROR_TYPE::NO_ERROR);
	}
}

void vJoinAux(Node* pc_node, Tree* pc_other) {
	int children_count = pc_node->iGetChildrenCount();
	if (children_count == 0) {
		pc_node->pcGetParent()->vSetChild(pc_node->pcGetParent()->iGetChildrenCount() - 1, pc_other->pcGetRoot());
	} else {
		vJoinAux(pc_node->pcGetChild(children_count - 1), pc_other);
	}
}

void UserInterface::run() {
	bool b_run = true;

	// Initialize variables
	Tree* pc_tree = NULL;
	std::vector<std::string> vec_vars = std::vector<std::string>();
	Parser parser = Parser();

	while (b_run) {
		std::string s_out;

		// Get user input
		std::string s_user_input;
		std::getline(std::cin, s_user_input);
		std::string s_action = s_user_input.substr(0, s_user_input.find(" "));
		std::string s_input = s_user_input.substr(s_user_input.find(" ") + 1, s_user_input.length() - s_user_input.find(" ") - 1);


		// ENTER
		if (s_action == "enter" && s_input != "") {
			std::pair<std::pair<Tree*, std::vector<std::string>>, E_ERROR_TYPE> pair_enter_result = enter(parser, s_input, s_out);
			if (pair_enter_result.second == E_ERROR_TYPE::INVALID_TOKEN) {
				s_out += "Invalid expression\n";
			} else {
				pc_tree = pair_enter_result.first.first;
				vec_vars = pair_enter_result.first.second;
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
				} else {
					s_out += "Result: " + std::to_string(Evaluator().dEvaluateTree(pc_tree, map_values.first)) + "\n";
				}
			}
		}

		// JOIN
		else if (s_action=="join" && s_input != "") {
			if (pc_tree == NULL) {
				s_out += "No tree entered\n";
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
					vJoinAux(pc_tree->pcGetRoot(), pc_tree_to_add);
					for (int i = 0; i < vec_vars_to_add.size(); i++) {
						vec_vars.push_back(vec_vars_to_add[i]);
					}
					std::set<std::string> set_variables(vec_vars.begin(), vec_vars.end());
					vec_vars = std::vector<std::string>(set_variables.begin(), set_variables.end());
				}
			}
		}

		// EXIT
		else if (s_user_input.substr(0, 4) == "exit") {
			b_run = false;
		}

		// INVALID
		else {
			s_out += "Invalid command\n";
		}

		// FLUSH OUTPUT
		std::cout << s_out << std::endl;
	}
}
