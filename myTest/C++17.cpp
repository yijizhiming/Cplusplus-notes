#include<iostream>
using namespace std;

[[deprecated("use new func instead of")]] void func() {}


int main(int argc, char* argv[])
{
	func();

	return 0;
}