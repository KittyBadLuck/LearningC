//simple vector program
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;
int main()
{
	int how_many;
	cout << "How many ints in data? :" << endl;
	cin >> how_many;
	vector<int> data(how_many);

	cout << "The contents of data: ";
	for (auto it = data.begin(); it != data.end(); it++)
		cin >> *it;


	//using with a file:
	ifstream data_file("data.txt");
	istream_iterator<int> start(data_file), end; //pointer to start of file
	vector<int> data(start, end); //vector constructor reads from start to end

	return 0;
}