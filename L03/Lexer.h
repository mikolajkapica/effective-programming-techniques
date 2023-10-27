#pragma once
#include <string> 
#include <vector>

class Token;

class Lexer {
public:
	Lexer(std::string s_input) : s_input(s_input) {}
	std::vector<Token*> vecLex();
private:
	std::string s_input;
};

