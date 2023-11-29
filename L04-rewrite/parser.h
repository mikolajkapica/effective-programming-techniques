#pragma once

#include "token.h"

#include <vector>
#include <string>

template <typename T>
class Node {
private:
	Token<T> *pc_token;
	std::vector<Node*> vec_children;
public:
	Node(Token<T>* token);
	~Node();
	Node* pcGetNthChild(int n) { return this->vec_children[n]; };
	void vSetNthChild(int n, Node* pc_node) { this->vec_children[n] = pc_node; };
	int iGetChildrenCount() { return this->vec_children.size(); };
	std::string toString();
};

template <typename T>
Node<T>::Node(Token<T>* token) : pc_token(token) {
	for (int i = 0; i < token->iGetArgumentsQuantity(); i++) {
		this->vec_children.push_back(NULL);
	}
}

template <typename T>
Node<T>::~Node() {
	delete this->pc_token; 
	for (int i = 0; i < vec_children.size(); i++) { 
		delete vec_children[i]; 
	} 
}

template <typename T>
std::string Node<T>::toString() {
	return this->pc_token->sGetLexeme();
}

template <typename T>
class Tree {
private:
	Node<T>* pc_root;
	std::vector<std::string> variables;
public:
	Tree() : pc_root(NULL) {}
	Tree(const Node<T>* pc_root);
	~Tree();
	inline std::vector<std::string> vecGetVariables() { return this->variables; };
	MyError pcInsert(Node<T>* pc_node);
	std::string toString();
};

template <typename T>
Tree<T>::~Tree() {
	delete this->pc_root;
}

template <typename T>
MyError pcInsertAux(Node<T>* pc_node, Node<T>* pc_current_node) {
	for (int i = 0; i < pc_current_node->iGetChildrenCount(); i++) {
		Node<T>* pc_child_node = pc_current_node->pcGetNthChild(i);

		// CHILD IS NULL
		if (pc_child_node == NULL) {
			pc_current_node->vSetNthChild(i, pc_node);
			return MyError(EError::NO_ERROR);
		} 

		// SEE IF A CHILD CAN HAVE A CHILD
		MyError m_error = pcInsertAux(pc_node, pc_child_node);

		// IF SO, RETURN
		if (!m_error.isError()) {
			return m_error;
		}
		// ELSE LOOK FOR ANOTHER CHILD
	}
	// NO CHILD CAN HAVE A CHILD
	return MyError(EError::PARSING_PROBLEM);
}

template <typename T>
MyError Tree<T>::pcInsert(Node<T>* pc_node) {
	// FIRST NODE INSERTION
	if (this->pc_root == NULL) {
		this->pc_root = pc_node;
		return MyError(EError::NO_ERROR);
	} 

	// OTHER NODES INSERTION
	return pcInsertAux<T>(pc_node, this->pc_root);
}

template <typename T>
std::string toStringAux(Node<T> *pc_current_node) {
	std::string s_out = "";
	s_out += pc_current_node->toString() + " ";
	for (int i = 0; i < pc_current_node->iGetChildrenCount(); i++) {
		Node<T>* pc_child_node = pc_current_node->pcGetNthChild(i);
		if (pc_child_node != NULL) {
			s_out += toStringAux(pc_child_node);
		}
	}
	return s_out;
}

template <typename T>
std::string Tree<T>::toString() {
	return toStringAux(this->pc_root);
}



// STATIC PROCEDURES 

template <typename T>
std::vector<Node<T>*> vecTokensToNodes(std::vector<Token<T>*> vec_tokens) {
	std::vector<Node<T>*> vec_nodes;
	for (int i = 0; i < vec_tokens.size(); i++) {
		vec_nodes.push_back(new Node<T>(vec_tokens[i]));
	}
	return vec_nodes;
}

template <typename T>
std::pair<MyError, Tree<T>*> pParse(std::vector<Token<T>*> tokens) {
	Tree<T>* tree = new Tree<T>();
	std::vector<Node<T>*> vec_nodes = vecTokensToNodes(tokens);
	for (int i = 0; i < vec_nodes.size(); i++) {
		if (tree->pcInsert(vec_nodes[i]).isError()) {
			return std::make_pair(MyError(EError::TREE_INSERT_ERROR), nullptr);
		}
	}
	return std::make_pair(MyError(EError::NO_ERROR), tree);
}
