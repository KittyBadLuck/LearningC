/* The distance of a marathon in kilometers
Lou de Tarade
20/06/2024*/

#include <stdio.h>

int main()
{
	int miles = 26, yards = 385;
	int kilometers;
	kilometers = 1.609 * (miles + yards / 1760.0);
	printf("\nA marathon is %lf kilometers. \n\n", kilometers);
	return 0;
}

