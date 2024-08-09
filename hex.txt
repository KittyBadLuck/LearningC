/*Dijikstra Shortest Path Algorithms + Minimum spanning Tree
* Ideally, I would have cut this code between different files so it is easier to read
* for this exercise everything had to be in the same file
Lou de Tarade
23/07/2024*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cassert>
#include <random>
#include <algorithm>
#include <limits>
using namespace std;

enum class Color { RED, BLUE, BLANK};

ostream& operator<<(ostream& out, Color c)
{
	switch (c)
	{
	case Color::RED:out << "R"; break;
	case Color::BLUE: out << "B"; break;
	case Color::BLANK: out << "."; break;
	}
	return out;
}
//PRIORITT QUEUE
template  <typename T>
class PriorityQueue
{
public:
	PriorityQueue() = default;
	~PriorityQueue() { clear(); }
	void clear() { Q.clear(); };
	bool contains(T elem)
	{
		for (int i = 0; i < this->size(); i++)
			if (this->Q[i].value == elem)
				return true; //verify value
		return false;//if no value found -> return false
	}
	bool insertElem(T value, double priority)
	{
		if (this->contains(value))
			return false;
		this->Q.push_back(HeapNode(value, priority));
		make_heap(this->Q.begin(), this->Q.end(), compare_Heap());
		sort_heap(this->Q.begin(), this->Q.end(), compare_Heap());

		return true;
	}

	T top() { return Q.front().value; } //return top node
	int size() { return Q.size(); } //return size of queue
	T bottom() { return Q.back().value; } //return bottom node
	void print()
	{
		for (auto elem : Q)
		{
			cout << elem.value << " priority : " << elem.priority << endl;
		}
	}

private:
	struct HeapNode //struct so i can have custom priority for each nodes
	{
		T value;
		double priority;
		HeapNode(T value, double priority) : value(value), priority(priority) {}
	};
	struct compare_Heap { //struct to compare the Nodes by priority and make a priority queue
		bool operator()(HeapNode const& a, HeapNode const& b) const {
			return a.priority < b.priority;
		}
	};
	vector<HeapNode> Q;
};


//NODE
class Node
{
public:
	Node() : x(0), y(0) {}
	Node(int x, int y, Color c = Color::BLANK) : x(x), y(y), c(c) {}

	friend ostream& operator<< (ostream& out, const Node& n)
	{
		out << n.x << " , " << n.y << " : " << n.c;
		return out;
	}
	inline int getX() const { return x; }
	inline int getY() const { return y; }
	inline Color getC() const { return c; }
	inline void setX(int i) { x = i; }
	inline void setY(int i) { y = i; }
	inline void setC(Color color) { c = color; }
private:
	int x, y;
	Color c;

};
//BOARD
class Board
{
public:
	Board(int size = 11);
	~Board() { board.clear(); }
	void printBoard(); 
	bool place(int x, int y, Color c);
	vector<Node*> getNeighbors(int x, int y, Color c = Color::BLANK); //return the surrounding tiles , of corresponding colors
	bool is_legal(int x, int y);
	bool hasWin(int x, int y, Color c); // verify if a win is found from the last postion
	int getSize() { return size; }
	Node* getNode(int x, int y) { return board[x][y]; }
private:
	int size;
	string line;
	vector<vector<Node*>> board;
};

//AI 
class AI
{
public:
	~AI() { moves.clear(); }
	pair<int, int> nextMove(Board& board, Color comp);
private:
	bool minVisited, maxVisited;
	vector<Node*> moves;
};

//GAME
class Game
{
public:
	void play();
	void setup(); //set up size of board and ask to choose colors
	bool playerTurn();
	bool computerTurn(); 
	void win(Color winner); //print win or loose message
private:
	Color player;
	Color computer;
	AI computerAI;
	Board board;
};

//MAIN
int main()
{
	Game g;
	g.play();
}

//------BOARD Methods---------
Board::Board(int size) : size(size), board(vector<vector<Node*>>(size))
{
	assert(size > 0);
	line = "\\";                  
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
			line += " / \\"; //automatic line creation depending on size
		for (int j = 0; j < size; j++)
		{
			board[i].push_back(new Node(i, j));
		}	
	}	
}

bool Board::place(int x, int y, Color c)
{
	if (is_legal(x, y))
	{
		board[x][y]->setC(c); 
		return true;
	}
		
	return false;
}

bool Board::is_legal(int x, int y)
{
	if (x >= size || x < 0) return false;
	if (y >= size || y < 0) return false;
	if (board[x][y]->getC() != Color::BLANK) return false;
	return true;
}

void Board::printBoard()
{
	cout << "  0"; //indicate coordinates on the sides
	for (int i = 1; i < size; i++)
		cout << " b " << i; // b = blue side
	cout << endl;

	// print the first line
	cout << "0 " << board[0][0]->getC();
	for (int i = 1; i < size; i++)
		cout << "---" << board[i][0]->getC();
	cout << endl;

	
	string indent = "";
	for (int i = 1; i < size; i++)
	{
		indent += ' ';
		cout << indent << "r " << line << endl; //r = red side
		if (i < 10)
		{
			indent += ' ';
			cout << indent << i << ' ' << board[0][i]->getC();
		}
		else
		{
			cout << indent << i << ' ' << board[0][i]->getC();
			indent += ' ';
		}

		for (int j = 1; j < size; j++)
			cout << "---" << board[j][i]->getC();
		cout << endl;
	}

	cout << "_________________________________________________________" << endl;
}

vector<Node*> Board::getNeighbors(int x, int y, Color c)
{
	vector<Node*> nb;

	assert(x >= 0 && x < size);
	assert(y >= 0 && y < size);

	//all posible surrounding position
	vector<pair<int, int>> positions = { 
		make_pair(x - 1,y),
		make_pair(x,y - 1),
		make_pair(x + 1,y - 1),
		make_pair(x + 1,y),
		make_pair(x - 1,y + 1),
		make_pair(x,y + 1),
	};

	//filter and remove position that are the wrong color
	//or position outside of board
	for (auto pos : positions)
	{
		if (pos.first >= 0 && pos.first < size
			&& pos.second >= 0 && pos.second < size)
		{
			if (board[pos.first][pos.second]->getC() == c)
			{
				nb.push_back(board[pos.first][pos.second]);
			}
		}
	}

	return nb;
}

bool Board::hasWin(int x, int y, Color c) //verify if the border of corresponding colors are touching
{
	vector<Node*> closeSet;
	vector<Node*> openSet;

	closeSet.push_back(board[x][y]);

	vector<Node*> nb = getNeighbors(x,y,c);
	openSet.insert(openSet.end(), nb.begin(), nb.end());

	bool minVisited = false, maxVisited= false; //verify if one edge is found;
	if (c == Color::BLUE)
	{
		if (y == 0) minVisited = true;
		if (y == (size - 1)) maxVisited = true;
	}
	else if (c == Color::RED)
	{
		if (x == 0) minVisited = true;
		if (x == (size - 1)) maxVisited = true;
	}

	while (!openSet.empty())
	{
		closeSet.push_back(openSet.back());
		openSet.pop_back();
		if (c == Color::BLUE)
		{
			if (closeSet.back()->getY() == 0) 
				minVisited = true;
			if (closeSet.back()->getY() == (size - 1)) 
				maxVisited = true;
		}
		else if (c == Color::RED)
		{
			if (closeSet.back()->getX() == 0) 
				minVisited = true;
			if (closeSet.back()->getX() == (size - 1))
				maxVisited = true;
		}
		if (minVisited && maxVisited)
			return true; //true if both end are reached

		nb = getNeighbors(closeSet.back()->getX(), closeSet.back()->getY(), c);
		for (auto n : nb)
		{
			//verify if item is in close or open set
			int cnt = count(openSet.begin(), openSet.end(), n); 
			cnt += count(closeSet.begin(), closeSet.end(), n);
			
			if (cnt == 0)
				openSet.push_back(n);
		}
	}

	return false;

}

//--------AI Methods-----------
pair<int, int> AI::nextMove(Board& board, Color comp)
{
	pair<int, int> next;
	if (moves.empty()) //if first move, get one empty node in the middle
	{
		int half = board.getSize()/2;
		next.first = half;
		next.second = half;
		while (!board.is_legal(next.first, next.second))
			if (comp == Color::BLUE)
				next.second -= 1;
			else
				next.first -= 1;
	}
	else
	{
		PriorityQueue<Node*> possible_moves;
		for (auto m : moves)
		{
			vector<Node*> nb = board.getNeighbors(m->getX(), m->getY());
			//add all neighbors to a priority queue, their value depending of the Color (to get the min or max possible move)
			for (auto n : nb) 
			{
				if (comp == Color::BLUE)
				{
					possible_moves.insertElem(n, n->getY());
				}
				else
				{
					possible_moves.insertElem(n, n->getX());
				}
			}
		}
		if(minVisited == true) //if the minimum was reached, search for the max element, else the min
		{
			cout << "get max " << endl;
			next.first = possible_moves.bottom()->getX();
			next.second = possible_moves.bottom()->getY();
		}
		else
		{
			cout << "get min" << endl;
			next.first = possible_moves.top()->getX();
			next.second = possible_moves.top()->getY();
		}
	}
	if (comp == Color::BLUE)
	{
		if (next.second == 0) minVisited = true;
		else if (next.second == (board.getSize()-1)) maxVisited = true;
	}
	else
	{
		if (next.first == 0) minVisited = true;
		else if (next.first == (board.getSize()-1)) maxVisited = true;
	}

	moves.push_back(board.getNode(next.first, next.second));
	return next;
}

//------GAME Methods---------
void Game::play()
{
	char userIn;
	std::cout << "You challenged the computer to a game of hex" << endl << endl;
	setup();

	std::cout << "Setup finished! we can start to play" << endl;

	while (true)
	{
		if (player == Color::BLUE)
		{
			if (playerTurn())
			{
				win(player);
				break;
			}
			if (computerTurn())
			{
				win(computer); 
				break;
			}
				
		}
		else
		{
			if (computerTurn())
			{
				win(computer); 
				break;
			}
				
			if (playerTurn())
			{
				win(player); 
				break;
			}
				
		}
	}
}

void Game::setup()
{
	//choose board size
	std::cout << "Now setting up the game" << endl;
	std::cout << "How big should the board be? (7 - 11 recomended) ? ";
	int dimension;
	cin >> dimension;
	while (true)
	{
		if (cin.fail() || dimension <= 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "You have entered wrong input" << endl;
			cin >> dimension;
		}
		else
			break;
	}
	std::cout << endl;
	std::cout << "Board will be of size " << dimension << endl;
	board = Board(dimension);

	//choose side
	char side = 'w';
	std::cout << "Now choose your side, blue or red (blue will go first) (b/r) : ";
	cin >> side;
	while (true)
	{
		if (cin.fail() || ( side != 'r' && side != 'R' && side!= 'b' && side != 'B'))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "You have entered wrong input" << endl;
			cin >> side;
		}
		else
			break;
	}
	std::cout << endl;
	if (side == 'r' || side == 'R')
	{
		player = Color::RED;
		computer = Color::BLUE;
		std::cout << "You choose red, you will go second, and need to connect an horizontal line" << endl;
	}
	else
	{
		player = Color::BLUE;
		computer = Color::RED;
		std::cout << "You choose blue, you will go first, and need to connect an vertical line" << endl;
	}


}

void Game::win(Color winner)
{
	if (winner == player)
		cout << "You won ! Well played" << endl << endl;
	else
		cout << "You lost, sorry" << endl << endl;
}

bool Game::playerTurn() //player turn, return true for a win
{
	int x = -1, y =-1;
	bool legal = false;
	cout << "Player Turn :" << endl;
	
	cout << "Where do you want to put your piece ( x y ) : ";
	cin >> x >> y;
	while (true)
	{
		if (cin.fail() || !board.is_legal(x, y))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Not a valid move" << endl;
			cin >> x >> y;
		}
		else
			break;
	}
	cout << "You played " << x << " " << y << endl;
	board.place(x, y, player);
	board.printBoard();
	if (board.hasWin(x, y, player))
		return true;
	return false;
}

bool Game::computerTurn() //computer turn, return false for a win
{
	cout << "Computer turn" << endl;
	pair<int, int> next = computerAI.nextMove(board, computer);
	board.place(next.first, next.second, computer);
	cout << "Computer played " << next.first << " , " << next.second << endl;

	board.printBoard();

	if (board.hasWin(next.first, next.second, computer))
		return true;
	return false;
		
}

