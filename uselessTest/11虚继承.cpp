//使用虚继承的目的：保证存在命名冲突的成员变量在派生类中只保留一份，
//即使间接基类中的成员在派生类中只保留一份。在菱形继承关系中，
//间接基类称为虚基类，直接基类和间接基类之间的继承关系称为虚继承。
//虚继承会直接由最低层次的派生类构造函数初始化虚基类
//实现方式：在继承方式前面加上 virtual 关键字。

#include <iostream>
using namespace std;

// 间接基类，即虚基类
class Base1
{
public:
    int var1;
};

// 直接基类 
class Base2 : virtual public Base1 // 虚继承
{
public:
    int var2;
};

// 直接基类 
class Base3 : virtual public Base1 // 虚继承
{
public:
    int var3;
};

// 派生类
class Derive : public Base2, public Base3
{
public:
    void set_var1(int tmp) { var1 = tmp; }
    void set_var2(int tmp) { var2 = tmp; }
    void set_var3(int tmp) { var3 = tmp; }
    void set_var4(int tmp) { var4 = tmp; }

private:
    int var4;
};

int main()
{
    Derive d;
    return 0;
}

