#pragma once
#include "MyEvaluator.h"
#include "CIndividual.h"

class CGeneticAlgorithm 
{
private:
	std::vector<MyEvaluator*> vec_evaluators;
	int i_population_size;
	int i_tournament_size;
	int i_elitism_size;
	float f_crossover_rate;
	float f_mutation_rate;
	int i_no_improvement_counter;
	double d_last_best_fitness;

	std::mt19937 gen;
	std::uniform_int_distribution<> distrib;

	CIndividual* pc_best_individual;
	std::vector<CIndividual*> vec_population;
	std::vector<CIndividual*> vec_elite;
	CIndividual* cGetTournamentWinner();
public:
	void vInitialize(
		CLFLnetEvaluator* pc_evaluator,
		int i_population_size,
		int i_tournament_size,
		int i_elitism_size,
		float f_crossover_rate,
		float f_mutation_rate
	);
	~CGeneticAlgorithm() {
		for (int i = 0; i < vec_population.size(); i++)
		{
			delete vec_population[i];
		}
		delete pc_best_individual;
	}

	void vRunIteration();

	CIndividual *pcGetBestIndividual() { return pc_best_individual; };
};

