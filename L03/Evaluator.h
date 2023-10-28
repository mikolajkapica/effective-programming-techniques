#pragma once

#include <map>
#include <string>

class Tree;

class Evaluator {
public:
	double dEvaluateTree(Tree *tree, std::map<std::string, double> map_vars);
};

