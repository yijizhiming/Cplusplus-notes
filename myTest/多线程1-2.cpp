#include <iostream>
#include <thread>


void callBack(int num)
{
	for (int i = 0; i < num; ++i)
		std::cout << "thread_1 : " << i << "\n";
}

void callBack2(int num)
{
	for (int i = 0; i < num; ++i)
		std::cout << "thread_2 : " << i << "\n";
}

int main(int argc, char* argv[])
{
	std::thread thread_1(&callBack, 10);
	std::cout << "before join\n";
	thread_1.join();
	std::cout << "after join\n";
	//thread_1.join();

	std::cout << "***************\n";

	std::thread thread_2(&callBack2, 10);
	std::cout << "before detach\n";
	thread_2.detach();
	std::cout << "after detach\n";


	return 0;
}

