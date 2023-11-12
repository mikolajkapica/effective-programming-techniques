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

std::string Node::sGetTokenLexeme() {
	return this->pc_token->sGetLexeme();
}

E_TOKEN_TYPE Node::eGetTokenType() {
	return this->pc_token->cGetTokenType();
}

void Node::vSetChild(int i_index, Node* node) {
	this->vec_children[i_index] = node;
	this->i_empty_children_count--;
	this->i_children_count++;
	node->pc_parent = this;
}

std::string Node::sToString() {
	std::string s_parent = this->pc_parent == NULL ? "NULL" : this->pc_parent->sGetTokenLexeme();
	std::string s_token_info = this->pcGetToken()->sToString();
	return "Node " + s_token_info.substr(7, s_token_info.length() - 1) + " Parent=[" + s_parent + "]\n";
}
