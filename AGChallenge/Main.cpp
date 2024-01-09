#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"
#include "CGeneticAlgorithm.h"

#include <exception>
#include <iostream>
#include <random>

using namespace TimeCounters;

using namespace std;

#define MAX_TIME 20 * 60


void  runAGExperiment(CString  netName, int popSize, double crossProb, double mutProb)
{
	CLFLnetEvaluator evaluator;
	evaluator.bConfigure(netName);
	
	try
	{
		CTimeCounter timeCounter;

		double timePassed;

		CGeneticAlgorithm optimizer(evaluator, popSize, crossProb, mutProb);

		timeCounter.vSetStartNow();

		timeCounter.bGetTimePassed(&timePassed);

		while (timePassed <= MAX_TIME)
		{
			CIndividual bestSolution = optimizer.runIter();
			cout << bestSolution.getFitness() << endl;

			timeCounter.bGetTimePassed(&timePassed);
		}
	}
	catch (exception &exception)
	{
		cout << exception.what() << endl;
	}
}

void main(int iArgCount, char **ppcArgValues)
{
	/*
	random_device c_mask_seed_generator;
	int i_mask_seed = (int)c_mask_seed_generator();


	CString  s_test;
	*/

	runAGExperiment("104b00", 200, 1, 0.02);

	/*vRunIsingSpinGlassExperiment(81, 0, i_mask_seed);
	vRunIsingSpinGlassExperiment(81, 0, iSEED_NO_MASK);

	vRunLeadingOnesExperiment(50, i_mask_seed);
	vRunLeadingOnesExperiment(50, iSEED_NO_MASK);

	vRunMaxSatExperiment(25, 0, 4.27f, i_mask_seed);
	vRunMaxSatExperiment(25, 0, 4.27f, iSEED_NO_MASK);

	vRunNearestNeighborNKExperiment(100, 0, 4, i_mask_seed);
	vRunNearestNeighborNKExperiment(100, 0, 4, iSEED_NO_MASK);

	vRunOneMaxExperiment(100, i_mask_seed);
	vRunOneMaxExperiment(100, iSEED_NO_MASK);

	vRunRastriginExperiment(200, 10, i_mask_seed);
	vRunRastriginExperiment(200, 10, iSEED_NO_MASK);*/
}