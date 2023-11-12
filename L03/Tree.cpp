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
	for (int i = 0; i < level; i++) {
		s_out += " ";
	}

	s_out += pc_current_node->sToString();

	for (int i = 0; i < pc_current_node->vecGetChildren().size(); i++) {
		Node *pc_child_node = pc_current_node->pcGetChild(i);
		if (pc_child_node != NULL) s_out += toStringAux(pc_child_node, level + 1);
	}
	return s_out;
}

std::string Tree::sToString() {
	return toStringAux(pc_root, 0);
}

void Tree::operator+=(Tree *tree) {
	Node *pc_current_node = this->pcGetRoot();
	if (pc_current_node == NULL) {
		this->pc_root = tree->pcGetRoot();
		std::cout << "root is null\n" << std::endl;
		return;
	}
	while (pc_current_node->pcGetChild(0) != NULL)
		pc_current_node = pc_current_node->pcGetChild(0);
	pc_current_node = pc_current_node->pcGetParent();
	pc_current_node->vSetChild(0, tree->pcGetRoot());
}
