#include "Parser.h"
#include "Tree.h"
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



data_type type(std::string &t) {
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

void Parser::parse() {
	if (this->tokens.size() == 0) {
		std::cout << "No tokens to parse" << std::endl;
		throw std::exception("No tokens to parse");
	}
	BinaryTree tree = BinaryTree();
	for (int i = 0; i < this->tokens.size(); i++) {
		if (type(this->tokens[i]) == OPERATOR) {
			tree.insert(this->tokens[i]);
		}
		else if (type(this->tokens[i]) == NUMBER) {
			tree.insert(this->tokens[i]);
		}
		else if (type(this->tokens[i]) == VARIABLE_OR_FUNCTION) {
			tree.insert(this->tokens[i]);
		}
	}

	
}

void Parser::lex() {
	int i_last_word_end = 0;
	for (int i = 0; i < strlen(this->input); i++) {
		if (this->input[i] == ' ') {
			this->tokens.push_back(std::string(this->input + i_last_word_end, i - i_last_word_end));
			i_last_word_end = i;
		}
	}
}

