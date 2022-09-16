#include <iostream>

using namespace std;

template <typename T>
void print_fun(const T& t)
{
    cout << "\nthe last" << endl;
    cout << t << endl; // 最后一个元素
}

template <typename T, typename... Args>
void print_fun(const T& t, const Args &...args)
{
    cout << " " << t << " ";
    print_fun(args...);
}

int main()
{
    print_fun("Hello", "wolrd", "ni", "hao","!");
    return 0;
}

