#include <iostream>
#include <cstdlib>
using namespace ::std;



//draw a random generated graph
bool** graph;
	srand(time(0)); //see rand()
	graph = new bool* [size];
	for (int i = 0; i < size; ++i)
	{
		graph[i] = new bool[size];
	}

	//generate nodes with 0.19 being the density
	for (int i = 0; i < size; ++i)
		for (int j = i; j < size; ++i)
			if (i == j) graph[i][j] = false;
				else graph[i][j] = (prob() < 0.19);