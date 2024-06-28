/*Print a date for different days. Can also get the next day
by Lou de Tarade
27/06/2024*/

#include <stdio.h>


typedef enum month{jan,feb,mar,apr,may,jun,jul,aug,sept,oct,nov,dec}month;//declare month enum
typedef struct date { month m; int d; }date;
enum month next_month(enum month m) { return((m + 1) % 12); } //get next month
int next_day(int d, int max_date) {return((d + 1)% max_date); } //get next day, second input is the max day in month (30,31 or 28)

struct date next_date(const date *current_date) // return the next date for a given date
{
	date next_d = { jan, 0 };//cannot be 0, if thats the case, that means it was not assigned
	switch (current_date->m)
	{
	case jan: //all month of 31 days are combined
	case mar:
	case may:
	case jul:
	case aug:
	case oct:
	case dec: 
		next_d.d = next_day(current_date->d, 31);
		if (next_d.d == 1)//if the day is 1, it means we changed month, so get the next one
			next_d.m = next_month(current_date->m);
		else
			next_d.m = (current_date->m);
		break;

	case apr://all month of 30 days are combined
	case jun:
	case sept:
	case nov:
		next_d.d = next_day(current_date->d, 30);
		if (next_d.d == 1) //if the day is 1, it means we changed month, so get the next one
			next_d.m = next_month(current_date->m);
		else
			next_d.m = (current_date->m);
		break;

	case feb: //we assume febuary as 28 day
		next_d.d = next_day(current_date->d, 28);
		if (next_d.d == 1)//if the day is 1, it means we changed month, so get the next one
			next_d.m = next_month(current_date->m);
		else
			next_d.m = (current_date->m);
		break;
	}

	return next_d;
}

int print_date(const date current_date) //print the inputed date as Month Day
{
	switch (current_date.m)
	{
	case jan: printf("January"); break;
	case feb: printf("Febuary"); break;
	case mar: printf("March"); break;
	case apr: printf("April"); break;
	case may: printf("May"); break;
	case jun: printf("June"); break;
	case jul: printf("July"); break;
	case aug: printf("August"); break;
	case sept: printf("September"); break;
	case oct: printf("October"); break;
	case nov: printf("November"); break;
	case dec: printf("December"); break;
	}
	printf(" %d", current_date.d);
	return 0;
}

int print_day_and_next(const date current_date) //print the current date and the next one
{
	printf("Current date is ");
	print_date(current_date);
	printf(" and next day is ");
	print_date(next_date(&current_date));

	printf("\n");
	return 0;
}

int main(void)
{
	date current_date = { jan, 1 };
	print_day_and_next(current_date);

	current_date.m = feb;
	current_date.d = 28;
	print_day_and_next(current_date);

	current_date.m = mar;
	current_date.d = 14;
	print_day_and_next(current_date);

	current_date.m = oct;
	current_date.d = 31;
	print_day_and_next(current_date);

	current_date.m = dec;
	current_date.d = 31;
	print_day_and_next(current_date);
	
	return 0;
}