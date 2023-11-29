#pragma once

#include "parser.h"
#include "errors.h"

#include <map>
#include <string>

template <typename T>
class Evaluator {
public:
	T tEvaluateTree(Tree<T>* pc_tree, std::map<std::string, T> map_variables);
};

int tOperatorEvaluate(Node<int>* pc_node, std::vector<int> arguments) {
	std::string lexeme = pc_node->sGetTokenLexeme();
	if (lexeme == "+")   return (int)(arguments[0] + arguments[1]);
	if (lexeme == "-")   return (int)(arguments[0] - arguments[1]);
	if (lexeme == "*")   return (int)(arguments[0] * arguments[1]);
	if (lexeme == "/")   return (int)(arguments[0] / arguments[1]);
	if (lexeme == "sin") return (int)(std::sin(arguments[0]));
	if (lexeme == "cos") return (int)(std::cos(arguments[0]));
	throw std::exception("Unknown operator");
}

double tOperatorEvaluate(Node<double>* pc_node, std::vector<double> arguments) {
	std::string lexeme = pc_node->sGetTokenLexeme();
	if (lexeme == "+")   return arguments[0] + arguments[1];
	if (lexeme == "-")   return arguments[0] - arguments[1];
	if (lexeme == "*")   return arguments[0] * arguments[1];
	if (lexeme == "/")   return arguments[0] / arguments[1];
	if (lexeme == "sin") return std::sin(arguments[0]);
	if (lexeme == "cos") return std::cos(arguments[0]);
	throw std::exception("Unknown operator");
}

std::string tOperatorEvaluate(Node<std::string>* pc_node, std::vector<std::string> arguments) {
	std::string lexeme = pc_node->sGetTokenLexeme();
	if (lexeme == "+")   return arguments[0] + arguments[1];

	if (lexeme == "-") {
		if (arguments[1] == "") return arguments[0];
		size_t pos = arguments[0].rfind(arguments[1]);
		if (pos == std::string::npos) {
			throw std::exception("Substring not found");
		}
		return arguments[0].substr(0, pos);
	}

	if (lexeme == "*") { // „alaxalaxala” * „xABC” = „alaxABCalaxABCala”
		if (arguments[1] == "") return arguments[0];
		char first_char = arguments[1][0];
		std::string s_add = arguments[1].substr(1, arguments[1].size() - 1);
		std::string s_result = "";
		for (int i = 0; i < arguments[0].size(); i++) {
			s_result += arguments[0][i];
			if (arguments[0][i] == first_char) {
				s_result += s_add;
			}
		}
		return s_result;
	}

	if (lexeme == "/") { // „alaxalaxala” / „xABC” = „alaxala”
		if (arguments[1] == "") return arguments[0];
		char first_char = arguments[1][0];
		std::string s_sub = arguments[1].substr(1, arguments[1].size() - 1);
		std::string s_result = "";
		for (int i = 0; i < arguments[0].size(); i++) {
			s_result += arguments[0][i];
			if (arguments[0][i] == first_char) {
				i += (int)s_sub.size();
			}
		}
		return s_result;
	}

	throw std::exception("Unknown operator");
}

bool tOperatorEvaluate(Node<bool>* pc_node, std::vector<bool> arguments) {
	std::string lexeme = pc_node->sGetTokenLexeme();
	if (lexeme == "+")   return arguments[0] || arguments[1];
	if (lexeme == "*")   return arguments[0] && arguments[1];
	throw std::exception("Unknown operator");
}


template <typename T>
T tEvaluateTreeAux(Node<T> *pc_current_node, std::map<std::string, T> map_vars) {
	std::vector<T> arguments;
	switch (pc_current_node->eGetTokenType()) {
	case ETokenType::CONSTANT:
		return pc_current_node->tGetTokenValue();
	case ETokenType::VARIABLE:
		return map_vars[pc_current_node->sGetTokenLexeme()];
	case ETokenType::OPERATOR:
		for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
			arguments.push_back(tEvaluateTreeAux(pc_current_node->pcGetNthChild(i), map_vars));
		}
		return tOperatorEvaluate(pc_current_node, arguments);
	case ETokenType::NONE:
		throw std::exception("Unknown token type");
	default:
		throw std::exception("Unknown token type");
	}
}

template <typename T>
T Evaluator<T>::tEvaluateTree(Tree<T>* pc_tree, std::map<std::string, T> map_variables) {
	return tEvaluateTreeAux<T>(pc_tree->pcGetRoot(), map_variables);
}

// IDEA!
//template <typename T>
//T tEvaluateTree(Tree<T>* pc_tree, std::map<std::string, T> map_variables, Node<T> *pc_current_node=pc_tree->pcGetRoot()) {
//	return tEvaluateTreeAux(pc_tree->pcGetRoot(), map_variables);
//}
