#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Edge
{
public:
	Edge() : x(NULL), y(NULL), weight(0.0) {}

	Edge(int x, int y, double weight = 0.0) : x(x), y(y), weight(weight) {}

	~Edge() {}

	inline bool operator==(const Edge& other) {
		return (other.getX() == this->getX() && other.getY() == this->getY());
	}

	inline int getX() const {
		return x;
	}

	inline int getY() const {
		return y;
	}

	inline double getWeight() const {
		return weight;
	}

	/**
	 * Prints the value of this node instance
	 */
	friend std::ostream& operator<< (std::ostream& os, const Edge<T>& edge) {
		std::stringstream ss;
		ss << "(" << edge.x << " " << "-" << " " << edge.y << ")";
		return (os << ss.str());
	}
private:
	int x;
	int y;
	double weight; 
};


class Graph 
{
public:
	bool isAdjacent(Graph g, int x, int y);
	vector<Edge> getNeighbors(int x) const;
private:
	int V; //number of vertex
	int E; //number of edges
};

//draw a random generated graph
//bool** graph;
//	srand(time(0)); //see rand()
//	graph = new bool* [size];
//	for (int i = 0; i < size; ++i)
//	{
//		graph[i] = new bool[size];
//	}
//
//	//generate nodes with 0.19 being the density
//	for (int i = 0; i < size; ++i)
//		for (int j = i; j < size; ++i)
//			if (i == j) graph[i][j] = false;
//				else graph[i][j] = (prob() < 0.19);