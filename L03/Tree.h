#pragma once
#include "Parser.h"
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    Node(Token* apc_token);
    ~Node() { 
		delete this->pc_token; 
        for (int i = 0; i < v_children.size(); i++) { 
            delete v_children[i]; 
        } 
    }
    Node *pcGetParent() { return this->pc_parent; }
    Token *pcGetToken() { return this->pc_token; }
    std::vector<Node*> vGetChildren() { return this->v_children; }
	Node *pcGetChild(int i_index) { return this->v_children[i_index]; }
    std::string sGetValue() { return this->pc_token->sGetLexeme(); }

private:
    Node *pc_parent;
    Token *pc_token;
    std::vector<Node*> v_children;
};

class Tree {
public:
    Tree() : pc_root(nullptr), pc_current_node(nullptr) {};
    ~Tree() { delete this->pc_root; }
    Node* pcInsert(Node* node);
    std::string sToString();
private:
    Node* pc_root;
    Node* pc_current_node;
};