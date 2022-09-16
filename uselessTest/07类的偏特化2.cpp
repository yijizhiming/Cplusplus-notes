#include <iostream>
using namespace std;

template<typename T>
class A {
public:
    void function() {
        cout << "一般" << endl;
    }
};

template<typename T>
class A<T*> { // 部分类型明确化，为偏特化类
public:
    void function() {
        cout << "偏特" << endl;
    }
};

int main() {
    A<int*> a;
    a.function();
    cout << "*********" << endl;
    A<int> b;
    b.function();
    cout << "*********" << endl;
    A<int**> c;
    c.function();
    return 0;
}

/*
偏特
一般
偏特
*/