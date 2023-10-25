#pragma once
#include <vector>
#include <string>

enum data_type {
	OPERATOR,
	NUMBER,
	VARIABLE_OR_FUNCTION,
	VARIABLE,
	FUNCTION
};

class Parser {
public:
	Parser(const char* input) : input(input) {}
	void lex();
	void parse();
	std::vector<std::string, data_type> getTokens() { return this->tokens; }

private:
	std::vector<std::string, data_type> tokens;
	const char* input;
};

