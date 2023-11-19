#pragma once
#include <string>
#include <vector>

#include "Errors.h"

class Tree;
class Token;
class Node;

class Parser {
public:
	std::pair<std::vector<Token*>, E_ERROR_TYPE> vecTokenize(std::string s_input, std::string &s_out);
	std::pair<Tree *, E_ERROR_TYPE> pcParse(std::vector<Token*> vec_tokens);

	std::vector<std::string> vecGetVariables() { return vec_variables; }
private:
	std::string s_input;
	std::vector<std::string> vec_variables;
};

