#pragma once
#include <string>

enum E_TOKEN_TYPE {
	OPERATOR,
	VALUE,
	VARIABLE,
	UNKNOWN,
	STRING
};

class Token {
public:
	Token(E_TOKEN_TYPE e_type, std::string s_lexeme, int i_arguments_count) : e_type(e_type), s_lexeme(s_lexeme), i_arguments_count(i_arguments_count) {}
	E_TOKEN_TYPE cGetTokenType() { return this->e_type; }
	void vSetTokenType(E_TOKEN_TYPE e_type) { this->e_type = e_type; }
	std::string sGetLexeme() { return this->s_lexeme; }
	int iGetArgumentsCount() { return this->i_arguments_count; }
	void vSetArgumentsCount(int i_arguments_count) { this->i_arguments_count = i_arguments_count; }
	void vIncrementArgumentsCount() { this->i_arguments_count++; }
	std::string sToString();
private:
	E_TOKEN_TYPE e_type;
	std::string s_lexeme;
	int i_arguments_count;
};

std::string Token::sToString() {
	E_TOKEN_TYPE e_type = this->cGetTokenType();
	std::string s_type;
	switch (e_type) {
		case E_TOKEN_TYPE::OPERATOR: s_type = "OPERATOR"; break;
		case E_TOKEN_TYPE::VALUE: s_type = "NUMBER"; break;
		case E_TOKEN_TYPE::STRING: s_type = "STRING"; break;
		case E_TOKEN_TYPE::VARIABLE: s_type = "VARIABLE"; break;
	}
	return "Token: [" + this->s_lexeme + "] [" + s_type + "]";
}
