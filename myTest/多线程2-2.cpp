#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<long> num(0);

void addnum()
{
    for (int i = 0; i < 100000; i++)
        num++;
}

int main()
{
    const int nthreads = 2;
    thread t[nthreads];
    for (int i = 0; i < nthreads; i++)
        t[i] = thread(addnum);

    for (auto& th : t)
        th.join();
    cout << num << endl;
    return 0;
}
