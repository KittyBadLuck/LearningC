/*Store a atomic elements as a list, from user input
Store the name, symbol and weight
then print a table of it
by Lou de Tarade
29/06/2024*/

/*The ADT List
course example
Lou de Tarade
24/06/2024*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 30
#define S_MAX_LEN 3 //symbol max lenght

typedef struct list_atomic {char *name; char *s; double w; struct list_atomic* next; } list_atomic;
int is_empty(const list_atomic* l) { return(l == NULL); }

void print_list(list_atomic* h, char* title) //print a list of atomic elements
{
	printf("%s\n", title);
	printf("Name\t|\tSymbol\t|\tWeight\n");
	while (h != NULL)
	{
		printf("%s\t|\t%s\t|\t%.4lf\n", h->name, h->s , h->w);
		h = h->next;
	}
}

list_atomic* create_list( char name[], char s[], double w) //create a list of elements, with its name, symbol, and weight
{
	list_atomic* head = malloc(sizeof(list_atomic));
	head->name = strdup(name); //copy char to the list
	head->s = strdup(s);
	head->w = w;
	head->next = NULL;
	return head;
}

list_atomic* add_to_front(char name[], char s[], double w, list_atomic* h) // add an atomic element to the front of a list
{
	list_atomic* head = create_list(name, s , w);
	head->next = h;
	return head;
}


int main(void)
{
	//declaratiob
	list_atomic list_of_elem;
	list_atomic* head = NULL;
	head = malloc(sizeof(list_atomic));

	printf("Input which atomic elements you want to add\n");

	char name[MAX_LEN];
	char s[S_MAX_LEN];
	double w;

	int continue_add = 1;//int to check if user is finished

	while (continue_add)
	{

		printf("Input as name symbol weight\n");
		if (scanf("%s %s %lf", name, s, &w) != 3) //check Input
		{
			printf("Input was not entered correctly, please enter as : name(char) symbol(char) weight(float)\n");
			while ((getchar()) != '\n');// flush butter so the next iteration is correct
		}
		else
		{
			head = add_to_front(name, s, w, head); //add new elements to the list
			printf("Finished adding elements? : \n ");
			printf( "- Type 0 if you are finished and want to print the list  \n");
			scanf("%d", &continue_add); // ask if user want to another or break the loop
			printf("\n");
		}


	}
	
	print_list(head, "List of atomic elements : "); //print the final list
	printf("\n\n");

	return 0;
}