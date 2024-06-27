/* Compute the average weight for a population of elephant seals
Lou de Tarade
25/06/2024*/

#include <stdio.h>
#define SIZE 1000 //constant size of array

double average(int list[], int size)
{/*Returns the average of the array "list" as a double. "list" must be the same size as "size"*/
	double sum = 0.0;
	for (int i = 0; i < size; i++)
	{
		sum += list[i];
	}

	return sum/size;
}

int main(void)
{
	//declarations
	int weights[SIZE] = {0}; //all values will be set to 0 by defaults

	FILE* fp = fopen("elephant_seal_data.txt", "r"); // open and read file
	int i = 0; 
	int num;

	if (fp == NULL)
	{
		perror("Error opening file");
		return 1; // failed to open file, exit program
	}
	printf("List of recorded weights: \n");
	while (fscanf(fp, "%d", &num) > 0) //get each int in file and assign its value to the array
	{
		if (i >= SIZE)
		{
			break; //detect if more data is in the txt file, and if its the case, stop the loop;
		}
		printf("%d \t", num);
		weights[i] = num; 
		i++;

	}
	printf("\n");
	fclose(fp); //close file once finished

	printf("The average weight for a population of %d elephant seals is %.2f \n", SIZE, average(weights, SIZE));


}