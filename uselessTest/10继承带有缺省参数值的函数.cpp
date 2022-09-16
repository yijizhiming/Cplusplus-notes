#include <iostream>
using namespace std;

class Base {
public:
	virtual void fun(int x = 1)
	{
		cout << "Base:" << x << endl;
	}
};

class Derive {
public:
	virtual void fun(int x = 2)
	{
		cout << "Derive:" << x << endl;
	}
};

int main()
{
	Base* b = new Base();
	Derive* d = new Derive();
	b->fun();
	b->fun(10);
	cout << "********" << endl;
	d->fun();
	d->fun(10);

	return 0;
}