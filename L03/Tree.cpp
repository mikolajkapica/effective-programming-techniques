#include "Tree.h"
#include <iostream>

Node::Node(Token* pc_token) {
	this->pc_token = pc_token;
	this->pc_parent = nullptr;
	this->v_children = std::vector<Node*>(pc_token->iGetArgumentsCount(), nullptr);
}

Node* Tree::pcInsert(Node *node) {
	if (this->pc_root == nullptr) {
		this->pc_root = node;
		this->pc_current_node = node;
		return node;
	}

	for (int i = 0; i < this->pc_current_node->vGetChildren().size(); i++) {
		if (this->pc_current_node->vGetChildren()[i] == nullptr) {
			this->pc_current_node->vGetChildren()[i] = node;
			this->pc_current_node = node;
			return node;
		}
	}

	throw std::exception("Tree is full");
}

std::string Tree::sToString() {
	std::cout << "jha" << std::endl;
	std::cout << this->pc_root->sGetValue() << std::endl;
	for (int i = 0; i < this->pc_root->vGetChildren().size(); i++) {
		std::cout << this->pc_root->vGetChildren()[i]->sGetValue() << std::endl;
		for (int j = 0; j < this->pc_root->vGetChildren()[i]->vGetChildren().size(); j++) {
			std::cout << "| " << this->pc_root->vGetChildren()[i]->vGetChildren()[j]->sGetValue() << std::endl;
			for (int k = 0; k < this->pc_root->vGetChildren()[i]->vGetChildren()[j]->vGetChildren().size(); k++) {
				std::cout << "| | " << this->pc_root->vGetChildren()[i]->vGetChildren()[j]->vGetChildren()[k]->sGetValue() << std::endl;
			}
		}
	}


}

