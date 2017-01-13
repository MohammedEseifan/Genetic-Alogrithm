#pragma once
#include <vector>
#include<string>
#include "DNA.h"
class Population
{
public:
	Population::Population(int size,float muteRate, string targetStr);
	~Population();
	std::string targetString;
	void calculateFitnesses();
	void reproduce();
	
	float maxFitness;
	int maxFitnessIndex;

private:
	std::vector<DNA> pop;
	int popSize;
	float mutationRate;
	float map(float value, float istart, float istop, float ostart, float ostop);
	int gen;
};


