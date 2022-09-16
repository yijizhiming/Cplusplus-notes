#include <iostream>
using namespace std;

template<typename T1, typename T2>
class A {
public:
    void function(T1 value1, T2 value2) {
        cout << "value1 = " << value1 << endl;
        cout << "value2 = " << value2 << endl;
    }
};

template<typename T>
class A<T, double> { // 部分类型明确化，为偏特化类
public:
    void function(T value1, double value2) {
        cout << "Value = " << value1 << endl;
        cout << "doubleValue = " << value2 << endl;
    }
};

int main() {
    A<char, double> a;
    a.function('a', 12.3);
    A<char, char> a2;
    a2.function('a2', 'a2');
    return 0;
}
