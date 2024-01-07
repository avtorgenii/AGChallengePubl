#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <cstdlib>
#include <ctime>

CGeneticAlgorithm::CGeneticAlgorithm(int popSize, double crossProb, double mutProb)
	: popSize(popSize), crossProb(crossProb), mutProb(mutProb) {}

CIndividual& CGeneticAlgorithm::run(int iterations, CLFLnetEvaluator& evaluator)
{
	srand(time(NULL));
	vector<CIndividual*> population;

	for (int i = 0; i < popSize; i++) 
	{
		CIndividual* newI = new CIndividual(&evaluator);
		population.push_back(newI);
	}

	for (int i = 0; i < iterations; i++)
	{
		// Crossing

		vector<CIndividual*> newPop;

		while (newPop.size() < population.size())
		{
			CIndividual* r1;
			CIndividual* r2;

			CIndividual* parent1;
			CIndividual* parent2;

			r1 = population[rand() % popSize];
			r2 = population[rand() % popSize];

			parent1 = r1->getFitness() > r2->getFitness() ? r1 : r2;

			r1 = population[rand() % popSize];
			r2 = population[rand() % popSize];

			parent2 = r1->getFitness() > r2->getFitness() ? r1 : r2;

			if (parent1 == parent2)
			{
				if (parent2 == r1)
					parent2 = r2;
				else
					parent2 = r1;
			}

			// Should cross ?
			if (static_cast<float>(rand()) / RAND_MAX < crossProb)
			{
				vector<CIndividual*> crossoverResult = parent1->crossover(*parent2);

				newPop.insert(newPop.end(), crossoverResult.begin(), crossoverResult.end());

			}
			else 
			{
				newPop.push_back(parent1);
				newPop.push_back(parent2);
			}
		}

		if (newPop.size() > population.size())
			newPop.pop_back();

		population = newPop;

		// Mutating

		for (auto el : population) 
		{
			el->mutate(mutProb);
		}
	}

	auto bestSolution = max_element(population.begin(), population.end(),
		[](CIndividual* a, CIndividual* b) 
		{
			return a->getFitness() < b->getFitness();
		}
	);

	return **bestSolution;
}

CIndividual CGeneticAlgorithm::selectParent(const vector<CIndividual>& population) const 
{

}
