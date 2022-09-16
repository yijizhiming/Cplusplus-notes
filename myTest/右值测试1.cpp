#include <iostream>
#include <string>
using namespace std;

class A {
public:
    A(int size) : size_(size) {
        data_ = new int[size];
        for (int i = 0; i < size; ++i)
            data_[i] = i;
    }
    A() {}
    A(const A& a) {
        size_ = a.size_;
        data_ = new int[size_];
        cout << "copy " << endl;
    }
    A(A&& a) {
        this->data_ = a.data_;
        this->size_ = a.size_;
        a.data_ = nullptr;
        cout << "move " << endl;
    }
    ~A() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }
    int* data_;
    int size_;
};

int main() {
    A a(10);
    cout << a.data_[0] << endl;
    A b = a;
    cout << a.data_[0] << endl;
    A c = std::move(a); // 调用移动构造函数
    cout << a.size_ << endl;
    cout << c.size_ << endl;
    //cout << a.data_[0] << endl;//这条语句不能执行，因为该内存空间的所有权转交给了c
    cout << c.data_[0] << endl;
    
  /*  分析

        Test(1)：1是右值，模板中T&& t这种为万能引用，右值1传到Test函数中变成了右值引用，
        但是调用PrintV()时候，t变成了左值，因为它变成了一个拥有名字的变量，所以打印lvalue，
        而PrintV(std::forward<T>(t))时候，会进行完美转发，按照原来的类型转发，所以打印rvalue，
        PrintV(std::move(t))毫无疑问会打印rvalue。

        Test(a)：a是左值，模板中T&& 这种为万能引用，左值a传到Test函数中变成了左值引用，
        所以有代码中打印。

        Test(std::forward<T>(a))：转发为左值还是右值，依赖于T，T是左值那就转发为左值，
        T是右值那就转发为右值。
  */


    return 0;
}