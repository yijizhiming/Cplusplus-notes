//std::async会首先创建线程执行is_prime(4444444443)， 任务创建之后，std::async立即返回一个std::future对象。
//
//主线程既可使用std::future::get获取结果，如果调用过程中，任务尚未完成，则主线程阻塞至任务完成。
//
//主线程也可使用std::future::wait_for等待结果返回，wait_for可设置超时时间，
//如果在超时时间之内任务完成，则返回std::future_status::ready状态；
//如果在超时时间之内任务尚未完成，则返回std::future_status::timeout状态。


#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

bool is_prime(int x)
{
	for (int i = 2; i < x; i++) {
		if (x % i == 0)
			return false;
	}
	return true;
}

int main()
{
	// call function asynchronously;
	std::future<bool> fut = std::async(is_prime, 4444444443);

	// do something while waiting for function to set future.
	std::cout << "checking,please wait...\n";
	std::chrono::milliseconds span(100);
	
	while (fut.wait_for(span) == std::future_status::timeout)
	{
		std::cout << '.' << std::flush;
	}
	bool x = fut.get();
	std::cout << "\n4444444443 " << (x ? "is" : "is not") << " prime.\n";

	return 0;
}