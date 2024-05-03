#pragma once

#include "Evaluator.h"

#include <random>
#include <vector>

#include "CGeneticAlgorithm.h"

using namespace std;

class COptimizer
{
public:
	COptimizer(CLFLnetEvaluator &cEvaluator);

	void vInitialize();
	void vRunIteration();

	vector<int> *pvGetCurrentBest() { return &v_current_best; }

private:
	void v_fill_randomly(vector<int> &vSolution);

	CLFLnetEvaluator &pc_evaluator;

	double d_current_best_fitness;
	vector<int> v_current_best;

	mt19937 c_rand_engine;

	CGeneticAlgorithm c_ga;
	int i_number_of_generations;
};//class COptimizer