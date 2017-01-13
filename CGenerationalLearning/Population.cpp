#include "stdafx.h"
#include "Population.h"
#include "DNA.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
using namespace std;

// Population class deals with creating, reproducing and assessing DNA objects until the targetString is reached
Population::Population(int size, float muteRate, string targetStr)
{
	gen = 0;
	popSize = size;
	mutationRate=muteRate;
	targetString = targetStr;

	//Fill population pool with new DNA objects
	for (int i = 0; i < popSize; i++)
	{
		pop.push_back(DNA(targetString.length(),i));
	}
	calculateFitnesses();
}

//Calculates the fitness of each DNA object and keeps track of the DNA with the heightest fitness
void Population::calculateFitnesses()
{
	//Init vars
	maxFitnessIndex = 0;
	maxFitness = 0;
	float avg = 0;

	//Loop through each DNA object, calculate fitness and check if fitness is greater than previous max
	for (int i = 0; i < popSize; i++)
	{
		pop[i].calcFitness(targetString);
		avg += pop[i].fitness;
		if (pop[i].fitness > maxFitness) {
			maxFitness = pop[i].fitness;
			maxFitnessIndex = i;
		}
		
	}

	//Print some information about the population (for debugging)
	cout << gen<<": "<<pop[maxFitnessIndex].str << "  " << (int)(100*(avg/popSize)) << endl;
}

//Generates a mating pool and randomly selects two DNA objects to mate
void Population::reproduce()
{
	gen++;

	//Creating mating pool
	vector<DNA> matingPool;
	matingPool.clear();

	//For each DNA object in the population, add it to the mating pool a certain number of times
	for (int i = 0; i < popSize; i++)
	{
		int num = 50*map(pop[i].fitness,0,maxFitness,0,1); //Determines how many times this DNA object should be added to the mating pool (aka probability of being mated)
		for (int x = 0; x <= num; x++)
		{
			matingPool.push_back(pop[i]);
		}
	}

	srand(time(0));


	for (int i = 0; i < popSize; i++)
	{
		//Select two DNAs to mate and mate them
		DNA parentA = matingPool[rand() % matingPool.size()];
		DNA parentB = matingPool[rand() % matingPool.size()];
		pop[i] = parentA.mate(parentB,rand());

		//Mutate the newly created child
		pop[i].mutate(mutationRate,rand());
	}
	calculateFitnesses();
}

// Used to map a value from an old range to a new one
float Population::map(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}



