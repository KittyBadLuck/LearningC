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
#include <fstream>
#include <string>
using namespace std;
const int MAX_GRAPH_SIZE = 50;
inline double prob() { return ((double)rand() / RAND_MAX); } //prob between 0 and 1

enum class Color {RED,BLUE,GREEN};

ostream& operator<<(ostream& out,Color c)
{
	switch (c)
	{
	case Color::RED:out << "RED"; break;
	case Color::BLUE: out << "BLUE"; break;
	case Color::GREEN: out << "GREEN"; break;
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

	void minPriorityQueue() //remove top elem
	{
		pop_heap(this->Q.begin(), this->Q.end(), compare_Heap());
		this->Q.pop_back();
		sort_heap(this->Q.begin(), this->Q.end(), compare_Heap());
	}
	void clear() { Q.clear(); };
	bool contains(T elem)
	{
		for (int i = 0; i < this->size(); i++)
			if (this->Q[i].value == elem)
				return true; //verify value
		return false;//if no value found -> return false
	}
	pair<T, double> getElement(int i)//get element from a position
	{
		pair<T, double> elem(this->Q[i].value, this->Q[i].priority);
		return elem;
	}

	bool chgPriority(T elem, double priority)//cgange priority of an element

	{
		for (int i = 0; i < this->size(); i++)
			if (this->Q[i].value == elem)
			{
				this->Q[i].priority = priority;
				make_heap(this->Q.begin(), this->Q.end(), compare_Heap());
				sort_heap(this->Q.begin(), this->Q.end(), compare_Heap());
				return true; //verify value
			}
		return false;//if no value found -> return false
	}
	bool insertElem(T value, double priority)
	{
		if (this->contains(value))
			return false;
		this->Q.push_back(HeapNode(value, priority));
		push_heap(this->Q.begin(), this->Q.end(), compare_Heap());
		sort_heap(this->Q.begin(), this->Q.end(), compare_Heap());

		return true;
	}

	void removeElem(int i)//remove an element
	{
		this->Q.erase(this->Q.begin() + (i - 1));
		make_heap(this->Q.begin(), this->Q.end(), compare_Heap());
		sort_heap(this->Q.begin(), this->Q.end(), compare_Heap());

	}

	T top() { return Q.front().value; } //return top node
	int size() { return Q.size(); } //return size of queue

	friend ostream& operator<< (ostream& out, const PriorityQueue& pq)
	{
		out << "( ";
		for (int i = 0; i < pq.Q.size(); i++)
			out << (*pq.Q[i].value) << " , " << pq.Q[i].priority << " ";
		out << ")";
		return out;
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

//NODE AND EDGES
class Node
{
public:
	Node() : value(NULL) {}
	Node(int value) : value(value) {}

	friend ostream& operator<< (ostream& out, const Node& n)
	{
		out << n.value;
		return out;
	}
	inline int getValue() const { return value; }
	inline void setValue(int i) { value = i; }
private:
	int value;
};

class Edge
{
public:
	Edge() : x(NULL), y(NULL), weight(0.0), c(Color::RED) {}
	Edge(Node* x, Node* y, double weight = 0.0, Color c = Color::RED) : x(x), y(y), weight(weight), c(c){}
	Edge(Edge* e) : x(e->getX()), y(e->getY()) , weight(e->getWeight()) , c(e->getC()){}
	~Edge() {
		delete x; delete y;
	}

	inline bool operator==(const Edge& other) {
		return (other.getX() == this->getX() && other.getY() == this->getY());
	}

	inline Node* getX() const { return x; }
	inline Node* getY() const { return y; }
	inline Color getC() const { return c; }
	inline double getWeight() { return weight; }
	inline void setX(Node* x) { x = x; }
	inline void setY(Node* y) { y = y; }
	inline void setWeight(double w) { weight = w; }

	friend ostream& operator<< (ostream& out, const Edge& e)
	{
		out << "(" << (*e.x) << " - " << (*e.y) << " = " << e.weight << " ) ";
		return out;
	}

private:
	Node* x;
	Node* y;
	double weight;
	Color c;
};

struct MinSpanTree { vector<Edge*> tree; double cost; ~MinSpanTree() { tree.clear(); } };

ostream& operator<<(ostream& out, const MinSpanTree& mst)
{
	out << "Cost : " << mst.cost << endl;
	out << "Edges : " << endl;
	for (auto edge : mst.tree)
		out << (*edge) << endl;
	return out;
}
//GRAPH
class Graph
{
public:
	Graph(int V = MAX_GRAPH_SIZE);
	Graph(string fileName);
	~Graph();
	bool isAdjacent(int x, int y);
	list<Edge*> getNeighbors(int x);
	inline int getV() { return this->V; }
	inline int getE() { return this->E; }
	inline vector<pair<Node*, list<Edge*>>> getAdjacency() const { return this->adjacencyList; }

	bool addEdge(int x, int y, int w, Color c = Color::RED);
	bool deleteEdge(Graph g, int x, int y);

	Node* getNodeValue(int x);//get the value of the node number x. x is the position
	void setNodeValue(int x, int a) { adjacencyList[x].first->setValue(a); }; //set the value of the node x to the number a. x is the position

	double getEdgeValue(Graph g, int x, int y); //return the value between the x node and y node. x is the position
	void setEdgeValue(Graph g, int x, int y, double w);//set the weight value between the x node and y node. x is the position

	void drawRandom(double density, double min_dist, double max_dist); //draw random edges according to its density
	MinSpanTree* findMST(); //find Minimum Spanning Tree of Graph
private:
	int V; //number of vertex
	int E; //number of edges
	vector<pair<Node*, list<Edge*>>> adjacencyList; //vector of pairs : Nodes, List of Edge
};

Graph::Graph(int V) : V(V), E(0), adjacencyList(vector<pair<Node*, list<Edge*>>>(V))
{
	assert(V > 0);

	for (int i = 0; i < V; i++)
	{
		adjacencyList[i].first = new Node(i); //fill the graph with nodes and their base values
	}
}
Graph::Graph(string fileName)
{
	ifstream data_file(fileName);
	istream_iterator<int> start(data_file), end; //initialize start as iterator to the beginning of file
	vector<int> data(start, end); //initialize vector data from start to end of file
	//in reading from the file, the input operator for strings uses white space
	//so each  white space set of characters is read as one string

	int size = data[0];
	V = size;
	adjacencyList = vector<pair<Node*, list<Edge*>>>(V);
	for (int i = 0; i < size; i++)
	{
		adjacencyList[i].first = new Node(i);
	}

	int edgeCnt = (data.size() - 1) / 3;
	for (int i = 0; i < edgeCnt; i++)
	{
		int index = i * 3;
		this->addEdge(data[index + 1], data[index + 2], data[index + 3]); //no color for this one
	}
}

Graph::~Graph()
{
	for (int i = 0; i < adjacencyList.size(); ++i)
	{
		list<Edge*>::iterator itr = adjacencyList[i].second.begin();
		while (itr != adjacencyList[i].second.end()) {
			delete* itr;
			++itr;
		}
		delete adjacencyList[i].first;
	}
}

Node* Graph::getNodeValue(int x)
{
	for (int i = 0; i < this->V; i++)
	{
		if (this->adjacencyList[i].first->getValue() == x)
			return this->adjacencyList[i].first;
	}
	return nullptr;
}

bool Graph::addEdge(int x, int y, int w, Color c)
{
	Node* xNode = this->getNodeValue(x);
	Node* yNode = this->getNodeValue(y);

	if (xNode == nullptr || yNode == nullptr)
		return false;
	if (this->isAdjacent(x, y))//verify if edge already exist
		return false;

	for (int i = 0; i < this->V; i++)
	{
		if (this->adjacencyList[i].first->getValue() == x)
			this->adjacencyList[i].second.push_back(new Edge(xNode, yNode, w, c));
		if (this->adjacencyList[i].first->getValue() == y)
			this->adjacencyList[i].second.push_back(new Edge(yNode, xNode, w, c));
	}
	this->E++;
	return true;
}

bool Graph::isAdjacent(int x, int y)
{
	Node* yNode = this->getNodeValue(y);

	for (int i = 0; i < this->V; i++)
	{
		if (this->adjacencyList[i].first->getValue() == x)
		{
			list<Edge*>::iterator itr = this->adjacencyList[i].second.begin();
			while (itr != this->adjacencyList[i].second.end()) {
				if ((*itr)->getY() == yNode) { return true; }
				itr++;
			}
			return false;
		}
	}
	return false;
}

bool Graph::deleteEdge(Graph g, int x, int y)
{
	assert(x >= 0 && x < g.V);
	assert(y >= 0 && y < g.V);

	Node* yNode = g.adjacencyList[y].first;
	list<Edge*>::iterator itr = g.adjacencyList[x].second.begin();
	while (itr != adjacencyList[x].second.end()) {
		if ((*itr)->getY() == yNode)
		{
			g.adjacencyList[x].second.remove(*itr);
			g.E--;
			delete* itr;
			return true;
		}
		itr++;
	}
	return false; //if it ends the loop without returning true, it means the edge where not addjacent.

}

double Graph::getEdgeValue(Graph g, int x, int y)
{
	assert(x >= 0 && x < g.V);
	assert(y >= 0 && y < g.V);

	Node* yNode = g.adjacencyList[y].first;
	list<Edge*>::iterator itr = g.adjacencyList[x].second.begin();
	while (itr != adjacencyList[x].second.end()) {
		if ((*itr)->getY() == yNode)
		{
			double w = (*itr)->getWeight();
			delete* itr;
			return w;
		}
		itr++;
	}
	return false;

}

void Graph::setEdgeValue(Graph g, int x, int y, double w)
{
	if (!g.isAdjacent(x, y))
		addEdge(x, y, w);
	else
	{
		Node* yNode = g.adjacencyList[y].first;
		list<Edge*>::iterator itr = g.adjacencyList[x].second.begin();
		while (itr != adjacencyList[x].second.end()) {
			if ((*itr)->getY() == yNode)
			{
				(*itr)->setWeight(w);
				delete* itr;
				break;
			}
			itr++;
		}
	}
}

list<Edge*> Graph::getNeighbors(int x)
{
	list<Edge*> result;
	for (int i = 0; i < this->V; i++)
	{
		if (this->adjacencyList[i].first->getValue() == x)
			return this->adjacencyList[i].second;
	}
	return result;
}

void Graph::drawRandom(double density, double min_dist, double max_dist)
{
	srand(time(0));
	double range = max_dist - min_dist;
	for (int i = 0; i < this->V; i++)
		for (int j = i; j < this->V; j++)
			if (i != j)
				if (prob() <= density)
				{
					uniform_real_distribution<double> unif(min_dist,
						max_dist);
					default_random_engine re;
					double random_w = unif(re); //get a random double weight
					int r = rand() % 3; // get a random color
					Color c;
					switch (r)
					{
					case 0: c = Color::RED;
					case 1: c = Color::BLUE;
					case 2: c = Color::GREEN;
					}
					this->addEdge(i, j, random_w, c);
				}

}

MinSpanTree* Graph::findMST()
{
	//use Prim algo
	MinSpanTree* mst = new MinSpanTree();
	vector<Node*> nodeLinked;
	PriorityQueue<Edge*> openSet;

	nodeLinked.push_back(this->adjacencyList[0].first);
	list<Edge*> neigbhors = this->adjacencyList[0].second;
	list<Edge*>::iterator itr = neigbhors.begin();
	while (itr != neigbhors.end()) { //add the first neigbhors
			openSet.insertElem((*itr), (*itr)->getWeight());
		itr++;
	}


	while (openSet.size() > 0) //run until their is nothing in open set
	{
		//get shortest Edge
		Edge* toCheck = openSet.top();
		openSet.minPriorityQueue();

		//check if node was already linked
		int cntY = count(nodeLinked.begin(), nodeLinked.end(), toCheck->getY()); 
		if (cntY > 0)
			continue;
		
		mst->tree.push_back(new Edge(toCheck));
		mst->cost = mst->cost + toCheck->getWeight();
		nodeLinked.push_back(toCheck->getY());
		
		neigbhors = this->getNeighbors(toCheck->getY()->getValue());

		itr = neigbhors.begin();
		while (itr != neigbhors.end()) //add new neigbhors
		{ 
			openSet.insertElem((*itr), (*itr)->getWeight());
			itr++;
		}
	}

	nodeLinked.clear();
	openSet.clear();
	return mst;
}



// SHORTEST PATH
struct Path { list<Node*> path; double cost; };

class ShortestPath
{
public:
	ShortestPath(Graph* graph) : graph(graph) {}
	~ShortestPath();

	Path* shortestPath(int s, int d); //return path from s to d
	Path* printShortestPath(int s, int w); //print path from s to d and return said path
	bool closeContains(Node* elem); //check if node is already in close set
	int openImprove(Node* elem, double cost); //check if node improve another priority of open set. return pos if true, -1 if false, -2 if not found
private:
	vector<Path*> closeSet;
	PriorityQueue<Path*> openSet;

	Graph* graph;
};

ShortestPath::~ShortestPath()
{
	this->closeSet.clear();
	this->openSet.clear();
}
bool ShortestPath::closeContains(Node* elem)
{
	for (int i = 0; i < this->closeSet.size(); i++)
	{

		if (this->closeSet[i]->path.back() == elem)
			return true;
	}
	return false;
}
int ShortestPath::openImprove(Node* elem, double cost)
{
	bool found = false;
	for (int i = 0; i < this->openSet.size(); i++)
	{
		pair<Path*, double> pathInSet = this->openSet.getElement(i);
		if (pathInSet.first->path.back() == elem)
		{
			found = true;
			if (pathInSet.second > cost)
				return i;
			break;
		}
	}
	if (found)return -1;
	return -2; //return -2 if not found
}
Path* ShortestPath::printShortestPath(int s, int d)
{
	Path* path = this->shortestPath(s, d);

	if (path == nullptr)
	{
		cout << "No path found from " << s << " to " << d << endl;
		return nullptr;
	}
	cout << "Shortest Path from " << s << " to " << d << " is: " << endl;
	list<Node*> nodes = path->path;
	list<Node*>::iterator itr = nodes.begin();
	cout << s;
	itr++;
	while (itr != nodes.end()) {
		cout << "->" << (*itr)->getValue();
		itr++;
	}
	cout << endl;
	cout << "and the cost is : " << path->cost;

	return path;
}
Path* ShortestPath::shortestPath(int s, int d)
{
	this->closeSet.clear(); //clear set from previous possible caclulation
	this->openSet.clear();

	Node* start = this->graph->getNodeValue(s);
	Node* end = this->graph->getNodeValue(d);

	closeSet.push_back(new Path());
	closeSet[0]->path.push_back(start); //add the start in close set at cost 0

	Path* searchingPath = closeSet[0];

	list<Edge*> neigbhors = this->graph->getNeighbors(s);
	list<Edge*>::iterator itr = neigbhors.begin();
	while (itr != neigbhors.end()) { //add the first neigbhors
		if (start != (*itr)->getY())
		{
			Path* next = new Path();
			next->path = searchingPath->path;
			next->path.push_back((*itr)->getY());

			next->cost = searchingPath->cost + (*itr)->getWeight();
			this->openSet.insertElem(next, next->cost);
		}
		itr++;
	}


	while (this->openSet.size() > 0) //run until their is nothing in open set or the destination was reached
	{
		this->closeSet.push_back(this->openSet.top());
		this->openSet.minPriorityQueue();
		searchingPath = this->closeSet.back();
		if (searchingPath->path.back()->getValue() == d) // verify if destination was reached
			return searchingPath;

		Node* lastN = searchingPath->path.back();
		neigbhors = this->graph->getNeighbors(lastN->getValue());

		cout << (*lastN);

		itr = neigbhors.begin();
		while (itr != neigbhors.end()) { //add the first neigbhors
			if (!this->closeContains((*itr)->getY())) //first check if it is in the close set
			{
				double cost = searchingPath->cost + (*itr)->getWeight();
				int isImprove = this->openImprove((*itr)->getY(), cost);
				if (isImprove != -1) //check if improve position or not
				{
					if (isImprove != -2)this->openSet.removeElem(isImprove); //remove previous element if it was an improvement

					Path* next = new Path();
					next->path = searchingPath->path;
					next->path.push_back((*itr)->getY());

					next->cost = cost;
					this->openSet.insertElem(next, next->cost);
				}
			}
			itr++;
		}

	}
	return nullptr; //return Null if the destination was not reached

}



//AVERAGE PATH LENGHT
double averagePathLenght(Graph* g)
{
	int size = g->getV();
	int validPath = 0;
	double sumLenght = 0;
	ShortestPath sP(g);
	for (int i = 1; i < size; i++)
	{
		Path* path = sP.shortestPath(0, i);
		if (path != nullptr)
		{
			validPath++;
			sumLenght += path->cost;
		}
	}

	return (sumLenght / validPath);
}

int main()
{
	Graph* graph1 = new Graph("data.txt");

	MinSpanTree* mst = graph1->findMST();

	cout << "Minimum Spanning Tree : " << endl;
	cout << (*mst);


	return 0;
}
