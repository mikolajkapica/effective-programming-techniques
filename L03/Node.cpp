#include "Node.h"
#include "Token.h"

#include <iostream>

Node::Node(Token* apc_token) {
	this->pc_token = apc_token;
	this->pc_parent = NULL;
	this->vec_children = std::vector<Node*>(apc_token->iGetArgumentsCount(), NULL);
	this->i_empty_children_count = apc_token->iGetArgumentsCount();
}

Node::~Node() {
	delete this->pc_token; 
	for (int i = 0; i < vec_children.size(); i++) { 
		delete vec_children[i]; 
	} 
}

std::string Node::sGetTokensLexeme() {
	return this->pc_token->sGetLexeme();
}

E_TOKEN_TYPE Node::eGetTokenType() {
	return this->pc_token->cGetTokenType();
}

void Node::vSetChild(int i_index, Node* node) {
	this->vec_children[i_index] = node;
	this->i_empty_children_count--;
	this->pc_parent = this;
}
