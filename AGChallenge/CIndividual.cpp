#include "CIndividual.h"
#include <cstdlib>

CIndividual::CIndividual()
{
}

CIndividual::CIndividual(CLFLnetEvaluator* evaluator) : evaluator(evaluator)
{
	for (int i = 0; i < GENOTYPELEN; i++) 
	{
		genotype.push_back(rand() % (MAXVAL + 1));
		//cout << genotype[i];
	}
}

void CIndividual::mutate(double mutProb)
{
	for (int i = 0; i < GENOTYPELEN; i++) 
	{
		if (static_cast<float>(rand()) / RAND_MAX < mutProb) 
		{
			genotype[i] = rand() % (MAXVAL + 1);
		}
	}
}

vector<CIndividual*> CIndividual::crossover(const CIndividual& other) const 
{
	int crossIndex = (rand() % (GENOTYPELEN - 1)) + 1;

	CIndividual* child1 = new CIndividual();
	CIndividual* child2 = new CIndividual();

	for (int i = 0; i < crossIndex; i++) 
	{
		child1->genotype.push_back(genotype[i]);
		child2->genotype.push_back(other.genotype[i]);
	}

	for (int i = crossIndex; i < GENOTYPELEN; i++)
	{
		child1->genotype.push_back(other.genotype[i]);
		child2->genotype.push_back(genotype[i]);
	}

	child1->evaluator = evaluator;
	child2->evaluator = evaluator;

	return { child1, child2 };
}

vector<int>& CIndividual::getGenotype()
{
	return genotype;
}

double CIndividual::getFitness()
{
	return evaluator->dEvaluate(&genotype);
}
