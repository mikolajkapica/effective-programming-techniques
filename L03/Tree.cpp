#include "Tree.h"

Node* BinaryTree::insert(Node* node, std::string value, bool left) {
	if (node == nullptr) {
		return new Node(value);
	}

	if (left) {
		node->left = insert(node->left, value);
	} else {
		node->right = insert(node->right, value);
	}

	return node;
}

void BinaryTree::insert(std::string value) {
	this->root = insert(this->root, value);
}

std::string BinaryTree::toString() {
	return inorderTraversal(this->root);
}

std::string BinaryTree::inorderTraversal(Node *root) {
	std::string out = "";
	if (root != nullptr) {
		out += inorderTraversal(root->left);
		out += std::to_string(root->data) + " ";
		out += inorderTraversal(root->right);
	}
	return out;
}
