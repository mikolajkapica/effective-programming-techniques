#include "Node.h"
#include "Token.h"

#include <iostream>

Node::Node(Token* apc_token) {
	this->pc_token = apc_token;
	this->pc_parent = nullptr;
	this->v_children = std::vector<Node*>(apc_token->iGetArgumentsCount(), NULL);
	this->i_empty_children_count = apc_token->iGetArgumentsCount();
}

Node::~Node() {
	delete this->pc_token; 
	for (int i = 0; i < v_children.size(); i++) { 
		delete v_children[i]; 
	} 
}

std::string Node::sGetTokensLexeme() {
	return this->pc_token->sGetLexeme();
}

E_TOKEN_TYPE Node::eGetTokenType() {
	return this->pc_token->cGetTokenType();
}
