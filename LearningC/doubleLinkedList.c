/*Double Linked list
Lou de Tarade
29/06/2024*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RAND 49

typedef struct list { int data; struct list* next; struct list* prev; } list;
int is_empty(const list* l) { return(l == NULL); }

void print_list(list* h, char* title)
{
	printf("%s\n", title);
	while (h != NULL)
	{
		printf("%d :", h->data);
		h = h->next;
	}
}

list* create_list(int d) //create a list
{
	list* head = malloc(sizeof(list));
	head->data = d;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

list* add_to_front(int d, list* h)  //add a list elemen to the front
{
	list* head = create_list(d);
	head->next = h;
	h->prev = head;
	return head;
}

list* add_to_tail(int d, list* t)//add a list element to the end 
{
	list* tail = create_list(d);
	tail->prev = t;
	t->next = tail;
	return tail;
}

list* array_to_list(int d[], int size)
{
	list* head = create_list(d[0]);
	list* tail = add_to_tail(d[1], head);

	int i;
	for (i = 2; i < size; i++)
	{
		tail = add_to_tail(d[i], tail);
	}
	return head;

}

void remove_duplicate(list* h)// remove duplicated data in a list
{
	list* head = h;
	list* searching_h; //list reference for searching

	while (head != NULL)//verify all value
	{
		searching_h = head->next; //get next value and compare

		while (searching_h != NULL)
		{
			if (head->data == searching_h->data)
			{
				//remove the element, by assigning the correct value to its previous and next element
				if (searching_h->next == NULL) 
				{
					searching_h->prev->next == NULL; //if null, return null
				}
				else
				{
					searching_h->prev->next = searching_h->next;
					searching_h->next->prev = searching_h->prev;
				}
			}
			searching_h = searching_h->next; //cherche next
		}
		head = head->next;
	}

}

int main(void)
{
	list list_of_int;
	list* head = NULL;
	head = malloc(sizeof(list));
	srand(time(0));
	int data[200];
	for (int i=0; i < 200; i++)
	{
		data[i] = rand() % (MAX_RAND + 1);
	}

	head = array_to_list(data, 200);
	remove_duplicate(head);

	print_list(head, "array to double linked list ");
	printf("\n\n");

	return 0;
}