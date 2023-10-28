#include <iostream>
#include <set>

#include "Tree.h"
#include "Parser.h"
#include "Token.h"
#include "Node.h"
#include "Errors.h"

Tree::~Tree() {
	delete this->pc_root;
}

E_ERROR_TYPE Tree::pcInsertAux(Token *token, Node* pc_current_node) {
	Node *node = new Node(token);
	if (this->pc_root == NULL) {
		this->pc_root = node;
		pc_current_node = node;
		return E_ERROR_TYPE::NO_ERROR;
	} 
	for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
		Node* pc_child_node = pc_current_node->pcGetChild(i);
		if (pc_child_node == NULL) {
			pc_current_node->vSetChild(i, node);
			return E_ERROR_TYPE::NO_ERROR;
		} else if (pc_child_node->iGetEmptyChildrenCount() > 0) {
			this->pcInsertAux(token, pc_child_node);
			return E_ERROR_TYPE::NO_ERROR;
		}
	}
	if (pc_current_node->pcGetParent() == NULL) {
		return E_ERROR_TYPE::PARSING_PROBLEM;
	}
	this->pcInsertAux(token, pc_current_node->pcGetParent());
}

E_ERROR_TYPE Tree::pcInsert(Token* token) {
	return this->pcInsertAux(token, this->pc_root);
}

std::string toStringAux(Node* pc_current_node) {
	std::string s_out = pc_current_node->sGetTokensLexeme() + " ";
	for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
		Node *pc_child_node = pc_current_node->pcGetChild(i);
		if (pc_child_node != NULL) s_out += toStringAux(pc_child_node);
	}
	return s_out;
}

std::string Tree::sToString() {
	return toStringAux(pc_root);
}
