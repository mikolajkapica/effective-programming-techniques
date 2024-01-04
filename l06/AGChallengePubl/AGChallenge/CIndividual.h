#pragma once

#include <vector>

#include "Evaluator.h"


class CIndividual
{
private:
	std::vector<int> vec_genotype;
	CLFLnetEvaluator &c_evaluator;
	double d_fitness;

public:
	CIndividual(std::vector<int> vec_genotype, CLFLnetEvaluator& c_evaluator) : vec_genotype(vec_genotype), c_evaluator(c_evaluator) 
	{
		d_fitness = dEvaluateFitness();
	};
	CIndividual(const CIndividual& cOther) : c_evaluator(cOther.c_evaluator), vec_genotype(cOther.vec_genotype), d_fitness(cOther.d_fitness) {};
	~CIndividual() {};
	CIndividual& operator=(const CIndividual& cOther) {
		if (this != &cOther) {
			vec_genotype = cOther.vec_genotype;
			c_evaluator = cOther.c_evaluator;
			d_fitness = cOther.d_fitness;
		}
		return *this;
	}
	CIndividual& operator=(CIndividual&& cOther) noexcept 
	{
		if (this != &cOther) 
		{
			vec_genotype = std::move(cOther.vec_genotype);
			c_evaluator = cOther.c_evaluator;
			d_fitness = cOther.d_fitness;
		}
		return *this;
	}


	double dEvaluateFitness() { return c_evaluator.dEvaluate(&vec_genotype); };
	std::pair<CIndividual, CIndividual> cCrossover(const CIndividual &cSecondParent) const;
	void vMutate(float f_mutation_rate);

	double dGetFitness() { return d_fitness; };
	std::vector<int> vecGetGenotype() { return vec_genotype; };
};

