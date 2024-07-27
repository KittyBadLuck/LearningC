/*create a class for points
Lou de Tarade
08/07/2024*/

#include <iostream>
using namespace ::std;

class point {
public:
	point();
	point(double u): x(u), y(0.0){}//constructor
	point(double x, double y) { this->x = x; this->y = y; }
	double getx() const {return x;}
	double gety() const { return y; }
	void setx(double v) { x = v; }
	void sety(double v) { y = v; }

private:
	double x, y;
};

point::operator double()
{
	return sqrt(x * x + y * y);
}
point operator+ (point& p1, point& p2)
{
	point sum = { p1.getx() + p2.getx() , p1.gety() + p2.gety()};
	return sum;
}

ostream& operator<< (ostream& out, const point& p)
{
	out << "(" << p.getx() << " , " << p.gety() << " ) ";
	return out;
}

int main()
{
	//point a = { 3.5, 2.5 }, b = { 2.5, 4.5 }, c;
	point s;
	double d = 3.5;

	s = d; //implicit conversion
	s = static_cast<point>(d); //explicit
	//cout << "a = " << a << " b = " << b << endl;
	//cout << "sum = " << a + b << endl;
	return 0;
}