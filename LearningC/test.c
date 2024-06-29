#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 52
typedef enum { diamonds, hearts, clubs, spades }suit;
typedef enum { ace, jack, queen, king }honour;
typedef struct
{
	suit suit_card;
	honour honour_card;
	short pips_card;
}card;
void swap(card* a, card* b)
{
	card temp = *a;
	*a = *b;
	*b = temp;
}
void printArray(card arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d %d//", arr[i].suit_card, arr[i].pips_card);
	printf("\n");
}
void shuffle(card arr[], int n)//function that generates random permutation of arr[](Fisher-yates algorithm)
{
	int i, j;
	srand(time(NULL));
	for (int i = n - 1; i > 0; i--) //we start from the last element, swap one by one
	{
		int j = rand() % (i + 1);//random index from 0 to i
		swap(&arr[i], &arr[j]);//swap arr[i] with element at random index														
	}
}
void approx_to_prob_onePair(card arr[], int n)
{
	int N = 0;
	int c = 0, d = 0;
	printf("Enter number of hands for sampling:");// enter 1 000 000
	scanf("%d", &N);
	for (int i = 0; i <= N; i++)
	{
		shuffle(arr, SIZE);
		for (int j = 0; j < 7; j++)
		{
			for (int k = j + 1; k < 7; k++)
			{
				if (arr[j].pips_card == arr[k].pips_card || arr[j].honour_card == arr[k].honour_card)
				{
					c = c + 1;
				}

			}

		}

	}
	printf("%d\n", c);
	double approxProb = c / N;
	printf("%.9fl", approxProb);
}

int main()
{
	card c1 = { .suit_card = hearts, .pips_card = 2 };
	card c2 = { .suit_card = hearts, .pips_card = 3 };
	card c3 = { .suit_card = hearts, .pips_card = 4 };
	card c4 = { .suit_card = hearts, .pips_card = 5 };
	card c5 = { .suit_card = hearts, .pips_card = 6 };
	card c6 = { .suit_card = hearts, .pips_card = 7 };
	card c7 = { .suit_card = hearts, .pips_card = 8 };
	card c8 = { .suit_card = hearts, .pips_card = 9 };
	card c9 = { .suit_card = hearts, .pips_card = 10 };
	card c10 = { .suit_card = hearts, .honour_card = ace };
	card c11 = { .suit_card = hearts, .honour_card = jack };
	card c12 = { .suit_card = hearts, .honour_card = queen };
	card c13 = { .suit_card = hearts, .honour_card = king };
	card c14 = { .suit_card = diamonds, .pips_card = 2 };
	card c15 = { .suit_card = diamonds, .pips_card = 3 };
	card c16 = { .suit_card = diamonds, .pips_card = 4 };
	card c17 = { .suit_card = diamonds, .pips_card = 5 };
	card c18 = { .suit_card = diamonds, .pips_card = 6 };
	card c19 = { .suit_card = diamonds, .pips_card = 7 };
	card c20 = { .suit_card = diamonds, .pips_card = 8 };
	card c21 = { .suit_card = diamonds, .pips_card = 9 };
	card c22 = { .suit_card = diamonds, .pips_card = 10 };
	card c23 = { .suit_card = diamonds, .honour_card = ace };
	card c24 = { .suit_card = diamonds, .honour_card = jack };
	card c25 = { .suit_card = diamonds, .honour_card = queen };
	card c26 = { .suit_card = diamonds, .honour_card = king };
	card c27 = { .suit_card = clubs, .pips_card = 2 };
	card c28 = { .suit_card = clubs, .pips_card = 3 };
	card c29 = { .suit_card = clubs, .pips_card = 4 };
	card c30 = { .suit_card = clubs, .pips_card = 5 };
	card c31 = { .suit_card = clubs, .pips_card = 6 };
	card c32 = { .suit_card = clubs, .pips_card = 7 };
	card c33 = { .suit_card = clubs, .pips_card = 8 };
	card c34 = { .suit_card = clubs, .pips_card = 9 };
	card c35 = { .suit_card = clubs, .pips_card = 10 };
	card c36 = { .suit_card = clubs, .honour_card = ace };
	card c37 = { .suit_card = clubs, .honour_card = jack };
	card c38 = { .suit_card = clubs, .honour_card = queen };
	card c39 = { .suit_card = clubs, .honour_card = king };
	card c40 = { .suit_card = spades, .pips_card = 2 };
	card c41 = { .suit_card = spades, .pips_card = 3 };
	card c42 = { .suit_card = spades, .pips_card = 4 };
	card c43 = { .suit_card = spades, .pips_card = 5 };
	card c44 = { .suit_card = spades, .pips_card = 6 };
	card c45 = { .suit_card = spades, .pips_card = 7 };
	card c46 = { .suit_card = spades, .pips_card = 8 };
	card c47 = { .suit_card = spades, .pips_card = 9 };
	card c48 = { .suit_card = spades, .pips_card = 10 };
	card c49 = { .suit_card = spades, .honour_card = ace };
	card c50 = { .suit_card = spades, .honour_card = jack };
	card c51 = { .suit_card = spades, .honour_card = queen };
	card c52 = { .suit_card = spades, .honour_card = king };
	card cardarray[] = { c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23,c24,c25,c26,c27,c28,c29,c30,c31,c32,c33,c34,c35,c36,c37,c38,c39,c40,c41,c42,c43,c44,c45,c46,c47,c48,c49,c50,c51,c52 };
	approx_to_prob_onePair(cardarray, SIZE);
}