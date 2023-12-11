#include <iostream>
#include "CMySmartPointer.h"
#include "tree.h"
#include "token.h"

int main()
{
	CMySmartPointer<int> pc_pointer = new int(5);
	std::cout << pc_pointer.iGetCounter() << std::endl;
	CMySmartPointer<int> pc_pointer2 = pc_pointer;

	std::cout << *pc_pointer << std::endl;
	std::cout << pc_pointer.iGetCounter() << std::endl;
	std::cout << *pc_pointer2 << std::endl;
	std::cout << pc_pointer2.iGetCounter() << std::endl;

	*pc_pointer = 10;
	std::cout << pc_pointer.iGetCounter() << std::endl;

	std::cout << *pc_pointer << std::endl;
	std::cout << *pc_pointer2 << std::endl;

	Tree<int> tree;
	std::cout << "tree.toString() = " << tree.toString() << std::endl;

	Tree<int> tree2;

	MyError e1 = tree.pcInsert(new Node<int>(new Token<int>(ETokenType::OPERATOR, NULL, "+", 2)));
	MyError e2 = tree.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 5, "5")));
	MyError e3 = tree.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 3, "3")));
	std::cout << std::endl;
	std::cout << "Added nodes" << std::endl;
	std::cout << "tree.toString() = " << tree.toString() << std::endl;

	tree2 = std::move(tree);
	std::cout << std::endl;
	std::cout << "Moved tree to tree2" << std::endl;
	std::cout << "tree2.toString() = " << tree2.toString() << std::endl;
	std::cout << "tree.toString() = " << tree.toString() << std::endl;
}//int main()
