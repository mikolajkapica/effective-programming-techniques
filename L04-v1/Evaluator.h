#pragma once

#include <map>
#include <string>

class Tree;

template <typename T>
class Evaluator {
public:
	T dEvaluateTree(Tree *tree, std::map<std::string, T> map_vars);
	T dEvaluateHelper(Node* pc_current_node, std::map<std::string, T> map_vars);
	T stot(std::string s);
};

#include "Tree.h"
#include "Token.h"
#include "Node.h"

#include <cmath>
#include <iostream>



template <typename T>
T dOperatorDispatcher(Node* node, std::vector<T> arguments) {
	std::string lexeme = node->sGetTokenLexeme();
	if (arguments.size() == 2) {
		if (lexeme == "+") return arguments[0] + arguments[1];
		if (lexeme == "-") return arguments[0] - arguments[1];
		if (lexeme == "*") return arguments[0] * arguments[1];
		if (lexeme == "/") return arguments[0] / arguments[1];
	} else if (arguments.size() == 1) {
		if (lexeme == "sin") return std::sin(arguments[0]);
		if (lexeme == "cos") return std::cos(arguments[0]);
	}
	throw std::exception("Unknown operator");
}

template <>
std::string dOperatorDispatcher(Node* node, std::vector<std::string> arguments) {
	std::string lexeme = node->sGetTokenLexeme();
	if (arguments.size() == 2) {
		if (lexeme == "+") return arguments[0] + arguments[1];
		if (lexeme == "-") { // find last occurence of arguments[1] in arguments[0]
			if (arguments[1] == "") return arguments[0];
			int pos = arguments[0].rfind(arguments[1]);
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
					i += s_sub.size();
				}
			}
			return s_result;
		}
	}
	throw std::exception("Unknown operator");
}

template <>
double Evaluator<double>::stot(std::string s_lexeme) {
	return std::stod(s_lexeme);
}

template <>
int Evaluator<int>::stot(std::string s_lexeme) {
	return  std::stoi(s_lexeme);
}

template <>
std::string Evaluator<std::string>::stot(std::string s_lexeme) {
	return s_lexeme;
}


template <typename T>
T Evaluator<T>::dEvaluateHelper(Node* pc_current_node, std::map<std::string, T> map_vars) {
	std::vector<T> arguments;
	switch (pc_current_node->eGetTokenType()) {
	case E_TOKEN_TYPE::VALUE:
		return this->stot(pc_current_node->sGetTokenLexeme());
	case E_TOKEN_TYPE::VARIABLE:
		return map_vars[pc_current_node->sGetTokenLexeme()];
	case E_TOKEN_TYPE::STRING:
		return pc_current_node->sGetTokenLexeme();
	case E_TOKEN_TYPE::OPERATOR:
		for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
			arguments.push_back(dEvaluateHelper(pc_current_node->pcGetChild(i), map_vars));
		}
		return dOperatorDispatcher(pc_current_node, arguments);
	case E_TOKEN_TYPE::UNKNOWN:
		throw std::exception("Unknown token type");
	}
}

template <typename T>
T Evaluator<T>::dEvaluateTree(Tree* tree, std::map<std::string, T> map_vars) {
	Node* current_node = tree->pcGetRoot();
	return dEvaluateHelper(current_node, map_vars);
}

template <>
std::string Evaluator<std::string>::dEvaluateTree(Tree* tree, std::map<std::string, std::string> map_vars) {
	Node* current_node = tree->pcGetRoot();
	return '"' + dEvaluateHelper(current_node, map_vars) + '"';
}


