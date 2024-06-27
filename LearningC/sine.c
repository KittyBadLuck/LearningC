/* Return the sine of a value  between 0 and 1
Lou de Tarade
21/06/2024*/

#include <stdio.h>
#include <math.h>

int main()
{
	double sinValue, x;

	printf("Enter value to calculate sine between 0 and 1 : ");
	scanf(" %lf", &x);
	if (x <= 0 || x >= 1)
	{
		printf("Invalid Input, please enter a value between 0 and 1 (non inclusive)\n");
		return 1;
	}
	else
	{
		sinValue = sin(x);
		printf("sin of %lf is %lf\n", x, sinValue);
		return 0;
	}

}

