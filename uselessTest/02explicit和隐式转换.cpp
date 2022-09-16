#include <iostream>
using namespace std;

class Student {
public:
	int age;


	Student() 
	{
		cout << "Student() " << endl;
		age = 0;
	}

	Student(int age)
	{
		cout << "Student(int age)" << endl;
		this->age = age;
	}

	//explicit Student(int age)
	//{
	//	cout << "Student(int age)" << endl;
	//	this->age = age;
	//}

	Student(Student& stu)
	{
		cout << "Student(Student& stu)" << endl;
		this->age = stu.age;
	}

	Student& operator=(const Student& stu)
	{
		cout << "Student& operator=(const Student& stu)" << endl;
		this->age = stu.age;
		return *this;
	}
};


int main()
{
	Student stu1(10);
	cout << "---------------------" << endl;
	Student stu2 = stu1;
	cout << "---------------------" << endl;
	Student stu3 = 10;
	cout << "---------------------" << endl;
	stu3 = stu2;

	return 0;
}