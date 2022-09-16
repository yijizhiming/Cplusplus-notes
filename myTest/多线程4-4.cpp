//std::packaged_task的作用就是提供一个不同线程之间的数据同步机制，它可以存储一个函数操作，
//并将其返回值传递给对应的future， 而这个future在另外一个线程中也可以安全的访问到这个值。
#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

int countdown(int from, int to)
{
	std::cout << "sleep 3 seconds\n";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "awake\n";
	for (int i = from; i != to; --i)
	{
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Lift off!\n";
	return from - to;
}

int main()
{
	std::packaged_task<int(int, int)> tsk(countdown);
	std::future<int> ret = tsk.get_future();
	std::thread th(std::move(tsk), 10, 0);
	// ...
	//th.join();
	std::cout << "wait...\n";
	int value = ret.get();// wait for the task to finish and get result
	std::cout << "The value is " << value << " \n";
	th.join();
	
	return 0;
}