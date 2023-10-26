#pragma once
#include "Tree.h"
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

enum E_TOKEN_TYPE {
	OPERATOR,
	NUMBER,
	VARIABLE_OR_FUNCTION,
	VARIABLE,
	FUNCTION
};

class Token {
public:
	Token(E_TOKEN_TYPE e_type, std::string s_lexeme) {
		this->e_type = e_type;
		this->s_lexeme = s_lexeme;
		this->i_arguments_count = 0;
	}
	E_TOKEN_TYPE cGetTokenType() { return this->e_type; }
	std::string sGetLexeme() { return this->s_lexeme; }
	std::string sToString();
	int iGetArgumentsCount() { return this->i_arguments_count; }
private:
	E_TOKEN_TYPE e_type;
	std::string s_lexeme;
	int i_arguments_count;
};

class Parser {
public:
	Parser(std::string s_input) : s_input(s_input) {}

	void lex();
	void parse();

	std::vector<Token*> getTokens() { return this->v_tokens; }
private:
	std::string s_input;
	std::vector<Token*> v_tokens;
	Tree *pc_tree;
};

