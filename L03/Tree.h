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
    E_ERROR_TYPE pcInsert(Token* token);
    Node *pcGetRoot() { return pc_root; }
    std::string sToString();
private:
    E_ERROR_TYPE pcInsertAux(Token* token, Node* pc_current_node);
    Node* pc_root;
};  
