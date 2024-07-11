/*C Program: dice probability
Lou de tarade
07/04/2024*/


//C VERSION
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define SIDES 6
//#define R_SIDE (rand()% SIDES + 1)
//
//int main()
//{
//
//	int trials;
//	int d1, d2;
//	int* outcomes;
//	int n_dice = 2;
//
//	srand(clock());
//	printf("\n Enter number of trials: ");
//	scanf("%d",&trials);
//	outcomes = (int*)malloc(sizeof(int) * trials);
//
//	for (int j = 0; j < trials; j++)
//		outcomes[(d1 = R_SIDE) + (d2 = R_SIDE)]++;
//	printf("probability\n");
//
//	for (int j = 2; j < n_dice * SIDES + 1; ++j)
//		printf("j = %d p=%lf\n", j, (double)(outcomes[j]) / trials);
//
//	return 0;
//}

//C++ VERSION
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int sides = 6;
inline int r_sides() { return(rand() % sides + 1); }

int main()
{
	int d1, d2;

	const int n_dice = 2;


	srand(clock());
	cout <<"\n Enter number of trials: ";

	int trials;
	cin >> trials;
	int* outcomes = new int[n_dice * sides +1];

	for (int j = 0; j < trials; j++)
		outcomes[(d1 = r_sides()) + (d2 = r_sides())]++;
	cout <<"probability\n";

	for (int j = 2; j < n_dice * sides + 1; ++j)
		cout <<"j = " << j  << " p = " << static_cast<double>(outcomes[j]) / trials << endl;

	return 0;
}