/* Print a table of sin and cosine between 0 and 1
Lou de Tarade
20/06/2024*/

#include<stdio.h>
#include<math.h> 
int main(void)
{
	//declaration
	double interval, sineValue, cosineValue;
	int i;


	for (i = 0; i <= 10; i++) // we need to use an int, so we make the loop between 1 and 10 
	{
		interval = i / 10.0; // divide by 10 to get back a result between 0 and 1

		sineValue = sin(interval); // calculate sine value
		cosineValue = cos(interval); // calculate cosine value

		printf("sin(%lf) = %lf \t cosine(%lf) = %lf \n", interval, sineValue , interval , cosineValue); //print result in new line
	}


	printf("\n++++++ + \n");
	return 0;
}