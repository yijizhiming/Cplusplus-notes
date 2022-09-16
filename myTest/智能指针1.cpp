#include <iostream>
using namespace std;


class B;
class A
{
public:
    //shared_ptr<B> pb_;
    weak_ptr<B> pb_;
    ~A()
    {
        cout << "A delete\n";
    }
};
class B
{
public:
    shared_ptr<A> pa_;
    ~B()
    {
        cout << "B delete\n";
    }
};

void fun()
{
    shared_ptr<B> pb(new B());
    shared_ptr<A> pa(new A());
    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;
    pb->pa_ = pa;
    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;
    pa->pb_ = pb;
    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;
}

int main()
{
    fun();
    return 0;
}