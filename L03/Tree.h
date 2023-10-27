#pragma once
#include <string>
#include <vector>

class Parser;
class Token;
class Node;


class Tree {
public:
    Tree() : pc_root(NULL), pc_current_node(pc_root) {}
    ~Tree();
    void pcInsert(Node* node);
    void pcInsert(Token* token);
    std::vector<std::string> vecGetVariables();
    std::string sToString();
    Node *pcGetRoot() { return pc_root; }
private:
    Node* pc_root;
    Node *pc_current_node;
};  
