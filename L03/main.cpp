#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Parser.h"
#include "Tree.h"
#include "Lexer.h"
#include "Token.h"
#include "Evaluator.h"

int main() {
	const char *s_input = "+ * 5 sin x * + a b 8";

	Lexer *lexer = new Lexer(s_input);
	std::vector<Token*> tokens = lexer->vecLex();
	std::cout << "Tokens: " << std::endl;
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i]->sToString();
	}
	std::cout << std::endl;

	Parser *parser = new Parser();
	Tree *tree = parser->pcParse(tokens);
	std::cout << "Tree:" << std::endl << tree->sToString();
	std::cout << std::endl;

	// vars
	std::vector<std::string> vars = tree->vecGetVariables();
	std::cout << "Variables:" << std::endl;
	for (int i = 0; i < vars.size(); i++) {
		std::cout << vars[i] << std::endl;
	}

	// comp
	std::cout << "Enter values for variables:" << std::endl;
	std::map<std::string, int> values;
	for (int i = 0; i < vars.size(); i++) {
		int value;
		std::cout << vars[i] << ": ";
		std::cin >> value;
		values.insert(std::pair<std::string, int>(vars[i], value));
	}
	Evaluator* evaluator = new Evaluator();
	std::cout << "Result: " << evaluator->dEvaluate(tree, values) << std::endl;


}
