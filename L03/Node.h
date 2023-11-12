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
