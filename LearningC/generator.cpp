#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

class gen { //generator for integrated function
public:
	gen(double x_zero, double increment): x(x_zero), incr(increment) {}
	double operator()() { x += incr; return x * x; }
private:
	double x, incr;
};

double integrate(gen g, int n)//integrate on (0,1), generate n values
{
	vector<double> fx(n);
	generate(fx.begin(), fx.end(), g);
	return (accumulate(fx.begin(), fx.end(), 0.0) / n); //sympson style for numerical integration
}


int main()
{
	const int n = 10000;

	gen g(0.0, 1.0 / n);
	cout << "integration program x**2" << endl;
	cout << integrate(g, n) << endl;
}