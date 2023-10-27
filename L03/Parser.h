#pragma once
#include <string>
#include <vector>

class Tree;
class Token;

class Parser {
public:
	Parser() {};
	Tree *pcParse(std::vector<Token*> vec_tokens);
	std::vector<std::string> vecGetVariables();
private:
};

