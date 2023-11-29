#pragma once
#include <string>
#include <vector>
#include "Errors.h"

class Parser;
class Token;
class Node;


class Tree {
public:
    Tree() : pc_root(NULL) {}
    ~Tree();
    Tree(const Tree *tree);
    E_ERROR_TYPE pcInsert(Token* token);
    Node *pcGetRoot() { return pc_root; }
    std::string sToString();
    Tree* operator+(Tree *tree);
    std::vector<std::string> vecGetVariables();
private:
    E_ERROR_TYPE pcInsertAux(Node* node, Node* pc_current_node);
    Node* pc_root;
};  

#include <iostream>
#include <set>

#include "Parser.h"
#include "Token.h"
#include "Node.h"
#include "Errors.h"

#define DEBUG false

Tree::~Tree() {
	delete this->pc_root;
}

void vCopyAux(Node* pc_current_node, Node* pc_other) {
	for (int i = 0; i < pc_other->vecGetChildren().size(); i++) {
		Node* pc_child_node = pc_other->pcGetChild(i);
		if (pc_child_node != NULL) {
			pc_current_node->vSetChild(i, new Node(pc_child_node->pcGetToken()));
			vCopyAux(pc_current_node->pcGetChild(i), pc_child_node);
		}
	}
}

Tree::Tree(const Tree *pc_tree) {
	this->pc_root = new Node(pc_tree->pc_root->pcGetToken());
	vCopyAux(this->pc_root, pc_tree->pc_root);
}


E_ERROR_TYPE Tree::pcInsertAux(Node* node, Node* pc_current_node) {
	for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
		Node* pc_child_node = pc_current_node->pcGetChild(i);

		// CHILD IS NULL
		if (pc_child_node == NULL) {
			pc_current_node->vSetChild(i, node);
			return E_ERROR_TYPE::NO_ERROR;
		} 

		// SEE IF A CHILD CAN HAVE A CHILD
		E_ERROR_TYPE e_type = pcInsertAux(node, pc_child_node);

		// IF SO, RETURN
		if (e_type == E_ERROR_TYPE::NO_ERROR) {
			return E_ERROR_TYPE::NO_ERROR;
		}
		// ELSE LOOK FOR ANOTHER CHILD
	}
	// NO CHILD CAN HAVE A CHILD
	return E_ERROR_TYPE::PARSING_PROBLEM;
}


E_ERROR_TYPE Tree::pcInsert(Token* token) {
	Node *node = new Node(token);

	// FIRST NODE INSERTION
	if (this->pc_root == NULL) {
		this->pc_root = node;
		return E_ERROR_TYPE::NO_ERROR;
	} 

	// OTHER NODES INSERTION
	return this->pcInsertAux(node, this->pc_root);
}

std::string toStringAux(Node* pc_current_node, int level) {
	std::string s_out = "";
	if (DEBUG) {
		for (int i = 0; i < level; i++) {
			s_out += " ";
		}

		s_out += pc_current_node->sToString();

		for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
			Node *pc_child_node = pc_current_node->pcGetChild(i);
			if (pc_child_node != NULL) s_out += toStringAux(pc_child_node, level + 1);
		}
		return s_out;
	} else {
		if (pc_current_node->pcGetToken()->cGetTokenType() == STRING) {
			s_out += '"' + pc_current_node->sGetTokenLexeme() + '"' + " ";
		} else {
			s_out += pc_current_node->sGetTokenLexeme() + " ";
		}

		for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
			Node *pc_child_node = pc_current_node->pcGetChild(i);
			if (pc_child_node != NULL) s_out += toStringAux(pc_child_node, level + 1);
		}
		return s_out;
	}

}

std::string Tree::sToString() {
	return toStringAux(pc_root, 0);
}

void vJoinAux(Node* pc_node, Tree* pc_other) {
	int children_count = pc_node->iGetChildrenCount();
	if (children_count == 0) {
		pc_node->pcGetParent()->vSetChild(pc_node->pcGetParent()->iGetChildrenCount() - 1, pc_other->pcGetRoot());
	} else {
		vJoinAux(pc_node->pcGetChild(children_count - 1), pc_other);
	}
}

Tree* Tree::operator+(Tree *tree) {
	Tree* pc_copy_this = new Tree(this);
	vJoinAux(pc_copy_this->pcGetRoot(), tree);
	return pc_copy_this;
}

std::set<std::string> setGetVariablesAux(Node* pc_current_node) {
	std::set<std::string> set_variables;
	for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
		Node *pc_child_node = pc_current_node->pcGetChild(i);
		if (pc_child_node != NULL) {
			if (pc_child_node->eGetTokenType() == E_TOKEN_TYPE::VARIABLE) {
				set_variables.insert(pc_child_node->sGetTokenLexeme());
			}
			std::set<std::string> set_child_variables = setGetVariablesAux(pc_child_node);
			set_variables.insert(set_child_variables.begin(), set_child_variables.end());
		}
	}
	return set_variables;
}

std::vector<std::string> Tree::vecGetVariables() {
	std::set<std::string> set_variables = setGetVariablesAux(this->pcGetRoot());
	return std::vector<std::string>(set_variables.begin(), set_variables.end());
}

