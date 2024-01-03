#pragma once

#include <vector>

#include "Evaluator.h"


class CIndividual
{
private:
	std::vector<int> vec_genotype;
	double d_fitness;

public:
	CIndividual(std::vector<int> vec_genotype, CLFLnetEvaluator &c_evaluator) 
	{ 
		this->vec_genotype = vec_genotype;
		this->d_fitness = dEvaluateFitness(c_evaluator); 
	};
	CIndividual(const CIndividual& cOther) {
		for (int i = 0; i < cOther.vec_genotype.size(); i++)
		{
			vec_genotype.push_back(cOther.vec_genotype[i]);
		}
		//vec_genotype = cOther.vec_genotype; 
		d_fitness = cOther.d_fitness; 
	};
	~CIndividual() {};


	double dEvaluateFitness(CLFLnetEvaluator &c_evaluator) { return c_evaluator.dEvaluate(&vec_genotype); };
	std::pair<CIndividual, CIndividual> cCrossover(const CIndividual &cSecondParent, CLFLnetEvaluator &c_evaluator) const;
	void vMutate(CLFLnetEvaluator &c_evaluator);

	double dGetFitness() { return d_fitness; };
	std::vector<int> vecGetGenotype() { return vec_genotype; };
};

