#include <iostream>

#include "Lexer.h"
#include "Token.h"

bool hasALetter(std::string t) {
	for (int i = 0; i < t.length(); i++) {
		if (isalpha(t[i])) {
			return true;
		}
	}
	return false;
}

bool isVariable(std::string &t) {
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

E_TOKEN_TYPE type(std::string& t) {
	if (t == "+" || t == "-" ||
		t == "*" || t == "/" ||
	    t == "sin" || t == "cos") {
		return OPERATOR;
	} else if (isVariable(t)) {
		return VARIABLE;
	} else if (isNumber(t)) {
		return NUMBER;
	} else {
		std::cout << "Invalid token: " << t << std::endl;
		throw std::exception("Invalid token");
	}
}

int getNumberOfArguments(std::string& t) {
	if (t == "+" || t == "-" ||
		t == "*" || t == "/") {
		return 2;
	}
	else if (t == "sin" || t == "cos") {
		return 1;
	}
	else {
		std::cout << "Invalid token: " << t << std::endl;
		throw std::exception("Invalid token");
	}
}	

std::vector<Token*> Lexer::vecLex() {
	std::vector<Token*> v_tokens;
	bool copying = false;
	int i_start_word;
	for (int i = 0; i < this->s_input.length(); i++) {
		if (!copying && this->s_input[i] != ' ') {
			copying = true;
			i_start_word = i;
		} else if (this->s_input[i] == ' ') {
			std::string s_lexeme = s_input.substr(i_start_word, i - i_start_word);
			E_TOKEN_TYPE e_type = type(s_lexeme);
			if (e_type == OPERATOR) {
				v_tokens.push_back(new Token(e_type, s_lexeme, getNumberOfArguments(s_lexeme)));
			} else {
				v_tokens.push_back(new Token(e_type, s_lexeme));
			}
			i_start_word = i+1;
			copying = false;
		}
	}
	if (copying) {
			std::string s_lexeme = s_input.substr(i_start_word, this->s_input.length() - i_start_word);
			E_TOKEN_TYPE e_type = type(s_lexeme);
			if (e_type == OPERATOR) {
				v_tokens.push_back(new Token(e_type, s_lexeme, getNumberOfArguments(s_lexeme)));
			} else {
				v_tokens.push_back(new Token(e_type, s_lexeme));
			}
	}
	return v_tokens;
}
