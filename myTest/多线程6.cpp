//template <class Fn, class... Args>
//
//void call_once(once_flag& flag, Fn&& fn, Args&&...args);
//
//需要包含头文件：<mutex>
//
//参数：
//
//（1）flag：是std::once_falg对象（定义一个该对象传进去即可）、属于控制的标签，相同的flag
// 只执行一次（见下面详解）
//
//（2）fn：需要只执行一次的函数对象、、
//
//（3）args：传递给fn函数的参数、、如果有就传递，没有就不传递。


#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

//必须设置为全局变量
once_flag init_flag;

void init()
{
	cout << "data has inited" << endl;
}

void fun()
{
	//每个线程的fun函数中的init_flag是不同的,不能设置为局部变量
	//once_flag init_flag;
	call_once(init_flag, init);
}

int main()
{
	thread t1(fun);
	thread t2(fun);
	t1.join();
	t2.join();
	system("pause");
	return 0;
}
