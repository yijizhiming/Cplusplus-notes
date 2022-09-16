#include <iostream>
using namespace std;

//解决方法一：借助 final 关键字，用该关键字修饰的类不能被继承。
//解决方法二：借助友元、虚继承和私有构造函数来实现
//①在子类继承中使用virtual虚继承，这样做的目的是让子类直接负责他爷爷的构造，
//可是他爷爷的构造和析构是私有的，不让他构造，所以孙子就不能构造自己了
//（也就是不让继承了，因为孙子必须此时必须直接负责爷爷的构造却又没法构造）
//
//②可是如果爷爷的构造和析构是私有的，意味着父类也不能构造了，
//所以把父类设为爷爷的友元，就可以继续访问爷爷的构造和析构函数，
//就可以构造父亲了（父亲负责构造爷爷，并且可以通过友元关系构造）

template <typename T>
class Base {
    friend T;
private:
    Base() {
        cout << "base" << endl;
    }
    ~Base() {}
};

class B :virtual public Base<B> {   //一定注意 必须是虚继承
public:
    B() {
        cout << "B" << endl;
    }
};

class C :public B {
public:
    C() {}     // error: 'Base<T>::Base() [with T = B]' is private within this context
};


int main() {
    B b;
    return 0;
}
