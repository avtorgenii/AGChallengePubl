#pragma once

#include "CIndividual.h"
#include "Evaluator.h"
#include <vector>

using namespace std;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(CLFLnetEvaluator& evaluator, int popSize, double crossProb, double mutProb);

	CIndividual& runIter();

private:
	int popSize;
	double crossProb;
	double mutProb;

	vector<CIndividual*> population;
};

