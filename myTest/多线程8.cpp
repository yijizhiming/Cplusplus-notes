//c++11引入thread_local，用thread_local修饰的变量具有thread周期，
//每一个线程都拥有并只拥有一个该变量的独立实例，一般用于需要保证线程安全的函数中。
//对于一个线程私有变量，一个线程拥有且只拥有一个该实例，类似于static

#include <iostream>
#include <thread>
#include <string>

class A {
public:
    A() {}
    ~A() {}

    void test(const std::string& name) {
        thread_local int count = 0;
        ++count;
        std::cout << name << ": " << count << std::endl;
    }
};

void func(const std::string& name) {
    A a1;
    a1.test(name);
    a1.test(name);
    A a2;
    a2.test(name);
    a2.test(name);
}

int main() {
    std::thread(func, "thread1").join();
    std::thread(func, "thread2").join();
    return 0;
}