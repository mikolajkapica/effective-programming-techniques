#include <iostream>
#include <set>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Node.h"

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
			t = t.substr(0, i) + t.substr(i + 1, t.length() - i - 1);
			i--;
		} else {
			current_letter++;
		}
	}
	return true;
}

bool isNumber(std::string t) {
	bool has_dot = false;
	for (int i = 0; i < t.length(); i++) {
		if (t[i] == '.') {
			if (has_dot) return false;
			has_dot = true;
		} else if (!isdigit(t[i])) {
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
		return UNKNOWN;
	}
}

int getNumberOfArguments(std::string& t) {
	if (t == "+" || t == "-" || t == "*" || t == "/") return 2;
	else if (t == "sin" || t == "cos") return 1;
	else return 0;
}	

std::pair<std::vector<Token*>, E_ERROR_TYPE> Parser::vecTokenize() {
	std::vector<Token*> v_tokens;
	int i_start_word;
	for (int i = 0; i < this->s_input.length(); i++) {
		if (this->s_input[i] != ' ') {
			i_start_word = i;
			while (i < this->s_input.length() && this->s_input[i] != ' ') i++;
			std::string s_lexeme = s_input.substr(i_start_word, i - i_start_word);
			E_TOKEN_TYPE e_type = type(s_lexeme);
			if (e_type == E_TOKEN_TYPE::UNKNOWN) {
				return std::make_pair(v_tokens, E_ERROR_TYPE::INVALID_TOKEN);
			}
			v_tokens.push_back(new Token(e_type, s_lexeme, getNumberOfArguments(s_lexeme)));
		} 
	}
	return std::make_pair(v_tokens, E_ERROR_TYPE::NO_ERROR);
}

void vCorrectTree(Node* current_node, Node *parent, int i_child_number) {
	if (current_node == NULL) {
		Token *token = new Token(E_TOKEN_TYPE::NUMBER, "1", 0);
		current_node = new Node(token);
		parent->vSetChild(i_child_number, current_node);
	} else {
		for (int i = 0; i < current_node->vecGetChildren().size(); i++) {
			vCorrectTree(current_node->pcGetChild(i), current_node, i);
		}
	}
}

Tree *Parser::pcParse(std::vector<Token*> vec_tokens) {
	Tree *tree = new Tree();
	std::set<std::string> set_variables;
	for (int i = 0; i < vec_tokens.size(); i++) {
		if (vec_tokens[i]->cGetTokenType() == E_TOKEN_TYPE::VARIABLE) {
			set_variables.insert(vec_tokens[i]->sGetLexeme());
		}
		E_ERROR_TYPE e_err = tree->pcInsert(vec_tokens[i]);
		if (e_err != E_ERROR_TYPE::NO_ERROR) {
			return NULL;
		}
	}
	vCorrectTree(tree->pcGetRoot(), NULL, 0);
	this->vec_variables = std::vector<std::string>(set_variables.begin(), set_variables.end());
	return tree;
}


