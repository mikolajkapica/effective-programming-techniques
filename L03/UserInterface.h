#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

class Tree;

class UserInterface {
public:
	UserInterface() : pc_tree(NULL), b_run(true) {};
	~UserInterface();
	void run();
private:
	Tree* pc_tree;
	std::vector<std::string> vec_vars;
	std::map<std::string, int> map_values;
	bool b_run;
};

