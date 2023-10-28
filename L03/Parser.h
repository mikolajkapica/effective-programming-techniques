#pragma once
#include <string>
#include <vector>

#include "Errors.h"

class Tree;
class Token;
class Node;

class Parser {
public:
	Parser(std::string s_input) : s_input(s_input) {}
	std::pair<std::vector<Token*>, E_ERROR_TYPE> vecTokenize();
	Tree *pcParse(std::vector<Token*> vec_tokens);

	std::vector<std::string> vecGetVariables() { return vec_variables; }
private:
	std::string s_input;
	std::vector<std::string> vec_variables;
};

