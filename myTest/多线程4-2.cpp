//promise和future
//future和promise的作用是在不同线程之间传递数据。使用指针也可以完成数据的传递，但是指针非常危险，
// 因为互斥量不能阻止指针的访问；而且指针的方式传递的数据是固定的，如果更改数据类型，
// 那么还需要更改有关的接口，比较麻烦；promise支持泛型的操作，更加方便编程处理。
//
//假设线程1需要线程2的数据，那么组合使用方式如下：
//
//线程1初始化一个promise对象和一个future对象，promise传递给线程2，相当于线程2对线程1的一个承诺；
// future相当于一个接受一个承诺，用来获取未来线程2传递的值
//线程2获取到promise后，需要对这个promise传递有关的数据，之后线程1的future就可以获取数据了。
//如果线程1想要获取数据，而线程2未给出数据，则线程1阻塞，直到线程2的数据到达。
//
//线程1只要检测到数据到达，get就可以返回，线程2的状态可以结束也可能继续运行。
//————————————————
//版权声明：本文为CSDN博主「qq_24127015」的原创文章，遵循CC 4.0 BY - SA版权协议，
// 转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/qq_24127015/article/details/104819447




#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

// 计算一个vector数组的和，并设置一个promise，这是一个承诺，需要设置这个值
void accumulate(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int> accumulate_promise)
{
	int sum = std::accumulate(first, last, 0);
	std::cout << "set promise\n";
	std::cout << "wait 5 seconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	accumulate_promise.set_value(sum);// Notify future
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void do_work(std::promise<void> barrier)
{
	std::cout << "set promise2\n";
	std::cout << "wait 5 seconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	barrier.set_value();
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
	// Demonstrate using promise<int> to transmit a result between threads.
	std::vector<int> numbers = { 1,2,3,4,5,6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
	std::cout << "waiting... \n";
	accumulate_future.wait();
	std::cout << "ready\n";
	std::cout << "result=" << accumulate_future.get() << "\n";
	work_thread.join();

	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	
	std::cout << "waiting2... \n";
	barrier_future.wait();
	std::cout << "ready2... \n";
	new_work_thread.join();
	
	return 0;
}