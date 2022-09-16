#include <iostream>
using namespace std;

class textBlock {
public:
	string s;
	textBlock(string s) : s(s) {}
	char& operator[](int position)
	{
		cout << "no const" << endl;
		return s[position];
	}
	const char& operator[](int position) const
	{
		cout << "cosnt" << endl;
		return s[position];
	}
};

int main()
{
	textBlock t("abcd");
	const textBlock ct("abcd");
	cout << t[0] << endl;
	cout << "**************" << endl;
	cout << ct[0] << endl;


	return 0;
}


