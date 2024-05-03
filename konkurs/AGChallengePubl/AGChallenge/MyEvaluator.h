#pragma once

#include "Evaluator.h"


class MyEvaluator
{
private:
	CLFLnetEvaluator* pc_evaluator;
	//static double d_best_fitness;
public:
	//MyEvaluator(CLFLnetEvaluator* pcEvaluator) { pc_evaluator = pcEvaluator; };
	MyEvaluator(CString s_name) { pc_evaluator = new CLFLnetEvaluator(); pc_evaluator->bConfigure(s_name); };
	//double dEvaluate(std::vector<int>* pvSolution) { double d_fit = pc_evaluator->dEvaluate(pvSolution); if (d_fit > d_best_fitness) d_best_fitness = d_fit; return d_fit; };
	double dEvaluate(std::vector<int>* pvSolution) { double d_fit = pc_evaluator->dEvaluate(pvSolution); return d_fit; };
	//double dGetBestFitness() { return d_best_fitness; };
	int iGetNumberOfValues(int iPairOffset) { return pc_evaluator->iGetNumberOfValues(iPairOffset); };
	int iGetNumberOfBits() { return pc_evaluator->iGetNumberOfBits(); };
};


