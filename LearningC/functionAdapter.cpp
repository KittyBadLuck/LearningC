#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

template<class ForwIter>
void print(ForwIter first, ForwIter last, const char* title)
{
	cout << title << endl;
	while (first != last)
		cout << *first++ << '\t';
	cout << endl;
}

//use a binder function bind2nd to transform initial sequence of values to these values doubled
int main()
{
	int data[3] = { 9,10,11 };

	print(data, data + 3, "Original Values ");
	transform(data, data + 3, data, bind2nd(multiplies<int>(), 2));
	print(data, data + 3, "New values");
}