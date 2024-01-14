#include "CGeneticAlgorithm.h"
#include <numeric>
#include <functional>
#include <omp.h>

template<typename T>
std::vector<T> vecGetNBest(std::vector<T> vec, int n, std::function<bool(T, T)> f_compare)
{
	std::vector<T> vec_best(n);
	std::copy(vec.begin(), vec.begin() + n, vec_best.begin());

	for (int i = n; i < vec.size(); i++) {
		if (f_compare(vec[i], vec_best[n - 1])) {
			vec_best[n - 1] = vec[i];
			std::sort(vec_best.begin(), vec_best.end(), f_compare);
		}
	}

	return vec_best;
}

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
	std::sort(vec_elite.begin(), vec_elite.end(), [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });
	vec_elite.resize(i_elitism_size);

	// update best individual
	pc_best_individual = new CIndividual(*vec_elite[0]);
}

void CGeneticAlgorithm::vRunIteration()
{
	bool b_debug = false;
	std::vector<CIndividual*> vec_new_population(i_population_size);

	// elitism
	//#pragma omp parallel for
	for (int i = 0; i < i_elitism_size; i++)
	{
		vec_new_population[i] = new CIndividual(*vec_elite[i]);
	}

	//#pragma omp parallel for
	for (int i = i_elitism_size; i < i_population_size; i++) 
	{
		int thread_id;
		if (b_debug) {
			thread_id = omp_get_thread_num();
			std::cout << "Thread: " << thread_id << "\n";
		}

		// get parents
		CIndividual pc_parent1 = cGetTournamentWinner();
		CIndividual pc_parent2 = cGetTournamentWinner();

		if (b_debug)
			std::cout << "After tournaments\n";

		if (dRand() < f_crossover_rate)
		{
			// crossover
			std::pair<CIndividual, CIndividual> p_children = pc_parent1.cCrossover(pc_parent2);

			pc_parent1 = p_children.first;
			pc_parent2 = p_children.second;
		}

		if (b_debug)
			std::cout << "After Crossover\n";

		// mutation
		pc_parent1.vMutate(f_mutation_rate);
		pc_parent2.vMutate(f_mutation_rate);

		if (b_debug)
			std::cout << "After Mutation " << thread_id << "\n";

		// add children to new population
		if (i < i_population_size)
			vec_new_population[i] = new CIndividual(pc_parent1);

		if (i + 1 < i_population_size) 
		{
			vec_new_population[i + 1] = new CIndividual(pc_parent2);
			//i++;
		}
		if (b_debug)
			std::cout << "After adding children " << thread_id << "\n";
	}

	//#pragma omp parallel for
	for (int i = 0; i < i_population_size; i++)
	{
		vec_new_population[i]->vEvaulateAndSetFitness();
	}

	if (b_debug)
	std::cout << "After parallel for\n";

	// assign new population
	//#pragma omp parallel for
	for (int i = 0; i < vec_population.size(); i++) 
	{
		delete vec_population[i];
	}

	vec_population = vec_new_population;

	// update elite
	vec_elite = vecGetNBest<CIndividual*>(vec_population, i_elitism_size, [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });

	// update best individual
	pc_best_individual = new CIndividual(*vec_elite[0]);
}	

