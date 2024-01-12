#pragma once

#include "CIndividual.h"
#include "Evaluator.h"
#include <vector>

#define PARENTSCOUNT 3

using namespace std;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(CLFLnetEvaluator& evaluator, int popSize, double crossProb, double mutProb);

	CIndividual& runIter();

	bool contains(vector<CIndividual>& vec, CIndividual* elem);

private:
	int popSize;
	double crossProb;
	double mutProb;
	vector<CIndividual> population;
};

