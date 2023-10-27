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
    Token* pcGetToken() { return this->pc_token; }
    std::vector<Node*> vGetChildren() { return this->v_children; }
	Node *pcGetChild(int i_index) { return this->v_children[i_index]; }
    void vSetChild(int i_index, Node* node) {
		this->v_children[i_index] = node;
		this->i_empty_children_count--;
	}
    int iGetEmptyChildrenCount() { return this->i_empty_children_count; }
    void vSetParent(Node* node) { this->pc_parent = node; }

    std::string sGetTokensLexeme();
    E_TOKEN_TYPE eGetTokenType();
private:
    Node *pc_parent;
    Token *pc_token;
    std::vector<Node*> v_children;
    int i_empty_children_count;
};
