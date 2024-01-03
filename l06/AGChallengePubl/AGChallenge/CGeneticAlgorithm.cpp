#include "CGeneticAlgorithm.h"
#include <numeric>
#include <functional>

CIndividual CGeneticAlgorithm::cGetTournamentWinner() 
{
	CIndividual* pc_best = vec_population[distrib(gen)];

	std::vector<int> indecies(i_population_size);
	std::iota(indecies.begin(), indecies.end(), 0);
	std::shuffle(indecies.begin(), indecies.end(), gen);

	for (int i = 0; i < i_tournament_size; i++) 
	{
		CIndividual* pc_current = vec_population[indecies[i]];
		double d_current_fitness = pc_current->dGetFitness();
		double d_best_fitness = pc_best->dGetFitness();
		if (d_current_fitness > d_best_fitness)
		{
			pc_best = pc_current;
		}
	}
	return *pc_best;
}

void CGeneticAlgorithm::vInitialize(CLFLnetEvaluator& c_evaluator, int i_population_size, int i_tournament_size, int i_elitism_size, float f_crossover_rate, float f_mutation_rate)
{
	this->c_evaluator = c_evaluator;
	this->i_population_size = i_population_size;
	this->i_tournament_size = i_tournament_size;
	this->i_elitism_size = i_elitism_size;
	this->f_crossover_rate = f_crossover_rate;
	this->f_mutation_rate = f_mutation_rate;

	gen = std::mt19937(random_device()());
	distrib = std::uniform_int_distribution<>(0, i_population_size - 1);

	vec_population = std::vector<CIndividual*>(i_population_size);
	vec_elite = std::vector<CIndividual*>(i_elitism_size);

	// fill population with random individuals
	for (int i = 0; i < i_population_size; i++)
	{
		std::vector<int> vec_genotype(c_evaluator.iGetNumberOfBits());
		for (int j = 0; j < c_evaluator.iGetNumberOfBits(); j++)
		{
			vec_genotype[j] = lRand(c_evaluator.iGetNumberOfValues(j));
		}
		vec_population[i] = new CIndividual(vec_genotype, c_evaluator);
	}

	// update elite
	vec_elite.resize(i_population_size);
	std::copy(vec_population.begin(), vec_population.end(), vec_elite.begin());
	std::nth_element(vec_elite.begin(), vec_elite.begin() + i_elitism_size, vec_elite.end(), [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });

	// update best individual
	pc_best_individual = new CIndividual(*vec_elite[0]);
}

void CGeneticAlgorithm::vRunIteration()
{
	std::vector<CIndividual*> vec_new_population(i_population_size);

	// elitism
	for (int i = 0; i < i_elitism_size; i++)
	{
		vec_new_population[i] = new CIndividual(*vec_elite[i]);
	}

	for (int i = i_elitism_size; i < i_population_size; i++) 
	{
		// get parents
		CIndividual pc_parent1 = cGetTournamentWinner();
		CIndividual pc_parent2 = cGetTournamentWinner();

		if (dRand() < f_crossover_rate)
		{
			// crossover
			std::pair<CIndividual, CIndividual> p_children = pc_parent1.cCrossover(pc_parent2, c_evaluator);

			pc_parent1 = p_children.first;
			pc_parent2 = p_children.second;
		}

		// mutation
		if (dRand() < f_mutation_rate) pc_parent1.vMutate(c_evaluator);
		if (dRand() < f_mutation_rate) pc_parent2.vMutate(c_evaluator);

		// add children to new population
		vec_new_population[i] = new CIndividual(pc_parent1);
		if (i + 1 < i_population_size) 
		{
			vec_new_population[i + 1] = new CIndividual(pc_parent2);
			i++;
		}
	}

	// assign new population
	for (int i = 0; i < vec_population.size(); i++) 
	{
		delete vec_population[i];
	}
	vec_population = vec_new_population;

	// update elite
	vec_elite.resize(i_population_size);
	std::copy(vec_population.begin(), vec_population.end(), vec_elite.begin());
	std::nth_element(vec_elite.begin(), vec_elite.begin() + i_elitism_size, vec_elite.end(), [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });

	// update best individual
	pc_best_individual = new CIndividual(*vec_elite[0]);
}	
