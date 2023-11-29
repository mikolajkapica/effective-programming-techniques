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
	Tree(const Node<T>* pc_root);
	~Tree();
	Node<T>* pcGetRoot() { return this->pc_root; };
	MyError pcInsert(Node<T>* pc_node);
	std::vector<std::string> vecGetVariables();
	void operator+=(Tree<T>* pc_tree);
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

template <typename T>
class Parser {
public: 
	std::pair<MyError, Tree<T>*> pParse(std::vector<Token<T>*> vec_tokens);
};

template <typename T>
bool vCorrectTree(Node<T>* current_node, Node<T> *parent, int i_child_number, bool b_changed) {
	if (current_node == NULL) {
		b_changed = true;
		Token<T> *token = new Token<T>(ETokenType::CONSTANT, T(), "0");
		current_node = new Node<T>(token);
		parent->vSetNthChild(i_child_number, current_node);
	} else {
		for (int i = 0; i < current_node->vecGetChildren().size(); i++) {
			bool b_change_rec = vCorrectTree(current_node->pcGetNthChild(i), current_node, i, b_changed);
			if (b_change_rec) {
				b_changed = true;
			}
		}
	}
	return b_changed;
}

template <typename T>
std::pair<MyError, Tree<T>*> Parser<T>::pParse(std::vector<Token<T>*> vec_tokens) {
	MyError e_error;
	Tree<T>* tree = new Tree<T>();
	std::vector<Node<T>*> vec_nodes;

	for (int i = 0; i < vec_tokens.size(); i++) {
		vec_nodes.push_back(new Node<T>(vec_tokens[i]));
	}

	for (int i = 0; i < vec_nodes.size(); i++) {
		MyError c_insert_errors = tree->pcInsert(vec_nodes[i]);
		if (c_insert_errors.bHasErrors()) {
			return std::make_pair(c_insert_errors, nullptr);
		}
		e_error += c_insert_errors;
	}

	if (vCorrectTree<T>(tree->pcGetRoot(), nullptr, 0, false)) {
		return std::make_pair(e_error + MyError(EWarning::TREE_HAD_TO_BE_FIXED), tree);
	}

	return std::make_pair(e_error, tree);
}
