#include <iostream>
#include <string>
using namespace std;

void PrintV(int& t) {
    cout << "lvalue" << endl;
}

void PrintV(int&& t) {
    cout << "rvalue" << endl;
}

template<typename T>
void Test(T&& t) {
    PrintV(t);
    PrintV(std::forward<T>(t));

    PrintV(std::move(t));
}

int main() {
    Test(1); // lvalue rvalue rvalue
    int a = 1;
    Test(a); // lvalue lvalue rvalue
    Test(std::forward<int>(a)); // lvalue rvalue rvalue
    Test(std::forward<int&>(a)); // lvalue lvalue rvalue
    Test(std::forward<int&&>(a)); // lvalue rvalue rvalue
    return 0;
}