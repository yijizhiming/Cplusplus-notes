// polymorphic.cc

#include <iostream>
using std::cout;
struct Base {
    Base() {
        cout << "base construct" << "\n";
    }

    virtual ~Base() {
        cout << "base destruct" << "\n";
    }

    void FuncA() {}

    virtual void FuncB() { cout << "Base FuncB \n"; }

    int a;
    int b;
};

struct Derive1 : public Base {
    Derive1() { cout << "Derive1 construct \n"; }
    ~Derive1() { cout << "Derive1 destruct \n"; }
    void FuncB() override { cout << "Derive1 FuncB \n"; }
};

struct Derive2 : public Base {
    Derive2() { cout << "Derive2 construct \n"; }
    ~Derive2() { cout << "Derive2 destruct \n"; }
    void FuncB() override { cout << "Derive2 FuncB \n"; }
};


int main() {
    {
        Derive1 d1;
        d1.FuncB();
    }

    cout << "======= \n";
    {
        Derive1 d1;
        d1.FuncB();

        Base& b1 = d1;
        b1.FuncB();
    }

    cout << "======= \n";
    {
        Derive2 d2;
        d2.FuncB();

        Base& b2 = d2;
        b2.FuncB();
    }

    cout << "======= \n";
    {
        Base b;
        b.FuncB();
    }

    cout << "======= \n";
    {
        Base* b = new Derive1();
        b->FuncB();
        delete b;
    }

    return 0;
}