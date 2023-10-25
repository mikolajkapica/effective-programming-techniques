#pragma once
#include <iostream>
#include <string>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
    ~Node() {
		delete left;
		delete right;
	}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        delete this->root;
    }

    Node* insert(Node *node, std::string value);
    void insert(std::string value);
    std::string toString();
    std::string inorderTraversal(Node *root);
private:
    Node* root;
};