//async、future创建后台任务并返回值，希望线程返回一个结果。
//
//async是函数模板，用来启动一个异步任务，启动起来一个异步任务之后，他返回一个future对象，
//future是个类模板。启动一个异步任务就是自动创建一个线程并开始执行对应的线程入口函数，
//他返回一个future对象，这个返回的对象里边含有线程入口函数所返回的结果，
//我们可以通过调用future对象的成员函数get（）来获取结果。future也被称为是提供了一种访问异步操作结果的机制，
//这个结果没有办法马上拿到，但是在线程执行完毕就可以拿到结果。get（）函数不拿到返回值，
//就卡在哪里等待拿值。额外传递一个参数到async（）中，该参数类型是launch（枚举类型），
//来达到一些特殊的目的。async强制异步任务在新线程上执行。
//
//launch：：deferred表示线程入口函数调用被延迟到future的wait（）或者get（）函数调用时才执行。
//如果wait（）和get（）没有调用，线程根本上就没创建，是在主线程中调用的线程入口函数。
//launch：：async在调用async函数的时候就开始创建线程，
//async函数默认用是launch：：async（异步创建新线程） | launch：：deferred(同步不创建新线程)标记，
//具体是哪个由程序决定。
//
//packaged_task，是类模板，把任务包装起来，各种可调对象，通过packaged_task来把各种可调对象包装起来，
//方便将来作为线程入口函数来调用

#include<iostream>                                                                                        
#include<thread>
#include<future>
using namespace std;

//线程入口函数                                                                    
int mythread(int mypar) {
	cout << mypar << endl;
	cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread() and" << std::this_thread::get_id() << endl;
	return 5;
}


 int main() {

	 cout << "main" << "thread = " << std::this_thread::get_id() << endl;
	 std::packaged_task<int(int)> mypt(mythread);  //把函数用mythread通过packaged_task包装起来
	 std::thread t1(std::ref(mypt), 1);  //线程直接开始执行，第二个参数作为线程入口函数的参数
	 t1.join();
	 std::future<int> result = mypt.get_future();  //future对象里包含有线程入口函数的返回结果
	 cout << result.get() << endl;
	 cout << "king hou" << endl;

	 return 0;

}