/* Use File I/O
Open and read a file of integers into an array that is created with the first integer telling you how many to read.
Print the min, max and average .
Lou de Tarade
02/07/2024*/

#include <stdio.h>
#include <stdlib.h>


void read_data(FILE* ptr, int d[], int size)
{
	int i = 0;
	int value = 0; //used for checking
	rewind(ptr);
	for (i = 0; i <= size; i++)
	{
		if (i == 0)
			fscanf(ptr, "%*d"); //skip first
		else
			if (fscanf(ptr, "%d", &d[i - 1]) != 1)
				printf("no proper value found at the %d position", i - 1);
				d[i-1] = 0;
	}
}

int find_size(FILE* ptr) //find the size of the array to create with first value
{
	int sz;
	rewind(ptr);
	fscanf(ptr, "%d", &sz);
	return sz;
}

void print_data(int d[], int size, FILE* ofp) //print data of array of int to string to screen and file
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d\t", d[i]);
		fprintf(ofp,"%d\t", d[i]);
		if ((i + 1) % 10 == 0)
		{
			fprintf(ofp, "\n");
			printf("\n");
		}
	}
}

int find_max(int d[], int size) //find the max value of an array of int
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (d[i] > max)
			max = d[i];
	}

	return max;
}

double average(int d[], int size) //return average of an array of int as a double
{
	int i;
	double avg = 0.0;

	for (i = 0; i < size; i++)
	{
		avg += d[i];
	}

	return (avg / size);
}

int main(int argc, char*argv[])
{

	if (argc != 3) //verify number of args
	{
		printf("Need executable inputfile outputfile \n");
		exit(1);
	}

	//declarations
	int i;
	FILE* ifp,* ofp;
	double avg;
	int max;

	ifp = fopen(argv[1], "r");
	ofp = fopen(argv[2], "w+");

    int sz = find_size(ifp);

	int* data;
	data = (int*)malloc(sizeof(int) * sz);

	read_data(ifp, data, sz);

	//print everything
	fflush(ofp);
	fprintf(ofp, "List of %d int is: ", sz);
	printf("List of %d int is: ", sz);
	print_data(data, sz, ofp);

	avg = average(data, sz);
	fprintf(ofp, "\n average was %10f", avg );
	printf( "\n average was %10f", avg);

	max = find_max(data, sz);
	fprintf(ofp, "\n max was %d", max);
	printf("\n max was %d", max);


	fprintf(ofp, "\n\n");
	printf("\n\n");


	fclose(ifp);
	fclose(ofp);

	return 0;
}