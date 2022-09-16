//死锁问题
//（1）忘记释放锁
//（2）单线程重复申请锁
//（3）双线程多锁申请


//当代码中有2个锁，锁A和锁B，也有2个线程，线程1和线程2，线程1执行时，
//先抢到锁A，然后要去抢占B，同时线程2先抢到了锁B，然后要去抢占锁A,
//此时就出现死锁情况，互相等待资源，又不释放自身的资源。

//解决方法：std::lock()
//std::lock()的作用是：当有2给锁时，要么同时锁上，要么同时不锁。
//就是当线程1执行时，先抢到锁A，然后发现锁B被别人占用时，
//此时抢不到锁B，然后它就会把A锁也释放掉。

#include <iostream>
#include<thread>
#include<string>
#include<vector>
#include<algorithm>
#include<windows.h>
#include<list>
#include<mutex>

using namespace std;

class myClass
{
public:
    void AddOrder()
    {
        for (int i = 0; i < 10000; i++)
        {
            cout << "addOrder执行，插入一个元素" << i << endl;
            std::lock(m_mutex1, m_mutex2);
            m_orderList.push_back(i);
            m_mutex1.unlock();
            m_mutex2.unlock();
        }
    }

    void RemoveOrder()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::lock(m_mutex2, m_mutex1);
            if (!m_orderList.empty())
            {
                int i = m_orderList.front();
                m_orderList.pop_front();
                cout << "RemoveOrder执行，删除一个元素11111111111111111111" << i << endl;
            }
            m_mutex1.unlock();
            m_mutex2.unlock();
        }
    }

private:
    list<int> m_orderList;
    std::mutex m_mutex1;
    std::mutex m_mutex2;
};

int main()
{
    myClass my;

    std::thread obj1(&myClass::AddOrder, &my);
    std::thread obj2(&myClass::RemoveOrder, &my);
    obj1.join();
    obj2.join();

    system("pause");
}