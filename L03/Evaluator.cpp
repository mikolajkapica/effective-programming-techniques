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

double dEvaluateHelper(Node* pc_current_node, std::map<std::string, int> map_vars) {
	std::cout << "Evaluating: " << pc_current_node->sGetTokensLexeme() << std::endl;
	if (pc_current_node->eGetTokenType() == E_TOKEN_TYPE::VARIABLE)
		std::cout << "Variable: " << pc_current_node->sGetTokensLexeme() << " value: " << map_vars[pc_current_node->sGetTokensLexeme()] << std::endl;
	switch (pc_current_node->eGetTokenType()) {
		case E_TOKEN_TYPE::NUMBER:
			return std::stod(pc_current_node->sGetTokensLexeme());
			break;
		case E_TOKEN_TYPE::VARIABLE:
			return map_vars[pc_current_node->sGetTokensLexeme()];
			break;
		case E_TOKEN_TYPE::OPERATOR:
			std::vector<double> arguments;
			for (int i = 0; i < pc_current_node->vGetChildren().size(); i++) {
				if (pc_current_node->pcGetChild(i) != NULL) {
					arguments.push_back(dEvaluateHelper(pc_current_node->pcGetChild(i), map_vars));
				}
			}
			double res = dOperatorDispatcher(pc_current_node, arguments);
			std::cout << "Result: " << res << std::endl;
			return res;
			break;
	}
}

double Evaluator::dEvaluate(Tree* tree, std::map<std::string, int> map_vars) {
	Node *current_node = tree->pcGetRoot();
	//while (current_node->eGetTokenType() == E_TOKEN_TYPE::OPERATOR) {
	//	current_node = current_node->pcGetChild(0);
	//}
	return dEvaluateHelper(current_node, map_vars);
}


