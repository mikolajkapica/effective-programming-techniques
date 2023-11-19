#pragma once
#include <string>
#include <vector>
#include "Errors.h"

class Parser;
class Token;
class Node;


class Tree {
public:
    Tree() : pc_root(NULL) {}
    ~Tree();
    Tree(Tree *tree);
    E_ERROR_TYPE pcInsert(Token* token);
    Node *pcGetRoot() { return pc_root; }
    std::string sToString();
    Tree* operator+(Tree *tree);
    std::vector<std::string> vecGetVariables();
private:
    E_ERROR_TYPE pcInsertAux(Node* node, Node* pc_current_node);
    Node* pc_root;
};  
