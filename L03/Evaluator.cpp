#include "Evaluator.h"
#include "Tree.h"
#include "Token.h"
#include "Node.h"

#include <cmath>
#include <iostream>

double dOperatorDispatcher(Node* node, std::vector<double> arguments) {
	std::string lexeme = node->sGetTokensLexeme();
	if (arguments.size() == 2) {
		if (lexeme == "+") return arguments[0] + arguments[1];
		if (lexeme == "-") return arguments[0] - arguments[1];
		if (lexeme == "*") return arguments[0] * arguments[1];
		if (lexeme == "/") return arguments[0] / arguments[1];
	} else if (arguments.size() == 1) {
		if (lexeme == "sin") return std::sin(arguments[0]);
		if (lexeme == "cos") return std::cos(arguments[0]);
	}
}

double dEvaluateHelper(Node* pc_current_node, std::map<std::string, double> map_vars) {
		switch (pc_current_node->eGetTokenType()) {
		case E_TOKEN_TYPE::NUMBER:
			return std::stod(pc_current_node->sGetTokensLexeme());
		case E_TOKEN_TYPE::VARIABLE:
			return map_vars[pc_current_node->sGetTokensLexeme()];
		case E_TOKEN_TYPE::OPERATOR:
			std::vector<double> arguments;
			for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
				arguments.push_back(dEvaluateHelper(pc_current_node->pcGetChild(i), map_vars));
			}
			return dOperatorDispatcher(pc_current_node, arguments);
	}
}

double Evaluator::dEvaluateTree(Tree* tree, std::map<std::string, double> map_vars) {
	Node* current_node = tree->pcGetRoot();
	return dEvaluateHelper(current_node, map_vars);
}


