/* Miles converted to kilometers in c++
Lou de Tarade
03/07/2024
First use of C++*/

#include <iostream>
using namespace ::std;
const double m_to_k = 1.609;

inline double convert(int mi) { return (mi)*m_to_k; } //"inline" is a kind of optimized function 

int main(void)
{
	int miles = 1;

	while (miles != 0)
	{
		cout << "Input distane in miles or 0 to terminate: ";
		cin >> miles;
		cout << "\n Distance is " << convert(miles) << " km." << endl;
	}

	cout << endl;
}