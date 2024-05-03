#include "CGeneticAlgorithm.h"
#include <numeric>
#include <functional>

//double MyEvaluator::d_best_fitness = 0.0;

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

CIndividual* CGeneticAlgorithm::cGetTournamentWinner() 
{
	CIndividual* pc_best = vec_population[distrib(gen)];

	std::vector<int> indecies(i_population_size);
	std::iota(indecies.begin(), indecies.end(), 0);
	std::shuffle(indecies.begin(), indecies.end(), gen);

	for (int i = 0; i < i_tournament_size; i++) 
	{
		CIndividual* pc_current = vec_population[indecies[i]];
		//double d_current_fitness = pc_current->dGetFakeFitness();
		double d_current_fitness = pc_current->dGetFitness();
		double d_best_fitness = pc_best->dGetFitness();
		if (d_current_fitness > d_best_fitness)
		{
			pc_best = pc_current;
		}
	}
	return pc_best;
}

void CGeneticAlgorithm::vInitialize(CLFLnetEvaluator* pc_evaluator, int i_population_size, int i_tournament_size, int i_elitism_size, float f_crossover_rate, float f_mutation_rate)
{
	this->vec_evaluators = std::vector<MyEvaluator*>(i_population_size);
	this->i_population_size = i_population_size;
	this->i_tournament_size = i_tournament_size;
	this->i_elitism_size = i_elitism_size;
	this->f_crossover_rate = f_crossover_rate;
	this->f_mutation_rate = f_mutation_rate;
	this->i_no_improvement_counter = 0;
	this->d_last_best_fitness = 0;

	gen = std::mt19937(random_device()());
	distrib = std::uniform_int_distribution<>(0, i_population_size - 1);

	vec_population = std::vector<CIndividual*>(i_population_size);
	vec_elite = std::vector<CIndividual*>(i_elitism_size);

	CString name = pc_evaluator->sGetNetName();

	#pragma omp parallel for
	for (int i = 0; i < i_population_size; i++)
	{
		this->vec_evaluators[i] = new MyEvaluator(name);
	}


	MyEvaluator* fst_evaluator = vec_evaluators[0];
	// fill population with random individuals
	#pragma omp parallel for
	for (int i = 0; i < i_population_size; i++)
	{
		std::vector<int> vec_genotype(fst_evaluator->iGetNumberOfBits());
		for (int j = 0; j < fst_evaluator->iGetNumberOfBits(); j++)
		{
			vec_genotype[j] = lRand(fst_evaluator->iGetNumberOfValues(j));
		}
		vec_population[i] = new CIndividual(vec_genotype);
	}

	// update elite
	vec_elite = vecGetNBest<CIndividual*>(vec_population, i_elitism_size, [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });

	// update best individual
	pc_best_individual = new CIndividual(*vec_elite[0]);
}

void CGeneticAlgorithm::vRunIteration()
{
	std::vector<CIndividual*> vec_new_population(i_population_size);

	// elitism
	#pragma omp parallel for
	for (int i = 0; i < i_elitism_size; i++)
	{
		vec_new_population[i] = new CIndividual(*vec_elite[i]);
	}

	#pragma omp parallel for
	for (int i = i_elitism_size; i < i_population_size; i = i + 2) 
	{
		// get parents
		CIndividual* pc_parent1 = cGetTournamentWinner();
		CIndividual* pc_parent2 = cGetTournamentWinner();

		bool isCrossover = dRand() < f_crossover_rate;
		if (isCrossover)
		{
			// crossover
			std::pair<CIndividual*, CIndividual*> p_children = pc_parent1->cCrossover(pc_parent2);

			pc_parent1 = p_children.first;
			pc_parent2 = p_children.second;
		}

		// mutation
		double f_mutation_mod = f_mutation_rate;
		 //if (i_no_improvement_counter > 50) f_mutation_mod += i_no_improvement_counter * 0.0005;
		//if (i_no_improvement_counter > 50) f_mutation_rate += 0.000005;
		//std::vector<CIndividual*> vec_new_individuals1 = pc_parent1->vMutateMod();
		//std::vector<CIndividual*> vec_new_individuals2 = pc_parent2->vMutateMod();

		//for (int j = 0; j < vec_new_individuals1.size() && i < i_population_size; j++)
		//{
		//	vec_new_population[i] = vec_new_individuals1[j];
		//	i++;
		//}

		//for (int j = 0; j < vec_new_individuals2.size() && i < i_population_size; j++)
		//{
		//	vec_new_population[i] = vec_new_individuals2[j];
		//	i++;
		//}

		// add children to new population

		if (i < i_population_size)
		{
			pc_parent1->vMutate(f_mutation_mod, vec_evaluators[i]);
			if (isCrossover)
				vec_new_population[i] = pc_parent1;
			else
				vec_new_population[i] = new CIndividual(pc_parent1);
		}


		if (i + 1 < i_population_size) 
		{
			pc_parent2->vMutate(f_mutation_mod, vec_evaluators[i+1]);
			if (isCrossover)
				vec_new_population[i+1] = pc_parent2;
			else
				vec_new_population[i+1] = new CIndividual(pc_parent2);
		}
	}


	// evaluate new population
	#pragma omp parallel for
	for (int i = 0; i < i_population_size; i++)
	{
		vec_new_population[i]->vEvaulateAndSetFitness(vec_evaluators[i]);
		//vec_new_population[i]->vEvaluateAndSetFakeFitness();
	}

	// delete old population
	#pragma omp parallel for
	for (int i = 0; i < vec_population.size(); i++) 
	{
		delete vec_population[i];
	}

	// assign new population
	vec_population = vec_new_population;

	// update elite
	vec_elite = vecGetNBest<CIndividual*>(vec_population, i_elitism_size, [](CIndividual* a, CIndividual* b) { return a->dGetFitness() > b->dGetFitness(); });

	// update best individual
	if (pc_best_individual->dGetFitness() < vec_elite[0]->dGetFitness()) {
		delete pc_best_individual;
		pc_best_individual = new CIndividual(*vec_elite[0]);
	}
	if (d_last_best_fitness == pc_best_individual->dGetFitness()) {
		i_no_improvement_counter++;
	} else {
		i_no_improvement_counter = 0;
		d_last_best_fitness = pc_best_individual->dGetFitness();
	}
	//std::cout << "Best fitness: " << pc_best_individual->dGetFitness() << std::endl;
	//std::cout << "Best from evaluator: " << pc_evaluator->dGetBestFitness() << std::endl;
}	


