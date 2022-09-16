//当一个线程等待另一个线程完成任务时，它会有很多选择。
//
//第一，它可以持续的检查共享数据标志(用于做保护工作的互斥量)，直到另一线程完成工作时对这个标志进行重设。
//不过，就是一种浪费：线程消耗宝贵的执行时间持续的检查对应标志，并且当互斥量被等待线程上锁后，
// 其他线程就没有办法获取锁，这样线程就会持续等待。
// 
//第二个选择l是周期轮询，在等待线程在检查间隙，使用 std::this_thread::sleep_for() 
// 进行周期性的间歇在这个循环中，在休眠前，函数对互斥量进行解锁，并且在休眠结束后再对互斥量进行上锁，
// 所以另外的线程就有机会获取锁并设置标识。
// 
//第三个选择(也是优先的选择)是，使用C++标准库提供的条件变量condition_variable去等待事件的发生。
//通过另一线程触发等待事件的机制是最基本的唤醒方式。
//
//std::condition_variable 和 std::condition_variable_any 。这两个实现都包含在 <mutex> 
// 或者<condition_variable>头文件的声明中。两者都需要与一个互斥量一起才能工作(互斥量是为了同步)；
// std::condition_variable仅限于与 std::mutex 一起工作，而后者可以和任何满足最低标准的互斥量
// 一起工作，从而加上了_any的后缀。因为 std::condition_variable_any 更加通用，
// 这就可能从体积、性能，以及系统资源的使用方面产生额外的开销。
//wait()用来等一个事件或者条件满足，如果第二个参数（可调对象）的lambda表达式返回值是false，
//即条件不满足，那么wait()将解锁互斥量，并阻塞到本行，如果第二个参数的lambda表达式返回值是true，
//那么wait()直接返回并继续执行。
//
//阻塞到什么时候为止呢？阻塞到其他某个线程调用notify_one()成员函数唤醒为止；
//
//如果没有第二个参数，那么效果跟第二个参数lambda表达式返回false效果一样。
//
//wait()将解锁互斥量，并阻塞到本行，直到到其他某个线程调用notify_one()成员函数为止。
//
//当其他线程用notify_one()将本线程wait()唤醒后，这个wait被唤醒后
//
//1、wait()不断尝试获取互斥量锁，如果获取不到那么流程就卡在wait()这里等待获取，如果获取到了，
//那么wait()就继续执行，获取到了锁
//
//2.1、如果wait有第二个参数就判断这个lambda表达式。
//
//a)如果表达式为false，那wait又对互斥量解锁，然后又休眠，等待再次被notify_one()唤醒
//b)如果lambda表达式为true，则wait返回，流程可以继续执行（此时互斥量已被锁住）。
// 注：在有第二个参数情况下（即设置了 Predicate），只有当 pred 条件为 false 时
// 调用 wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞。
// 因此第二种情况类似以下代码：
//while (!pred()) wait(lck);
// 
//2.2、如果wait没有第二个参数，则wait返回，流程走下去。
//
//流程只要走到了wait()下面则互斥量一定被锁住了。
// 
//notify_all()
//同时通知所有等待线程，但是需要注意的是，如果所有线程只有一个线程可以拿到互斥量，
// 那么也只有一个线程可以继续执行。
//
//对使用读写锁的多个读线程，可以同时被唤醒并同时继续工作。

#include <iostream>                // std::cout
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable

std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.

void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
    while (!ready) // 如果标志位不为 true, 则等待...
        cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后,
    // 线程被唤醒, 继续往下执行打印线程编号id.
    std::cout << "thread " << id << '\n';
}

void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cv.notify_all(); // 唤醒所有线程.
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);

    std::cout << "10 threads ready to race...\n";
    go(); // go!

    for (auto& th : threads)
        th.join();

    return 0;
}
