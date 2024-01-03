#include "CIndividual.h"

// Simplest crossover - one point crossover
std::pair<CIndividual, CIndividual> CIndividual::cCrossover(const CIndividual& cSecondParent, CLFLnetEvaluator &c_evaluator) const
{
	std::vector<int> vec_fst_child_genotype(vec_genotype.size());
	std::vector<int> vec_snd_child_genotype(vec_genotype.size());

	int i_crossover_point = rand() % vec_genotype.size();

	for (int i = 0; i < vec_genotype.size(); i++)
	{
		if (i < i_crossover_point)
		{
			vec_fst_child_genotype[i] = vec_genotype[i];
			vec_snd_child_genotype[i] = cSecondParent.vec_genotype[i];
		}
		else
		{
			vec_fst_child_genotype[i] = cSecondParent.vec_genotype[i];
			vec_snd_child_genotype[i] = vec_genotype[i];
		}
	}

	return std::make_pair(CIndividual(vec_fst_child_genotype, c_evaluator), CIndividual(vec_snd_child_genotype, c_evaluator));
}

void CIndividual::vMutate(CLFLnetEvaluator& c_evaluator) {
	int i_index = rand() % vec_genotype.size();
	vec_genotype[i_index] = rand() % c_evaluator.iGetNumberOfValues(i_index);
}
