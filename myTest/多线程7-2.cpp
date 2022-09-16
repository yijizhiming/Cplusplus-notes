#include <iostream>
#include<thread>
#include<string>
#include<vector>
#include<algorithm>
#include<windows.h>
#include<list>
#include<mutex>

using namespace std;
// 以下是对上面代码优化，用到了lock_guard，防止上锁后忘记解锁。std::adopt_lock作用取消上锁功能
class myClass
{
public:
    void AddOrder()
    {
        for (int i = 0; i < 10000; i++)
        {
            cout << "addOrder执行，插入一个元素" << i << endl;
            std::lock(m_mutex1, m_mutex2);
            //std::adopt_lock作用：取消对锁1上锁，因为上一句已经对锁1进行了上锁
            std::lock_guard<std::mutex> guard1(m_mutex1, std::adopt_lock);
            std::lock_guard<std::mutex> guard2(m_mutex2, std::adopt_lock);
            m_orderList.push_back(i);
        }
    }

    void RemoveOrder()
    {
        for (int i = 0; i < 10000; i++)
        {
            std::lock(m_mutex2, m_mutex1);
            std::lock_guard<std::mutex> guard1(m_mutex1, std::adopt_lock);
            std::lock_guard<std::mutex> guard2(m_mutex2, std::adopt_lock);
            if (!m_orderList.empty())
            {
                int i = m_orderList.front();
                m_orderList.pop_front();
                cout << "RemoveOrder执行，删除一个元素" << i << endl;
            }
        }
    }

private:
    std::list<int> m_orderList;
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