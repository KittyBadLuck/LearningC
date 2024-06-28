/*Randomly shuffle a deck of cards
Will then deal out a 7 card hand and evaluate the probability of combinaison for this hand

by Lou de Tarade
28/06/2024*/

#include <stdio.h>
#include <time.h> 
#define DECK_LEN 52
#define HAND_LEN 7
#define FULL (DECK_LEN -1)
#define EMPTY -1
#define SAMPLE_SIZE 1000000

typedef enum suit{spade, club, heart, diamond}suit; //enum value for each suit of card
typedef struct card { suit s; short pips; }card; //card struct, pips are represented as an int 0-12 , 12 being king and 0 being ace
typedef struct stack_deck { card cards[DECK_LEN]; int top; }stack_deck;


int SortDeck(card deck[])//sort all cards in a deck in a proper order.
{
	
	for (int i = 0; i < 4; i++)//sort for each suit
	{
		for (int y = 0; y < 13; y++)//sort for each pips
		{
			deck[y + (13 * i)] = (card){ i, y };//assign new card
		}
	}
	return 0;
}

void ShuffleDeck(card deck[], int seedOffset) {
	int swapper = 0; //index of card to be swapped
	int i = 0; //counter
	card temp = { 0, 0 }; //temp holding place for swap
	srand(time(NULL)*seedOffset); //seed the random numbers with current time
	for (i = 0; i < DECK_LEN; i++) {
		//generate a pseudo-random number from 0 to 51
		swapper = rand() % DECK_LEN;
		//swap current card with the swapper
		temp = deck[i];
		deck[i] = deck[swapper];
		deck[swapper] = temp;
	}
}
card PopCard(stack_deck* deck) { return(deck->cards[deck->top--]); }//get the top card of the deck

int PickHand(card hand[], stack_deck* deck) //create a hand, picking the cards from the top of the deck 
{
	for (int i = 0; i < HAND_LEN; i++)
		hand[i] = PopCard(deck); 
	return 0;
}

void DisplayHand(card hand[]) //display the current hand
{
	for (int i = 0; i < HAND_LEN; i++)
	{
		switch (hand[i].pips)
		{
		case 0: printf("Ace"); break;
		case 10: printf("Jake"); break;
		case 11: printf("Queen"); break;
		case 12: printf("King"); break;
		default: printf("%d", hand[i].pips);
		}
		printf(" of ");

		switch (hand[i].s)
		{
		case spade: printf("Spade"); break;
		case club: printf("Club"); break;
		case heart: printf("Heart"); break;
		case diamond: printf("Diamond"); break;
		}
		printf("\n");
	}
}

int CalculateProbabilities()//calulate the probabilities of combinaison, with a SAMPLE_SIZE
{
	//declaration for number of combinaison found
	int no_pair =0;
	int one_pair = 0;
	int two_pair = 0;
	int three_of_kind = 0;
	int full_house = 0;
	int four_of_kind = 0;

	int total = 0;
	for (int i = 0; i < SAMPLE_SIZE; i++)
	{
		//set up deck and shuffle it. regenerate a deck each time to make sure that all probabilities are equal
		stack_deck deck;
		SortDeck(deck.cards);
		deck.top = FULL;
		ShuffleDeck(deck.cards, i);

		//pick a hand and display it.
		card hand[HAND_LEN];
		PickHand(hand, &deck);

		switch (CheckHand(hand))
		{
		case 1: one_pair++; break;
		case 2: two_pair++; break;
		case 3: three_of_kind++; break;
		case 4: four_of_kind++; break;
		case 5: full_house++; break;
		default: no_pair++;break;
		}
	}
	
	total = no_pair + one_pair + two_pair + three_of_kind + four_of_kind + full_house;
	printf("Probabilities of different combinaison for a sample size of %d :\n", SAMPLE_SIZE);
	printf("Hand\t|\tCombinations\t|\tProbabilities\n");
	printf("No Pair\t|\t%d\t|\t%f\n", no_pair, (no_pair * 1.0) / SAMPLE_SIZE);
	printf("One Pair\t|\t%d\t|\t%f\n", one_pair, (one_pair * 1.0) / SAMPLE_SIZE);
	printf("Two Pair\t|\t%d\t|\t%f\n", two_pair, (two_pair * 1.0) / SAMPLE_SIZE);
	printf("Three of Kind\t|\t%d\t|\t%f\n", three_of_kind, (three_of_kind * 1.0) / SAMPLE_SIZE);
	printf("Four of Kind\t|\t%d\t|\t%f\n", four_of_kind, (four_of_kind * 1.0) / SAMPLE_SIZE);
	printf("Full House\t|\t%d\t|\t%f\n", full_house, (full_house * 1.0) / SAMPLE_SIZE);
	printf("Total\t|\t%d\t|\t%f\n", total, (total * 1.0) / SAMPLE_SIZE);

	return 0;
}

int CheckHand(card hand[]) 
{ /*Check hand for combinaison. 
  0 = nothing; 1 = 1 pair, 2 = 2 pair ; 3 = 3 of kind
  4 = 4 of kind; 5 = full house */
	int pair_found = 0;
	int three_found = 0;
	int four_found = 0;
	int num_in_ranks[13] = { 0 }; //array with all ranks.


	for (int i = 0; i < HAND_LEN; i++)
		num_in_ranks[hand[i].pips]++; //read all cards and add how many there are in each rank

	for (int rank = 0; rank < 13; rank++)
	{
		switch (num_in_ranks[rank])//check how many of each rank there is, and increment corresponding values
		{
		case 4: four_found++; break;
		case 3: three_found++; break;
		case 2: pair_found++; break;
		}
	}

	//return correct int
	if (three_found && pair_found) return 5;
	if (four_found) return 4;
	if (three_found && !pair_found) return 3;
	if (pair_found == 2) return 2;
	if (pair_found == 1) return 1;

	return 0; //if the loop finish, it means no four of kind was found before
}

int main(void)
{

	CalculateProbabilities();

	return 0;
}
