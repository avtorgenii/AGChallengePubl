#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <cstdlib>
#include <ctime>

CGeneticAlgorithm::CGeneticAlgorithm(CLFLnetEvaluator& evaluator, int popSize, double crossProb, double mutProb)
	: popSize(popSize), crossProb(crossProb), mutProb(mutProb) 
{
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < popSize; i++)
	{
		population.push_back(CIndividual(&evaluator));
	}

}

CIndividual& CGeneticAlgorithm::runIter()
{
	vector<CIndividual> newPop;

	// Crossing
	while (newPop.size() < population.size())
	{
		CIndividual r1;
		CIndividual r2;

		CIndividual parent1;
		CIndividual parent2;

		r1 = population[rand() % popSize];
		r2 = population[rand() % popSize];

		parent1 = r1.getFitness() > r2.getFitness() ? r1 : r2;

		r1 = population[rand() % popSize];
		r2 = population[rand() % popSize];

		parent2 = r1.getFitness() > r2.getFitness() ? r1 : r2;

		if (&parent1 == &parent2)
		{
			if (&parent2 == &r1)
				parent2 = r2;
			else
				parent2 = r1;
		}

		// Should cross ?
		if (static_cast<float>(rand()) / RAND_MAX <= crossProb)
		{
			vector<CIndividual> crossoverResult = parent1.crossover(parent2);

			newPop.insert(newPop.end(), crossoverResult.begin(), crossoverResult.end());
		}
		else
		{
			newPop.push_back(CIndividual(parent1));
			newPop.push_back(CIndividual(parent2));
		}
	}

	if (newPop.size() > population.size())
		newPop.pop_back();

	
	population = newPop;


	// Mutating
	
	for (auto &el : population)
	{
		el.mutate(mutProb);
	}
	

	auto bestSolution = max_element(population.begin(), population.end(),
		[](CIndividual a, CIndividual b) 
		{
			return a.getFitness() < b.getFitness();
		}
	);

	return *bestSolution;
}
