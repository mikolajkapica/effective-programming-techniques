#pragma once

#include "token.h"
#include "errors.h"

#include <vector>
#include <string>
#include <utility>

template <typename T>
class Node {
private:
	Token<T> *pc_token;
	Node<T> *pc_parent;
	std::vector<Node*> vec_children;
public:
	Node(Token<T>* token);
	~Node();
	inline std::vector<Node*> vecGetChildren() { return this->vec_children; };
	inline Node* pcGetNthChild(int n) { return this->vec_children[n]; };
	inline Node* pcGetParent() { return this->pc_parent; };
	inline void vSetNthChild(int n, Node* pc_node) { this->vec_children[n] = pc_node; pc_node->pc_parent = this; };
	inline int iGetChildrenCount() { return (int)this->vec_children.size(); };
	inline std::string sGetTokenLexeme() { return this->pc_token->sGetLexeme(); };
	inline ETokenType eGetTokenType() { return this->pc_token->eGetTokenType(); };
	inline T tGetTokenValue() { return this->pc_token->tGetValue(); };
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

template <>
std::string Node<std::string>::toString() {
	if (this->pc_token->eGetTokenType() == ETokenType::CONSTANT) {
		return "\"" + this->pc_token->sGetLexeme() + "\"";
	}
	return this->pc_token->sGetLexeme();
}

template <typename T>
class Tree {
private:
	Node<T>* pc_root;
public:
	Tree() : pc_root(NULL) {}
	~Tree();
	Node<T>* pcGetRoot() { return this->pc_root; };
	MyError pcInsert(Node<T>* pc_node);
	std::vector<std::string> vecGetVariables();
	void operator+=(Tree<T>* pc_tree);
	std::string toString();
	void operator=(Tree<T>&& pc_tree) noexcept {
		this->pc_root = pc_tree.pc_root;
		pc_tree.pc_root = NULL;
	}
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
			return MyError();
		} 

		// SEE IF A CHILD CAN HAVE A CHILD
		MyError m_error = pcInsertAux(pc_node, pc_child_node);

		// IF SO, RETURN
		if (!m_error.bHasErrors()) {
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
		return MyError();
	} 

	// OTHER NODES INSERTION
	return pcInsertAux<T>(pc_node, this->pc_root);
}

template <typename T>
void vJoinAux(Node<T>* pc_node, Tree<T>* pc_other) {
	int children_count = (int)pc_node->iGetChildrenCount();
	if (children_count == 0) {
		pc_node->pcGetParent()->vSetNthChild((pc_node->pcGetParent()->iGetChildrenCount() - 1), pc_other->pcGetRoot());
	} else {
		vJoinAux(pc_node->pcGetNthChild(children_count - 1), pc_other);
	}
}

template <typename T>
std::vector<std::string> vecGetVariablesAux(Node<T>* pc_current_node, std::vector<std::string> vec_variables) {
	for (int i = 0; i < pc_current_node->iGetChildrenCount(); i++) {
		Node<T>* pc_child_node = pc_current_node->pcGetNthChild(i);
		if (pc_child_node->eGetTokenType() == ETokenType::VARIABLE) {
			vec_variables.push_back(pc_child_node->sGetTokenLexeme());
		}
		else {
			vec_variables = vecGetVariablesAux(pc_child_node, vec_variables);
		}
	}
	return vec_variables;
}

template <typename T>
std::vector<std::string> Tree<T>::vecGetVariables() {
	std::vector<std::string> vec_variables;
	std::vector<std::string> vec_variables_aux = vecGetVariablesAux(this->pc_root, vec_variables);
	for (int i = 0; i < vec_variables_aux.size(); i++) {
		bool b_found = false;
		for (int j = 0; j < vec_variables.size(); j++) {
			if (vec_variables_aux[i] == vec_variables[j]) {
				b_found = true;
				break;
			}
		}
		if (!b_found) {
			vec_variables.push_back(vec_variables_aux[i]);
		}
	}
	return vec_variables;
}

template <typename T>
void Tree<T>::operator+=(Tree<T>* pc_tree) {
	vJoinAux(this->pc_root, pc_tree);
}

template <typename T>
std::string toStringAux(Node<T> *pc_current_node) {
	if (pc_current_node == NULL) {
		return "";
	}
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
