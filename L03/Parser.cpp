#include <iostream>
#include <set>

#include "Parser.h"
#include "Tree.h"
#include "Token.h"
#include "Node.h"

Tree *Parser::pcParse(std::vector<Token*> vec_tokens) {
	Tree *tree = new Tree();
	for (int i = 0; i < vec_tokens.size(); i++) {
		tree->pcInsert(vec_tokens[i]);
	}
	return tree;
}



