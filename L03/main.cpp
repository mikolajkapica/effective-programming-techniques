#include <iostream>
#include "Tree.h"
#include "Parser.h"

int main() {
	const char *s_input = "+ * 5 sin x * + a b 8";
	Parser parser = Parser(s_input);
	parser.lex();

	std::cout << "Tokens: ";
	std::vector<std::string> tokens = parser.getTokens();
	for (int i = 0; i < tokens.size() - 1; i++) {
		std::cout << tokens[i] << " ";
	}
	std::cout << std::endl;

	BinaryTree tree = BinaryTree();

}
