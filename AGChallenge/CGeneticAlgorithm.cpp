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

		//vector<CIndividual> parents;

		// Should cross ?
		if (static_cast<float>(rand()) / RAND_MAX <= crossProb)
		{
			vector<CIndividual> parents;
			CIndividual temp;

			while (parents.size() != PARENTSCOUNT) 
			{
				r1 = population[rand() % popSize];
				r2 = population[rand() % popSize];

				temp = r1.getFitness() > r2.getFitness() ? r1 : r2;

				if (!contains(parents, &temp))
				{
					parents.push_back(temp);
				}
			}

			//vector<CIndividual> crossoverResult = parents[0].crossover(parents[1]);
			//newPop.insert(newPop.end(), crossoverResult.begin(), crossoverResult.end());

			CIndividual crossoverResult = parents[0].newCrossover(parents[1], parents[2]);

			newPop.push_back(crossoverResult);
		}
		else
		{
			/*
			CIndividual temp;

			while (parents.size() != PARENTSCOUNT)
			{
				r1 = population[rand() % popSize];
				r2 = population[rand() % popSize];

				temp = r1.getFitness() > r2.getFitness() ? r1 : r2;

				if (!contains(parents, &temp))
				{
					parents.push_back(temp);
				}
			}
			*/

			r1 = population[rand() % popSize];
			r2 = population[rand() % popSize];

			CIndividual parent1 = r1.getFitness() > r2.getFitness() ? r1 : r2;

			newPop.push_back(CIndividual(parent1));
		}
	}

	/*
	if (newPop.size() > population.size())
		newPop.pop_back();
	*/

	
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

bool CGeneticAlgorithm::contains(vector<CIndividual>& vec, CIndividual * elem)
{
	for (auto el : vec) 
	{
		if (&el == elem)
			return true;
	}

	return false;
}
