#include "Optimizer.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;


void stats(int &i_number_of_generations, double d_time_passed, double d_current_best_fitness);

COptimizer::COptimizer(CLFLnetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());

	d_current_best_fitness = 0;

	// # START - MY CODE HERE ##########
	i_number_of_generations = 0;
	#define DEFAULT_POPULATION_SIZE 200
	#define DEFAULT_TOURNAMENT_SIZE 10
	#define DEFAULT_ELITISM_SIZE 25
	#define DEFAULT_CROSSOVER_RATE 0.9
	#define DEFAULT_MUTATION_RATE 0.001
	c_ga.vInitialize(c_evaluator, DEFAULT_POPULATION_SIZE, DEFAULT_TOURNAMENT_SIZE, DEFAULT_ELITISM_SIZE, DEFAULT_CROSSOVER_RATE, DEFAULT_MUTATION_RATE);
	// # END - MY CODE HERE ############

}//COptimizer::COptimizer(CEvaluator &cEvaluator)

void COptimizer::vInitialize()
{
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();
}//void COptimizer::vInitialize()

void COptimizer::vRunIteration(double d_time_passed)
{
	vector<int> v_candidate;
	//v_fill_randomly(v_candidate);

	// # START - MY CODE HERE ##########
	this->c_ga.vRunIteration();
	v_candidate = this->c_ga.pcGetBestIndividual()->vecGetGenotype();
	// # END - MY CODE HERE ############

	double d_candidate_fitness = c_evaluator.dEvaluate(&v_candidate);

	if (d_candidate_fitness > d_current_best_fitness)
	{
		v_current_best = v_candidate;
		d_current_best_fitness = d_candidate_fitness;

		// # START - MY CODE HERE ##########
		// # END - MY CODE HERE ############

		//cout << d_current_best_fitness << endl;
		stats(i_number_of_generations, d_time_passed, d_current_best_fitness);
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

void stats(int &i_number_of_generations, double d_time_passed, double d_current_best_fitness)
{
	cout << '\r';
	std::string s_out;
	s_out += "GEN=" + to_string(i_number_of_generations) + " | ";
	s_out += "TIME: ";
	int i_hours = (int)d_time_passed / 3600;
	int i_minutes = ((int)d_time_passed % 3600) / 60;
	int i_seconds = (int)d_time_passed % 60;
	if (i_hours > 0)
	{
		s_out += to_string(i_hours) + "h ";
	}
	if (i_minutes > 0)
	{
		s_out += to_string(i_minutes) + "m ";
	}
	s_out += to_string(i_seconds) + "s -> ";
	cout << s_out << d_current_best_fitness;
}
