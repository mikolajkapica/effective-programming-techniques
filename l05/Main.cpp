#include <iostream>
#include "CMySmartPointer.h"
#include "tree.h"
#include "token.h"

int main()
{
	CMySmartPointer pc_pointer = new int(5);
	std::cout << pc_pointer.iGetCounter() << std::endl;
	CMySmartPointer pc_pointer2 = pc_pointer;
	std::cout << pc_pointer.iGetCounter() << std::endl;
	CMySmartPointer pc_pointer3 = pc_pointer;
	std::cout << pc_pointer.iGetCounter() << std::endl;
	CMySmartPointer pc_pointer4 = pc_pointer;
	std::cout << pc_pointer.iGetCounter() << std::endl;

	CMySmartPointer<int> pc_pointer5;
	pc_pointer5 = pc_pointer.cDuplicate();
	std::cout << "pc_pointer5 = " << *pc_pointer5 << std::endl;
	std::cout << "pc_pointer5 counter = " << pc_pointer.iGetCounter() << std::endl;
	std::cout << std::endl;


	std::cout << *pc_pointer << std::endl;
	std::cout << pc_pointer.iGetCounter() << std::endl;
	std::cout << *pc_pointer2 << std::endl;
	std::cout << pc_pointer2.iGetCounter() << std::endl;

	*pc_pointer = 10;
	std::cout << pc_pointer.iGetCounter() << std::endl;

	std::cout << *pc_pointer << std::endl;
	std::cout << *pc_pointer2 << std::endl;

	Tree<int> tree1 = Tree<int>();
	MyError e1 = tree1.pcInsert(new Node<int>(new Token<int>(ETokenType::OPERATOR, NULL, "+", 2)));
	MyError e2 = tree1.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 5, "5")));
	MyError e3 = tree1.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 3, "3")));

	Tree<int> tree2 = Tree<int>();
	MyError e4 = tree2.pcInsert(new Node<int>(new Token<int>(ETokenType::OPERATOR, NULL, "*", 2)));
	MyError e5 = tree2.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 8, "8")));
	MyError e6 = tree2.pcInsert(new Node<int>(new Token<int>(ETokenType::CONSTANT, 2, "2")));

	std::cout << "tree1.toString() = " << tree1.toString() << std::endl;
	std::cout << "tree2.toString() = " << tree2.toString() << std::endl;
	std::cout << std::endl;

	tree1 = std::move(tree2);

	std::cout << "Moved tree3 to tree1" << std::endl;
	std::cout << "tree1.toString() = " << tree1.toString() << std::endl;
	std::cout << "tree2.toString() = " << tree2.toString() << std::endl;
}//int main()
