//C++ For C Programmers Part B  2.13
//Ira Pohl   April 2016
//overriding behavior

#include <iostream>

class B {
public:
    int i;
    virtual void print_i() const
    {
        std::cout << i << " inside B" << std::endl;
    }
};

class D : public B {
public:
    void print_i() const
    {
        std::cout << i << " inside D" << std::endl;
    }
};

int main()
{
    B   b;
    B* pb = &b;      //point at a B object
    D   f;
    f.i = 1 + (b.i = 1);
    pb->print_i();  //call B::print_i()
    pb = &f;          //point at a D object
    pb->print_i();  //call D::print_i()
}


//CORRECT

#include <iostream>

class B {
public:
    virtual void foo(int i) { std::cout << "B::foo(int) " << i << "\n"; }
    virtual void foo(double x) { std::cout << "B::foo(double) " << x << "\n"; }
};

class D : public B {
public:
    void foo(int i) { std::cout << "D::foo(int) " << i << "\n"; }
    void foo(double x) { std::cout << "D::foo(double) " << x << "\n"; }
};


int main()
{
    D d;
    B b, * pb = &d;
    b.foo(9.5);
    d.foo(9.5);
    pb->foo(9.5);
}

// CONFUSED


#include <iostream>

class B {
public:
    virtual void foo(int i) { std::cout << "B::foo(int) " << i << "\n"; }
    virtual void foo(double x) { std::cout << "B::foo(double) " << x << "\n"; }
};

class D : public B {
public:
    void foo(int i) { std::cout << "D::foo(int) " << i << "\n"; }
};


int main()
{
    D d;
    B b, * pb = &d;
    b.foo(9.5);
    d.foo(9.5);
    pb->foo(9.5);
}