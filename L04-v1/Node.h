#pragma once
#include <string>
#include <vector>

class Token;
enum E_TOKEN_TYPE;

class Node {
public:
    Node(Token* apc_token);
    ~Node();

    Node* pcGetParent() { return this->pc_parent; }
    std::vector<Node*> vecGetChildren() { return this->vec_children; }
	Node *pcGetChild(int i_index) { return this->vec_children[i_index]; }
    int iGetChildrenCount() { return this->i_children_count; }
    int iGetEmptyChildrenCount() { return this->i_empty_children_count; }
    Token* pcGetToken() { return this->pc_token; }
    std::string sGetTokenLexeme();
    E_TOKEN_TYPE eGetTokenType();
    void vSetChild(int i_index, Node* node);
    std::string sToString();
private:
    Node *pc_parent;
    Token *pc_token;
    std::vector<Node*> vec_children;
    int i_children_count;
    int i_empty_children_count;
};

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
	const int i_prefix_length = 7;
	return "Node " + s_token_info.substr(i_prefix_length, s_token_info.length() - 1) + " Parent=[" + s_parent + "]\n";
}
