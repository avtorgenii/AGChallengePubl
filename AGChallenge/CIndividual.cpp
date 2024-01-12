#include "CIndividual.h"

CIndividual::CIndividual() : evaluator(nullptr)
{
}

CIndividual::CIndividual(const CIndividual& other) : genotype(other.genotype), evaluator(other.evaluator)
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

vector<CIndividual> CIndividual::crossover(const CIndividual& other) const 
{
	int crossIndex = (rand() % (GENOTYPELEN - 1)) + 1;

	CIndividual child1;
	CIndividual child2;

	for (int i = 0; i < crossIndex; i++)
	{
		child1.genotype.push_back(genotype[i]);
		child2.genotype.push_back(other.genotype[i]);
	}

	for (int i = crossIndex; i < GENOTYPELEN; i++)
	{
		child1.genotype.push_back(other.genotype[i]);
		child2.genotype.push_back(genotype[i]);
	}

	child1.evaluator = evaluator;
	child2.evaluator = evaluator;

	return { child1, child2 };
}

CIndividual CIndividual::newCrossover(const CIndividual & other1, const CIndividual & other2) const
{
	CIndividual res(*this);

	vector<int> indices;
	vector<int> gens;

	for (unsigned int i = 0; i < other1.genotype.size(); i++) 
	{
		if (other1.genotype[i] == other2.genotype[i]) 
		{
			indices.push_back(i);
			gens.push_back(other1.genotype[i]);
		}
	}

	for (unsigned int i = 0;i < indices.size();i++) 
	{
		res.genotype[indices[i]] = gens[i];
	}

	return res;
}

vector<int>& CIndividual::getGenotype()
{
	return genotype;
}

double CIndividual::getFitness()
{
	return evaluator->dEvaluate(&genotype);
}

string CIndividual::toString()
{
	string res = "";

	for (auto el : genotype) 
	{
		res += to_string(el);
	}

	return res;
}
