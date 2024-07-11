
#include <iostream>
#include <memory>
using namespace std;

struct slistelem { char* data; slistelem* next; };

//class slist{ //singly linked list
//public:
//	slist():h(0) {} //empty list
//	~slist() { release(); } // destructor (release not defined here
//	void release();
//	void prepend(char* c);
//	void print();
//private:
//	slistelem* h; //list head
//
//};

//
//void slist::prepend(char* c)
//{
//	slistelem* temp = new slistelem;
//	temp->next = h;
//	temp->data = c;
//	h = temp; //update c 
//}
//
//slist::~slist()
//{
//	cout << "destructor called" << endl; //just for demonstration
//	release(); //march thru list with deletes
//}

class list_element {
public:
	list_element(int n = 0, list_element* ptr = nullptr): d(n), next(ptr){}
	int d;
	list_element* next;
};

class list {
public:
	//constructors
	list():head(0), cursor(0){} //default constructor
	list(const int* arr, int n); // transfer data constructor
	list(const list& lst); //copy constructor "move constructor"

	~list(); //delete destructor

	void preprend(int n);
	int get_element() { return cursor->d; }
	void advance() { cursor = cursor->next; }
	void print();
private:
	list_element* head;
	list_element* cursor;
};

void list::preprend(int n)
{
	if (head == 0)
		cursor = head = new list_element(n, head);
	else
		head = new list_element(n, head);
}

void list::print()
{
	list_element* h = head;
	while (h != 0) //idiom chaining
	{
		cout << h->d << ", ";
		h = h->next;
	}

	cout << "###" << endl;
}

list::list(const int* arr, int n) //transfert constructor
{
	list_element* h = new list_element();
	list_element* previous;
	head = h;
	h->d = arr[0];
	previous = h;
	for (int i = 0; i < n; ++i)
	{
		h = new list_element();
		h->d = arr[i];
		previous->next = h;
		previous = h;
	}
	cursor = head;
}

list::list(const list& lst) //copy constructor
{
	if (lst.head == 0)
	{
		head = 0; cursor = 0;
	}
	else
	{
		cursor = lst.head;
		list_element* h = new list_element();
		list_element* previous;
		head = h;
		h->d = lst.head->d;
		previous = h;
		for (cursor = lst.head; cursor != 0;)
		{
			h  = new list_element();
			h->d = cursor->d;
			previous->next = h;
			cursor = cursor->next;
			previous = h;
		}
	}
	cursor = head;
}

list::~list() //destructor
{
	for (cursor = head; cursor != 0;)
	{
		cursor = head->next;
		delete head;
		head = cursor;
	}
}

int main()
{
	list a, b;
	int data[10] = { 3,4,6,7,-3,5 };
	list d(data, 6);
	list e(data, 10);
	a.preprend(9); a.preprend(8);
	cout << "list a " << endl;
	a.print();
	for (int i = 0; i < 40; ++i)
		b.preprend(i * i);
	cout << "list b " << endl;
	b.print();
	list c(b);
	cout << "list c " << endl;
	c.print();
	cout << "list d " << endl;
	d.print();
	cout << "list e " << endl;
	e.print();

	return 0;
}