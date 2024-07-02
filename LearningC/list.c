/*The ADT List
course example
Lou de Tarade
24/06/2024*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct list { int data; struct list* next; } list;
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

list* create_list(int d)
{
	list* head = malloc(sizeof(list));
	head->data = d;
	head->next = NULL;
	return head;
}

list* add_to_front(int d, list* h)
{
	list* head = create_list(d);
	head->next = h;
	return head;
}

list* array_to_list(int d[], int size)
{
	list* head = create_list(d[0]);
	int i;
	for (i = 1; i < size; i++)
	{
		head = add_to_front(d[i], head);
	}
	return head;
}

void delete(list* elem, list** prev, list** hd)
{
	if (*hd == *prev)
		*hd = elem->next;
	else
		(*prev)->next = elem->next;
	free(elem);
}

void delete_list(list* h)
{
	list* temp;
	if (h != NULL)
	{
		temp = h;
		delete_list(h = h->next);
		free(temp);
	}
}

void concat(list* h1, list* h2)
{
	if (h1 == NULL)
		h1 = h2;
	else if (h1->next == NULL)
		h1->next = h2;
	else
		concat(h1->next, h2);
}
int count(list* h)
{
	int cnt = 0;
	while (h != NULL)
	{
		cnt++;
		h = h->next;
	}
	return cnt;
}
int main(void)
{
	list list_of_int;
	list* head = NULL;
	head = malloc(sizeof(list));

	printf("sizeof(list) = %lu\n", sizeof(list)); //unsigned long
	head->data = 5; 
	head->next = NULL;

	//print_list(head, "single element list");
	//printf("\n\n");

	int data[6] = { 2,3,5,7,8,9 };
	head = array_to_list(data, 6);

	//print_list(head, "array to list ");
	//printf("\n\n");

	//test delete 
	list* head1 = NULL, * head2 = NULL;
	int data2[] = { 17,6,99 };
	head1 = array_to_list(data, 6);
	head2 = array_to_list(data2, 3);
	print_list(head1, "data[6] made into a 6 elem list");
	print_list(head2, "data2[3] made into a 3 elem list");
	concat(head1, head2);
	print_list(head1, "concat list");
	printf("\n Size of concat list is %d\n", count(head1));
	delete(head1, &head1, &head1);
	print_list(head1, "delete from list");
	delete(head1->next->next, &head1->next, &head1);
	print_list(head1, "delete from list");

	printf("\n\n");

	return 0;
}