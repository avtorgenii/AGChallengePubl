#pragma once

#include <vector>
#include "Evaluator.h"
#include <string>
#define MAXVAL 3
#define GENOTYPELEN 2500

using namespace std;


class CIndividual {
public:
	CIndividual();
	CIndividual(const CIndividual& other);
	CIndividual(CLFLnetEvaluator* evaluator);

	void mutate(double mutProb);

	vector<CIndividual> crossover(const CIndividual& other) const;

	vector<int>& getGenotype();

	double getFitness();

	string toString();

private:
	vector<int> genotype;
	CLFLnetEvaluator* evaluator;

};

