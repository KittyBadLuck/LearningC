//list of example for iterator
#include <iostream>
#include <fstream>
#include <numeric> // has accumulate
using namespace std;


int main()
{
	//using input iterator
	ifstream myin("data");
	//equivalent to begin() and end()
	istream_iterator<int> in(myin);
	istream_iterator<int> eos; //end of file

	cout << "Sum of data is " << accumulate(in, eos, 0) << endl; //0 is starting value to accumulate
}