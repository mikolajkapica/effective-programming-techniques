#pragma once

#include <map>
#include <string>

class Tree;

class Evaluator {
public:
	double dEvaluate(Tree *tree, std::map<std::string, int> map_vars);
};

