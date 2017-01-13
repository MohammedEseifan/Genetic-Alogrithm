#include "stdafx.h"
#include "DNA.h"
#include <cstdlib>
#include <ctime>
#include<string>
#include<iostream>

using namespace std;

//Default constructor, generates random string
DNA::DNA(int size,int seed_)
{
	//Init random class with passed seed value
	seed = seed_;
	srand(time(0)+seed);

	//Generate random array of characters and convert to string
	char *temp = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = rand() % 95 + 32;
	}
	
	temp[size] = '\0';
	str = string(temp);
	fitness = 0;
}

//Constructor used when creating new DNA object from mating
DNA::DNA(string s, int seed_ )
{
	str = s;
	seed = seed_;
	fitness = 0;
}

//Splices this instance's string with the partner's string at the randomSplit point
DNA DNA::mate(DNA partner, int randomSplit)
{
	int split = randomSplit%str.length();
	return DNA(str.substr(0, split) + partner.str.substr(split, str.length() - split), rand()); //Return new DNA object with combination of strings

}

//Calculates the fitness
void DNA::calcFitness(string targetString) {
	
	float sum = 0;
	
	//Find number of character in the current string that match the target string
	for (int i = 0; i < targetString.length(); i++)
	{
		sum += targetString[i] == str[i];
	}
	
	//Set fitness value as the percentage of right characters
	fitness= sum / targetString.length();
}

//Mutates the current DNA object
void DNA::mutate(float rate, int seed_)
{
	//Init vars
	srand(time(0)+seed_);
	char *temp = new char[str.length()+1];

	//For each character in the string
	for (int i = 0; i < str.length(); i++) {
		//if the randomly generated number is less than the mutation rate then generate a random character
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < rate) {
			temp[i] = rand() % 95 + 32;
		} else { //else keep the same character
			temp[i] = str[i];
		}
	}
	temp[str.length()] = '\0';
	str = string(temp);

}

//Getter function for seed value
int DNA::getSeed()
{
	return seed;
}
