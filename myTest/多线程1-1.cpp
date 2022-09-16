//普通情况下建议使用std::lock_guard，因为std::lock_guard更加轻量级，
// 但如果用在条件变量的wait中环境中，必须使用std::unique_lock。
//
//
//
//条件变量是C++11引入的一种同步机制，它可以阻塞一个线程或多个线程，
//直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁配合使用，
//这里的锁就是上面介绍的std::unique_lock。
//
//mutex本身不锁住变量，它是一个互斥量，多个使用相同的全局变量的线程去获得同一个锁，锁的是程序


#include <iostream>
#include <thread>
#include <windows.h>
void func() {
    for (int i = 0; i < 100; ++i) {
        std::cout << "thread::func:" << i << std::endl;
    }
}
int main() {
    std::cout << "--------\n";
    std::thread my_thread(func);
    
    for (int i = 0; i < 10; ++i)
        std::cout << "main\n";
    //my_thread.detach();
    my_thread.join();
    for (int i = 0; i < 10; ++i)
        std::cout << "main\n";
    return 0;
}
