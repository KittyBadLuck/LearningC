#include <iostream>

using namespace std;

class B {
public:
	int i;
	virtual void print_i()const { cout << i << "inside B" << endl; }
};

class D : public B {
public:
	void print_i()const { cout << i << "inside D" << endl; }//virtual
};

int main()
{
	B b;
	B* pb = &b;	//point at a B object
	D f;

	f.i = 1 + (b.i = 1);
	pb->print_i(); //callB::print_i()
	pb = &f;		//point at a D object
	pb->print_i();	//call D::print_i()
}