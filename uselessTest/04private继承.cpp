#include <iostream>
using namespace std;

class Base {
public:
	virtual void fun1() = 0;
	virtual void fun1(int) { cout << "hello" << endl; };
};

class Derive : private Base{
public:
	virtual void fun1() 
	{ 
		cout << "nihao" << endl;
		Base::fun1(x); 
	};
	/*virtual void fun1(int)
	{
		cout << "Derive:fun1(int)" << endl;
	}*/

	int x;
};

int main()
{
	Derive d;
	int x = 1;
	d.fun1();
	//d.fun1(x);

	return 0;
}