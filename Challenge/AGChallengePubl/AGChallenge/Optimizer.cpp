#include "Optimizer.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;

COptimizer::COptimizer(CLFLnetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());

	d_current_best_fitness = 0;
}//COptimizer::COptimizer(CEvaluator &cEvaluator)

void COptimizer::vInitialize()
{
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();

	i_number_of_generations = 0;

	#define DEFAULT_POPULATION_SIZE 1000
	#define DEFAULT_TOURNAMENT_SIZE 50
	#define DEFAULT_ELITISM_SIZE 10
	#define DEFAULT_CROSSOVER_RATE 0.97
	#define DEFAULT_MUTATION_RATE 0.001
	c_ga.vInitialize(c_evaluator, DEFAULT_POPULATION_SIZE, DEFAULT_TOURNAMENT_SIZE, DEFAULT_ELITISM_SIZE, DEFAULT_CROSSOVER_RATE, DEFAULT_MUTATION_RATE);
}//void COptimizer::vInitialize()

void COptimizer::vRunIteration(double d_time_passed)
{
	vector<int> v_candidate;
	//v_fill_randomly(v_candidate);

	this->c_ga.vRunIteration();
	v_candidate = this->c_ga.pcGetBestIndividual()->vecGetGenotype();
	double d_candidate_fitness = this->c_ga.pcGetBestIndividual()->dGetFitness();

	if (d_candidate_fitness > d_current_best_fitness)
	{
		v_current_best = v_candidate;
		d_current_best_fitness = d_candidate_fitness;

		if (d_current_best_fitness > 10e-5) { 
			cout << "Found solution in " << i_number_of_generations << " iterations [time: ] " << d_time_passed << "s" << endl;
		}
		cout << "GEN=" << i_number_of_generations << " | TIME: " << d_time_passed << "s -> " << d_current_best_fitness << endl;

	}//if (d_candidate_fitness > d_current_best_fitness)
	i_number_of_generations++;
}//void COptimizer::vRunIteration()



void COptimizer::v_fill_randomly(vector<int> &vSolution)
{
	vSolution.resize((size_t)c_evaluator.iGetNumberOfBits());

	for (int ii = 0; ii < vSolution.size(); ii++)
	{
		vSolution.at(ii) = lRand(c_evaluator.iGetNumberOfValues(ii));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void COptimizer::v_fill_randomly(const vector<int> &vSolution)
