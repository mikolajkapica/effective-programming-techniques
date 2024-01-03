#pragma once
#include "Evaluator.h"
#include "CIndividual.h"


class CGeneticAlgorithm
{
private:
	CLFLnetEvaluator& c_evaluator;
	int i_population_size;
	int i_tournament_size;
	int i_elitism_size;
	float f_crossover_rate;
	float f_mutation_rate;

	std::mt19937 gen;
	std::uniform_int_distribution<> distrib;

	CIndividual* pc_best_individual;
	std::vector<CIndividual*> vec_population;
	std::vector<CIndividual*> vec_elite;
	CIndividual cGetTournamentWinner();
public:
	CGeneticAlgorithm() : c_evaluator(*(new CLFLnetEvaluator())) {};
	void vInitialize(
		CLFLnetEvaluator& c_evaluator,
		int i_population_size,
		int i_tournament_size,
		int i_elitism_size,
		float f_crossover_rate,
		float f_mutation_rate
	);

	void vRunIteration();

	CIndividual *pcGetBestIndividual() { return pc_best_individual; };
};

// TODO: deallocation??

