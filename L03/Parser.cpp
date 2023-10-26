#include "Parser.h"
#include <iostream>

bool hasALetter(std::string t) {
	for (int i = 0; i < t.length(); i++) {
		if (isalpha(t[i])) {
			return true;
		}
	}
	return false;
}

bool isVariableOrFunction(std::string &t) {
	if (!hasALetter(t)) {
		return false;
	}
	int current_letter = 0;
	for (int i = 0; current_letter < t.length(); i++) {
		if (!isalpha(t[i]) && !isdigit(t[i])) {
			std::cout << "Invalid variable or function name: " << t << " found character: " << t[i] << std::endl;
			t = t.substr(0, i) + t.substr(i + 1, t.length());
			i--;
		}
		current_letter++;
	}
	return true;
}

bool isNumber(std::string t) {
	for (int i = 0; i < t.length(); i++) {
		if (!isdigit(t[i])) {
			return false;
		}
	}
	return true;
}

E_TOKEN_TYPE type(std::string &t) {
	if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^") {
		return OPERATOR;
	} else if (isVariableOrFunction(t)) {
		return VARIABLE_OR_FUNCTION;
	} else if (isNumber(t)) {
		return NUMBER;
	} else {
		std::cout << "Invalid token: " << t << std::endl;
		throw std::exception("Invalid token");
	}
}

void Parser::lex() {
	int i_start_word = 0;
	for (int i = 0; i < this->s_input.length(); i++) {
		if (this->s_input[i] == ' ') {
			std::string s_lexeme = this->s_input.substr(i_start_word, i - i_start_word);
			E_TOKEN_TYPE e_type = type(s_lexeme);
			this->v_tokens.push_back(new Token(e_type, s_lexeme));
			i_start_word = i+1;
		}
	}
}

void Parser::parse() {
}

std::string Token::sToString() {
	E_TOKEN_TYPE e_type = this->cGetTokenType();
	std::string s_type;
	switch (e_type) {
		case E_TOKEN_TYPE::OPERATOR: s_type = "OPERATOR"; break;
		case E_TOKEN_TYPE::NUMBER: s_type = "NUMBER"; break;
		case E_TOKEN_TYPE::VARIABLE_OR_FUNCTION: s_type = "VARIABLE_OR_FUNCTION"; break;
		case E_TOKEN_TYPE::VARIABLE: s_type = "VARIABLE"; break;
		case E_TOKEN_TYPE::FUNCTION: s_type = "FUNCTION"; break;
	}
	return "Token: [" + this->s_lexeme + "] [" + s_type + "]\n";
}

