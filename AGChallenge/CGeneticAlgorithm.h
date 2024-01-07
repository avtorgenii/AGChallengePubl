#pragma once

#include "CIndividual.h"
#include "Evaluator.h"
#include <vector>

using namespace std;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(int popSize, double crossProb, double mutProb);

	CIndividual& run(int iterations, CLFLnetEvaluator& evaluator);

private:
	int popSize;
	double crossProb;
	double mutProb;

	CIndividual selectParent(const vector<CIndividual>& population) const;
};

