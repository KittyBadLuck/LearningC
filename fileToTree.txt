/* Use File I/O
Open and read a file of integer pairs into an array that is created with the first integer telling you how many to read.

So  4 9  11  4  5    would mean create an integer array size 4 and read into data[].

Write a routine that places these values into a binary tree structure. Then walk the tree “inorder” and print these values to the screen.
Lou de Tarade
02/07/2024*/

#include <stdio.h>
#include <stdlib.h>


typedef int DATA; //data for node tree
struct node { DATA d; struct node* left; struct node* right; }; // node structure

typedef struct node NODE;
typedef NODE* BTREE; 

BTREE new_node(void) { return(malloc(sizeof(NODE))); }//create an empty node

BTREE init_node(DATA d1, BTREE p1, BTREE p2) //initialize node
{
	BTREE t;
	t = new_node();
	t->d = d1;
	t->left = p1;
	t->right = p2;
	return t;
}

BTREE create_tree(DATA a[], int i, int size)// create a tree from an array, recursivly
{
	if (i >= size)
		return NULL;
	else
		return(init_node(a[i],
			create_tree(a, 2 * i + 1, size),
			create_tree(a, 2 * i + 2, size)));
}


void read_data(FILE* ptr, int d[], int size) // read data from a file and input it in an array
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
			{
				d[i - 1] = 0;
			}
	}
}

int find_size(FILE* ptr) //find the size of the array to create with first value
{
	int sz;
	rewind(ptr);
	fscanf(ptr, "%d", &sz);
	return sz;
}


void inorder(BTREE root) //print a binary tree in order
{
	if (root != NULL)
	{
		inorder(root->left);
		printf(" %d ", root->d);
		inorder(root->right);
	}
}

int main(int argc, char* argv[])
{

	if (argc != 2) //verify number of args
	{
		printf("Need executable inputfile \n");
		exit(1);
	}

	//declarations
	int i;
	FILE* ifp, * ofp;

	ifp = fopen(argv[1], "r");

	if (ifp == NULL) //verify that file was opened
	{
		printf("Error reading file %s", argv[1]);
		exit(1);
	}

	int sz = find_size(ifp);

	int* data;
	data = (int*)malloc(sizeof(int) * sz);

	read_data(ifp, data, sz); //get data

	BTREE b;
	b = create_tree(data, 0, sz); //create tree from data
	printf("Binary Tree of %d node in order:", sz);
	inorder(b); //print tree

	printf("\n\n");


	fclose(ifp);

	return 0;
}
