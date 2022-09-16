#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
//aotomic原子的 即不能分割的，最小单位。
//
//举个例子，int num;
//
//num = num + 1;
//
//我们都知道对于num = num + 1这条程序语句需要分解为三步，
//
//1、把变量num读取到某一个寄存器R存储，
//
//2、CPU对寄存器R的值进行计算，
//
//3、计算完成后将值存回内存
//
//在多线程执行num++的时候 当前num为1 线程A执行完第二步 此时num为2但是还没有存入内存，
//然后线程B开始执行第一步，从内存中取出num，num依旧是1，这样就出现问题了，
//相当于A线程和B线程一共执行了连词num = num + 1，但是num却只增加了1



long num = 0;

void addnum()
{
    for (int i = 0; i < 100000; i++)
        ++num;//不对全局变量进行互斥访问
}

int main()
{
    int nthreads = 2;
    thread t[2];
    for (int i = 0; i < nthreads; i++)
        t[i] = thread(addnum);

    for (auto& th : t)
        th.join();
    cout << num << endl;
    return 0;
}
