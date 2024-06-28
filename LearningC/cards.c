/*Randomly shuffle a deck of cards
Will then deal out a 7 card hand and evaluate the probability of combinaison for this hand*/

#include <stdio.h>
#include <time.h> 
#define DECK_LEN 52
#define HAND_LEN 7
#define FULL (DECK_LEN -1)
#define EMPTY -1

typedef enum suit{spade, club, heart, diamond}suit; //enum value for each suit of card
typedef struct card { suit s; int pips; }card; //card struct, pips are represented as an int 0-12 , 12 being king and 0 being ace
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

void ShuffleDeck(card deck[]) {
	int swapper = 0; //index of card to be swapped
	int i = 0; //counter
	card temp = { 0, 0 }; //temp holding place for swap
	srand(time(NULL)); //seed the random numbers with current time
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

int main(void)
{
	//set up deck and shuffle it
	stack_deck deck;
	SortDeck(deck.cards);
	deck.top = FULL;
	ShuffleDeck(deck.cards);

	//pick a hand and display it
	card hand[HAND_LEN];
	PickHand(hand, &deck);
	DisplayHand(hand);

	return 0;
}