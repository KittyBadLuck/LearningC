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

inline double prob() { return (1.0 * rand() / RAND_MAX); } //prob between 0 and 1

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
	Board(const Board& b); //copy constructor
	~Board() { board.clear(); }
	void printBoard(); 
	bool place(int x, int y, Color c);
	vector<Node*> getNeighbors(int x, int y, Color c = Color::BLANK); //return the surrounding tiles , of corresponding colors
	bool is_legal(int x, int y);
	bool isWon(Color c); //return who won on a filled board.
	void randomFill(); //fill the remaining board with random color in equal mesure
	int getSize() { return size; }
	Node* getNode(int x, int y) { return board[x][y]; }
	vector<Node*> getLegalMoves(); //return all legal moves;
protected:
	int size;
	string line;
	vector<vector<Node*>> board;
};

//AI 
class AI
{
public:
	~AI() { moves.clear(); }
	pair<int, int> nextMove(Board& board, Color comp); //return the next most optimal move
	double moveWinProbability(Board& board, int x, int y, int trials = 1000);//calculate the probability that a move will win using MonteCarlo
	void setColor(Color color) { c = color; }
	Color getColor() { return c; }
protected:
	Color c;
	bool minVisited, maxVisited;
	vector<Node*> moves;
};

//GAME
class Game
{
public:
	void play();
	void setup(); //set up size of board and ask to choose colors
	void playerTurn();
	void computerTurn(); 
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

Board::Board(const Board& b) :Board(b.size)
{
	for (int i = 0; i < b.size; i++)
		for (int j = i; j < b.size; j++)
		{
			board[i][j]->setC(b.board[i][j]->getC());
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

vector<Node*> Board::getLegalMoves()
{
	vector<Node*> moves;
	for (auto v : board)
		for (auto n : v)
			if (n->getC() == Color::BLANK)
				moves.push_back(n);

	return moves;
}

bool Board::isWon(Color c)
{
	vector<Node*> closeSet;
	vector<Node*> openSet;

	for (int i = 0; i < size; i++) //check for all place in the top row
	{
		int cnt;
		if (c == Color::BLUE) {
			cnt = count(closeSet.begin(), closeSet.end(), board[i][0]);
		}
		else
		{
			cnt = count(closeSet.begin(), closeSet.end(), board[0][i]);
		}
		
		if (cnt > 0)
			continue; //skip iteration if it was already a neighbors to another one

		vector<Node*> nb = getNeighbors(i, 0, Color::BLUE);
		openSet.insert(openSet.end(), nb.begin(), nb.end());

		while (!openSet.empty())
		{
			closeSet.push_back(openSet.back());
			openSet.pop_back();

			if (c == Color::BLUE) {
				if (closeSet.back()->getY() == (size - 1)) //if reached bottom of the board, then its a win for blue
					return true;
			}
			else
			{
				if (closeSet.back()->getX() == (size - 1)) //if reached bottom of the board, then its a win for blue
					return true;
			}

			nb = getNeighbors(closeSet.back()->getX(), closeSet.back()->getY(), Color::BLUE);
			for (auto n : nb) //add new neighbors
			{
				//verify if item is in close or open set
				int cnt = count(openSet.begin(), openSet.end(), n);
				cnt += count(closeSet.begin(), closeSet.end(), n);

				if (cnt == 0)
					openSet.push_back(n);
			}
		}
	}

	return false; //if arrives here, then win for Red
}

void Board::randomFill()
{
	int blue = (size*size) / 2 + (size % 2); //how many blue to place
	int red = (size*size) / 2; //how many red to place

	for( auto v : board)
		for(auto n : v)
			switch (n->getC())
			{
			case Color::RED:red--; break;
			case Color::BLUE: blue--; break;
			case Color::BLANK: 
				if ((red == 0) || (prob() <= 0.5 && blue != 0))
				{
					n->setC(Color::BLUE);
					blue--;
				}
				else
				{
					n->setC(Color::RED);
					red--;
				}
				break;
			}

}

//--------AI Methods-----------
pair<int, int> AI::nextMove(Board& board, Color comp)
{
	pair<int, int> next;
	double bestProb = 0.0;
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
		for (auto m : board.getLegalMoves())
		{
			double prob = moveWinProbability(board, m->getX(), m->getY());
			
			if (prob > bestProb)
			{
				next.first = m->getX();
				next.second = m->getY();
				bestProb = prob;
			}
		}
	}
	moves.push_back(board.getNode(next.first, next.second));
	return next;
}

double AI::moveWinProbability(Board& board, int x, int y, int trials)
{
	Board copyB(board); //copied board 
	copyB.place(x, y, c);
	int win = 0;


	for (int i = 0; i < 1; i++)
	{
		srand(time(0) + i);//new random seed
		copyB.randomFill();
		if (copyB.isWon(c))
			win++;
	}

	return (1.0 * (double)win) / trials;
}

//------GAME Methods---------
void Game::play()
{
	char userIn;
	std::cout << "You challenged the computer to a game of hex" << endl << endl;
	setup();

	std::cout << "Setup finished! we can start to play" << endl;
	bool pTurn;

	if (player == Color::BLUE)
		pTurn = true;
	while (true)
	{
		board.printBoard();
		if (pTurn)
		{
			playerTurn();
			pTurn = false;
			if (board.isWon(player))
			{
				win(player);
				break;
			}	
		}
		else
		{
			computerTurn();
			pTurn = true;
			if (board.isWon(computer))
			{
				win(computer);
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
	board.printBoard();
	if (winner == player)
		cout << "You won ! Well played" << endl << endl;
	else
		cout << "You lost, sorry" << endl << endl;
}

void Game::playerTurn() //player turn, return true for a win
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

}

void Game::computerTurn() //computer turn, return false for a win
{
	cout << "Computer turn" << endl;
	pair<int, int> next = computerAI.nextMove(board, computer);
	board.place(next.first, next.second, computer);
	cout << "Computer played " << next.first << " , " << next.second << endl;
}

