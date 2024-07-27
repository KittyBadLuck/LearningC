//simple STL vector program
//+ new features of c++ 11
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v(100); //vector is a template and a random access container (replace array)

	for (int i = 0; i < 100; ++i)
		v[i] = i; //index thru an array 
	//for (vector<int>::iterator p = v.begin(); // OLD VERSION
	//	p != v.end(); ++p)
	//	cout << *p << '\t';
	for (auto p = v.begin(); //new, using auto
		p != v.end(); ++p)
		cout << *p << '\t';

	cout << endl;

}