#include <iostream>
#include <set>
#include <utility>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Node.h"
#include "VariablesUtitlities.h"

E_TOKEN_TYPE type(std::string &t, std::string &s_out) {
	std::string s_original = t;
	E_ERROR_TYPE e_var = isVariable(t);
	if (t == "+" || t == "-" ||
		t == "*" || t == "/" ||
	    t == "sin" || t == "cos") {
		return OPERATOR;
	} else if (e_var == E_ERROR_TYPE::NO_ERROR) {
		return VARIABLE;
	} else if (e_var == E_ERROR_TYPE::INVALID_CHARACTERS) {
		s_out += "'" + s_original + "' variable had to be changed to '" + t + "'\n";
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

std::pair<std::vector<Token*>, E_ERROR_TYPE> Parser::vecTokenize(std::string s_input, std::string &s_out) {
	std::vector<Token*> v_tokens;
	int i_start_word;
	for (int i = 0; i < s_input.length(); i++) {
		if (s_input[i] != ' ') {
			i_start_word = i;
			while (i < s_input.length() && s_input[i] != ' ') i++;
			std::string s_lexeme = s_input.substr(i_start_word, i - i_start_word);
			E_TOKEN_TYPE e_type = type(s_lexeme, s_out);
			if (e_type == E_TOKEN_TYPE::UNKNOWN) {
				return std::make_pair(v_tokens, E_ERROR_TYPE::INVALID_TOKEN);
			}
			v_tokens.push_back(new Token(e_type, s_lexeme, getNumberOfArguments(s_lexeme)));
		} 
	}
	return std::make_pair(v_tokens, E_ERROR_TYPE::NO_ERROR);
}

bool vCorrectTree(Node* current_node, Node *parent, int i_child_number, bool b_changed) {
	if (current_node == NULL) {
		b_changed = true;
		Token *token = new Token(E_TOKEN_TYPE::NUMBER, "1", 0);
		current_node = new Node(token);
		parent->vSetChild(i_child_number, current_node);
	} else {
		for (int i = 0; i < current_node->vecGetChildren().size(); i++) {
			bool b_change_rec = vCorrectTree(current_node->pcGetChild(i), current_node, i, b_changed);
			if (b_change_rec) {
				b_changed = true;
			}
		}
	}
	return b_changed;
}

std::pair<Tree *, E_ERROR_TYPE> Parser::pcParse(std::vector<Token*> vec_tokens) {

	Tree *tree = new Tree();
	std::set<std::string> set_variables;

	for (int i = 0; i < vec_tokens.size(); i++) {
		Token *t_current = vec_tokens[i];

		// ADD VARIABLES TO SET
		if (t_current->cGetTokenType() == E_TOKEN_TYPE::VARIABLE) {
			set_variables.insert(t_current->sGetLexeme());
		}

		// INSERT TOKEN INTO TREE
		E_ERROR_TYPE e_err = tree->pcInsert(t_current);

		// IF ERROR OCCURED
		if (e_err != E_ERROR_TYPE::NO_ERROR) {
			return std::make_pair(tree, e_err);
		}
	}

	// UPDATE TREE WITH MISSING NODES (1)
	bool b_changed = vCorrectTree(tree->pcGetRoot(), NULL, 0, false);

	// CHANGE SET TO VECTOR AND ASSIGN IT TO this->vec_variables
	this->vec_variables = std::vector<std::string>(set_variables.begin(), set_variables.end());

	if (b_changed) {
		return std::make_pair(tree, E_ERROR_TYPE::TREE_CORRECTED);
	}
	return std::make_pair(tree, E_ERROR_TYPE::NO_ERROR);
}


