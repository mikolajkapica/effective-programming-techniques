#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

class Tree;
class Parser;

class UserInterface {
public:
	std::string run(Tree *&pc_tree, std::vector<std::string> &vec_vars, Parser *&parser, bool &b_run);
};

