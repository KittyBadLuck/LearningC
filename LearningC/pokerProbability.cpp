/*Calculate the probability of a hand in Poker
25/07/2024*/
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

enum class suit: short {SPADE, HEART, DIAMOND, CLUB};

ostream& operator<< (ostream& out, const suit& s)
{
	switch (s)
	{
	case suit::SPADE: out << "SPADE";break;
	case suit::HEART: out << "HEART"; break;
	case suit::DIAMOND: out << "DIAMOND"; break;
	case suit::CLUB: out << "CLUB"; break;
	}

	return out;
}

class pips {
public:
	pips(int val) : v(val) { assert(v > 0 && v < 14); }
	friend ostream& operator<< (ostream& out, const pips& p);
	int get_pips() { return v; }
private:
	int v;
};

ostream& operator<<(ostream& out, const pips& p)
{
	out << p.v; //presumes  << overload for pips and suit
	return out;
}

class card
{
public:
	card():s(suit::SPADE), v(1){}
	card(suit s, pips v):s(s),v(v){}
	friend ostream& operator<< (ostream& out, const card& c);
	suit get_suit() const { return s; }
	pips get_pips() const { return v; }
private:
	suit s;
	pips v;
};

ostream& operator<<(ostream& out, const card& c)
{
	out << c.v << " of " << c.s; //presumes  << overload for pips and suit
	return out;
}

void init_deck(vector<card>& d)
{
	for (int i = 1; i < 14; ++i)
	{
		card c(suit::SPADE, i);
		d[i - 1] = c;
	}
	for (int i = 1; i < 14; ++i)
	{
		card c(suit::HEART, i);
		d[i + 12] = c;
	}
	for (int i = 1; i < 14; ++i)
	{
		card c(suit::DIAMOND, i);
		d[i + 25] = c;
	}
	for (int i = 1; i < 14; ++i)
	{
		card c(suit::CLUB, i);
		d[i +38] = c;
	}

}

void print(vector<card>& deck)
{
	for (auto card_val:deck)
		cout << card_val << "\t";
	cout << endl;
}

bool is_flush(vector <card>& hand)
{
	short s_cnt =0, h_cnt=0, d_cnt=0, c_cnt=0; //count for each suit
	for (auto p = hand.begin(); p != hand.end(); ++p) //check how many of each suit there is
	{
		if (p->get_suit() == suit::SPADE) s_cnt++;
		if (p->get_suit() == suit::HEART) h_cnt++;
		if (p->get_suit() == suit::DIAMOND) d_cnt++;
		if (p->get_suit() == suit::CLUB) c_cnt++;
	}

	if(s_cnt >= 5 || h_cnt >=5 || d_cnt >= 5 || c_cnt >= 5)  // if 5 of same suit was found, then its a flush
		return true;
	return false;
}

bool is_straight(vector<card>& hand , vector<card> * picked_hand = nullptr)
{
	vector<int> pips_v(hand.size());
	int index = 0;

	for (auto p = hand.begin(); p != hand.end(); ++p)
		pips_v[index++] = (p->get_pips()).get_pips();

	sort(pips_v.begin(), pips_v.end()); //stl iterator range

	if (picked_hand != nullptr)picked_hand->clear();
	
	for (int i = 0; i < (hand.size() - 4); i++)
		for (int j = 0; j < 5; ++j)
		{
			if ((j + i + 1) < hand.size()) { //verify size
				
				if (pips_v[j + i] == pips_v[j + i + 1] - 1)
				{
					if (picked_hand != nullptr) { picked_hand->push_back(hand[j + i]); }
				}
				else
				{
					if (picked_hand != nullptr) picked_hand->clear();
					break;
				}
			}
			else
			{
				if (picked_hand != nullptr)
				{
					picked_hand->push_back(hand[j + i]);
				}
				return true;
			}
				
		}
	return false;

	//int pips_v[5], i = 0;
	//for (auto p = hand.begin(); p != hand.end(); ++p)
	//	pips_v[i++] = (p->get_pips()).get_pips();

	//sort(pips_v, pips_v + 5); //stl iterator range

	//if (pips_v[0] != 1) //non aces
	//	return (pips_v[0] == pips_v[1] - 1 && pips_v[1] == pips_v[2] - 1)
	//	&& (pips_v[2] == pips_v[3] - 1 && pips_v[3] == pips_v[4] - 1); //verify if all values are equal to (next value - 1)
	//else //aces have a special logic
	//	return(pips_v[0] == pips_v[1] - 1 && pips_v[1] == pips_v[2] - 1)
	//	&& (pips_v[2] == pips_v[3] - 1 && pips_v[3] == pips_v[4] - 1) //verify for when aces is lowest card
	//	|| (pips_v[1] == 10) && (pips_v[2] == 11) && (pips_v[3] == 12)
	//	&& (pips_v[4] == 13); //verify when aces is hightest card

} 

bool is_straight_flush(vector <card>& hand)
{
	vector<card> best_hand(5);
	if (is_straight(hand, &best_hand))
		return is_flush(best_hand);
	else
		return false;
}

bool is_4of_akind(vector<card>& hand)
{
	int i = hand[0].get_pips().get_pips();
	int same_count = 0;
	for (auto p = ++hand.begin(); p != hand.end(); ++p)
		if (i == p->get_pips().get_pips())
			same_count++;
	if (same_count >= 4)
		return true;
	return false;
}

int main()
{

	vector <card> deck(52);
	srand(time(0));
	init_deck(deck);

	int how_many;
	int flush_count = 0;
	int str_count = 0;
	int str_flush_count = 0;

	vector<card> hand;

	//hand.push_back((*new card(suit::DIAMOND, 1)));
	//hand.push_back((*new card(suit::DIAMOND, 2)));
	//hand.push_back((*new card(suit::DIAMOND, 5)));
	//hand.push_back((*new card(suit::DIAMOND, 6)));
	//hand.push_back((*new card(suit::DIAMOND, 7)));
	//hand.push_back((*new card(suit::DIAMOND, 8)));
	//hand.push_back((*new card(suit::DIAMOND, 9)));

	//std::cout << "is flush " << is_flush(hand) << endl;
	//std::cout << "is straight " << is_straight(hand) << endl;
	//std::cout << "is straight flush " << is_straight_flush(hand) << endl;

	std::cout << "How many shuffles? : ";
	std::cin >> how_many;

	for (int loop = 0; loop < how_many; ++loop) //run simulation
	{
		random_shuffle(deck.begin(), deck.end()); //STL algorithm
		vector<card> hand(7);
		int i = 0;
		for (auto p = deck.begin(); i < 7; ++p)
			hand[i++] = *p;
		if (is_flush(hand)) flush_count++;
		if (is_straight(hand)) str_count++;
		if (is_straight_flush(hand)) str_flush_count++;
	}

	std::cout << "Flushes " << flush_count << " out of " << how_many << endl;
	std::cout << "Straights " << str_count << " out of " << how_many << endl;
	std::cout << "Straight Flushes " << str_flush_count << " out of " << how_many << endl;
}