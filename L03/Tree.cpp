#include <iostream>
#include <set>

#include "Tree.h"
#include "Parser.h"
#include "Token.h"
#include "Node.h"

Tree::~Tree() {
	delete this->pc_root;
}

void Tree::pcInsert(Node *node) {
	if (this->pc_current_node == NULL) {
		if (this->pc_root == NULL) {
			this->pc_root = node;
			this->pc_current_node = node;
			return;
		} else {
			std::cout << "weird root is not null and current node is null" << std::endl;
		}
	} 
	for (int i = 0; i < pc_current_node->vGetChildren().size(); i++) {
		if (pc_current_node->vGetChildren()[i] == NULL) {
			pc_current_node->vSetChild(i, node);
			node->vSetParent(pc_current_node);
			return;
		} else if (pc_current_node->vGetChildren()[i]->iGetEmptyChildrenCount() > 0) {
			pc_current_node = pc_current_node->vGetChildren()[i];
			pcInsert(node);
			return;
		}
	}
	pc_current_node = pc_current_node->pcGetParent();
	this->pcInsert(node);
}

void Tree::pcInsert(Token* token) {
	return this->pcInsert(new Node(token));
}

std::string toStringAux(Node* pc_current_node, int level) {
	std::string s_out;
	for (int i = 0; i < level; i++) {
		s_out += "|";
	}
	s_out += pc_current_node->sGetTokensLexeme() + "\n";
	for (int i = 0; i < pc_current_node->vGetChildren().size(); i++) {
		if (pc_current_node->vGetChildren()[i] != NULL) {
			s_out += toStringAux(pc_current_node->vGetChildren()[i], level + 1);
		}
	}
	return s_out;
}

std::string Tree::sToString() {
	return toStringAux(pc_root, 0);
}

void vTraverseAddVariables(std::set<std::string> &set_variables, Node* pc_current_node) {
	if (pc_current_node->eGetTokenType() == VARIABLE) {
		set_variables.insert(pc_current_node->sGetTokensLexeme());
	}
	for (int i = 0; i < pc_current_node->vGetChildren().size(); i++) {
		if (pc_current_node->vGetChildren()[i] != NULL) {
			vTraverseAddVariables(set_variables, pc_current_node->vGetChildren()[i]);
		}
	}
}

std::vector<std::string> Tree::vecGetVariables() {
	std::set<std::string> set_variables;
	vTraverseAddVariables(set_variables, this->pc_root);
	return std::vector<std::string>(set_variables.begin(), set_variables.end());
}


