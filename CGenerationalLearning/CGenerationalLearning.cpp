// CGenerationalLearning.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <vector>
#include "Population.h"

using namespace std;


int main()
{
	Population pop(200,0.02,"This is a test!");
	while (pop.maxFitness < 1) {
		pop.reproduce();
	}
}

