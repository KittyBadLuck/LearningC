/*Use a template to sum elements of an array
Lou de Tarade
03/07/2024*/

#include <iostream>
using namespace ::std;

//double sum_double(int n[], int size)
//{
//	double sum = 0.0;
//	for (int i = 0; i < size; i++) sum += n[i];
//	return sum;
//}

template<class summable> 
summable sum(const summable data[], int size, summable sum = 0)
{
	for (int i = 0; i < size; i++) sum += data[i];
	return sum;
}
template<class summable>
summable subtract(const summable data[], int size, summable start = 0)
{
	for (int i = 0; i < size; i++) start -= data[i];
	return start;
}

template<class summable>
void output(const summable data[], int size)
{
	for (int i = 0; i < size; i++) cout << "data[ " << i << "] = " << data[i] << endl;
}

int main(void)
{
	cout << "Write the sum of an array\n";
	int test[3] = { 2,4,6 };

	cout << "sum int : " << sum(test, 3) << endl;

	double test2[3] = { 1.1, 2.2, 3.5 };

	cout << "sum double : " << sum(test2, 3) << endl;

	cout << "subtract double : " << subtract(test2, 3, sum(test2, 3)) << endl;

	output(test, 3);

	return 0;
}
