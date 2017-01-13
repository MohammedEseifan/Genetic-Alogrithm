#include "stdafx.h"
#include "DNA.h"
#include <cstdlib>
#include <ctime>
#include<string>
#include<iostream>

using namespace std;


DNA::DNA(int size,int see)
{
	seed = see;
	srand(time(0)+seed);
	char *temp = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = rand() % 95 + 32;
	}
	
	temp[size] = '\0';
	str = string(temp);
	fitness = 0;
}

DNA::DNA(string s, int see )
{
	str = s;
	seed = see;
	fitness = 0;
}


DNA DNA::mate(DNA partner,int sp)
{
	int split = sp%str.length();
	return DNA(str.substr(0, split) + partner.str.substr(split, str.length() - split),rand());

}

void DNA::calcFitness(string targetString) {
	float sum = 0;
	for (int i = 0; i < targetString.length(); i++)
	{
		sum += targetString[i] == str[i];
	}
	
	fitness= sum / targetString.length();
}

void DNA::mutate(float rate, int see)
{
	srand(time(0)+see);
	char *temp = new char[str.length()+1];
	for (int i = 0; i < str.length(); i++) {
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < rate) {
			temp[i] = rand() % 95 + 32;
		} else {
			temp[i] = str[i];
		}
	}
	temp[str.length()] = '\0';
	str = string(temp);

}

int DNA::getSeed()
{
	return seed;
}
