#pragma once
#include<string>
using namespace std;
class DNA
{
public:
	string str;
	DNA(int size, int seed);
	DNA(string s, int seed);
	DNA mate(DNA partner, int split);
	float fitness;
	void calcFitness(string targetString);
	void mutate(float rate, int seed);
	int getSeed();
private:
	int seed;
};




