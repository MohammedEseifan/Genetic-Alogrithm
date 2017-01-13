#include "stdafx.h"
#include "Population.h"
#include "DNA.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
using namespace std;

Population::Population(int size, float muteRate, string targetStr)
{
	gen = 0;
	popSize = size;
	mutationRate=muteRate;
	targetString = targetStr;
	
	for (int i = 0; i < popSize; i++)
	{
		pop.push_back(DNA(targetString.length(),i));
	}
	calculateFitnesses();
}

Population::~Population()
{
}

void Population::calculateFitnesses()
{
	maxFitnessIndex = 0;
	maxFitness = 0;
	float sum = 0;
	for (int i = 0; i < popSize; i++)
	{
		pop[i].calcFitness(targetString);
		sum += pop[i].fitness;
		if (pop[i].fitness > maxFitness) {
			maxFitness = pop[i].fitness;
			maxFitnessIndex = i;
		}
		//cout << pop[i].str << "  " << pop[i].fitness << endl;
	}
	cout << gen<<": "<<pop[maxFitnessIndex].str << "  " << (int)(100*(sum/popSize)) << endl;
}

void Population::reproduce()
{
	gen++;

	//Creating mating pool
	vector<DNA> matingPool;
	matingPool.clear();
	for (int i = 0; i < popSize; i++)
	{
		int num = 50*map(pop[i].fitness,0,maxFitness,0,1);
		for (int x = 0; x <= num; x++)
		{
			matingPool.push_back(pop[i]);
		}
	}

	srand(time(0));
	//cout << matingPool.size() << endl;
	for (int i = 0; i < popSize; i++)
	{
		DNA parentA = matingPool[rand() % matingPool.size()];
		DNA parentB = matingPool[rand() % matingPool.size()];
		pop[i] = parentA.mate(parentB,rand());
		pop[i].mutate(mutationRate,rand());
	}
	calculateFitnesses();
}

float Population::map(float value,
	float istart,
	float istop,
	float ostart,
	float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}



