#include "CIndividual.h"

// Simplest crossover - one point crossover
std::pair<CIndividual*, CIndividual*> CIndividual::cCrossover(const CIndividual* cSecondParent) const
{
	std::vector<int> vec_fst_child_genotype(vec_genotype.size());
	std::vector<int> vec_snd_child_genotype(vec_genotype.size());

	int i_crossover_point = rand() % vec_genotype.size();

	#pragma omp parallel for
	for (int i = 0; i < vec_genotype.size(); i++)
	{
		if (i < i_crossover_point)
		{
			vec_fst_child_genotype[i] = vec_genotype[i];
			vec_snd_child_genotype[i] = cSecondParent->vec_genotype[i];
		}
		else
		{
			vec_fst_child_genotype[i] = cSecondParent->vec_genotype[i];
			vec_snd_child_genotype[i] = vec_genotype[i];
		}
	}

	return std::make_pair(new CIndividual(vec_fst_child_genotype), new CIndividual(vec_snd_child_genotype));
}

void CIndividual::vMutate(float f_mutation_rate, MyEvaluator* pc_evaluator) {
	#pragma omp parallel for
	for (int i = 0; i < vec_genotype.size(); i++)
	{
		if (dRand() < f_mutation_rate)
		{
			vec_genotype[i] = rand() % pc_evaluator->iGetNumberOfValues(i);
		}
	}
}

//std::vector<CIndividual*> CIndividual::vMutateMod()
//{
//	// losowa liczba od 0 do evaluator iGetNumberOfValues
//	int i_random_gene = rand() % pc_evaluator->iGetNumberOfBits();
//	int i_random_gene_max_value = pc_evaluator->iGetNumberOfValues(i_random_gene);
//	std::vector<int> vec_genotype_copy(vec_genotype);
//
//	// generuje i_random_gene_max_value osobnikow 
//	std::vector<CIndividual*> vec_individuals;
//	for (int i = 0; i < i_random_gene_max_value; i++) {
//		if (i != vec_genotype[i_random_gene]) {
//			vec_genotype_copy[i_random_gene] = i;
//			CIndividual *c_individual = new CIndividual(vec_genotype_copy, pc_evaluator);
//			vec_individuals.push_back(c_individual);
//		}
//	}
//	return vec_individuals;
//}
