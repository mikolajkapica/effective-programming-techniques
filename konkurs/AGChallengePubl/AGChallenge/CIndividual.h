#pragma once

#include <vector>

#include "MyEvaluator.h"


class CIndividual
{
private:
	std::vector<int> vec_genotype;
	double d_fitness;
	//double d_fake_fitness;

public:
	CIndividual(std::vector<int> vec_genotype) : vec_genotype(vec_genotype) {};
	//CIndividual(const CIndividual* cOther) : vec_genotype(cOther->vec_genotype), pc_evaluator(cOther->pc_evaluator), d_fitness(cOther->d_fitness), d_fake_fitness(cOther->d_fake_fitness) {};
	CIndividual(const CIndividual* cOther) : vec_genotype(cOther->vec_genotype), d_fitness(cOther->d_fitness) {};





	//void vEvaluateAndSetFakeFitness() {
	//	double d_fitness = this->d_fitness;
	//	double d_best = pc_evaluator->dGetBestFitness();
	//	if (d_fitness < 0.1 * d_best) {
	//		//printf("Fake fitness: %f\n", 0.9 * d_best);
	//		this->d_fake_fitness = 0.9 * d_best;
	//		return;
	//	}
	//	this->d_fake_fitness = d_fitness;
	//}
	void vEvaulateAndSetFitness(MyEvaluator* pc_evaluator) { this->d_fitness = pc_evaluator->dEvaluate(&vec_genotype); };
	std::pair<CIndividual*, CIndividual*> cCrossover(const CIndividual *cSecondParent) const;
	void vMutate(float f_mutation_rate, MyEvaluator* pc_evaluator);

	//double dGetFitness() { if (d_fitness < 0.05 * pc_evaluator->dGetBestFitness()) return 0.75 * pc_evaluator->dGetBestFitness(); return d_fitness; };
	double dGetFitness() { return d_fitness; };
	//double dGetFakeFitness() { return d_fake_fitness; };
	std::vector<int> vecGetGenotype() { return vec_genotype; };
};

