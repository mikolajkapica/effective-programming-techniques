#include "UserInterface.h"
#include "Parser.h"
#include <iostream>
#include "Tree.h"

int main() {
	UserInterface ui;

	Tree* pc_tree = NULL;
	std::vector<std::string> vec_vars = std::vector<std::string>();
	Parser *parser = new Parser();

	bool b_run = true;
	while (b_run) {
		std::string s_output = ui.run(pc_tree, vec_vars, parser, b_run);
		std::cout << s_output << std::endl;
	}

}
