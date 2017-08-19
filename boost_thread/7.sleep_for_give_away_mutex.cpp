#include"which_to_run.h"
#ifdef SLEEP_GIVE_OUT_MUTEX
#include<boost/thread.hpp>
#include<iostream>
#include<Windows.h>
boost::mutex mutex;
//boost::condition_variable_any con;
//
//bool flag = false;
//void fun1()
//{
//	//boost::unique_lock<boost::mutex> ul{mutex};
//	mutex.lock();
//	flag = true;
//	con.notify_all();
//	boost::this_thread::sleep_for(boost::chrono::seconds(1));
//}
//void fun2()
//{
//	mutex.lock();
//	while(!flag)
//	{
//		con.wait(mutex);
//	}
//	std::cout << "end of fun2" << std::endl;
//}


void fun1()
{
	//mutex.lock();
	//Sleep(1000);
	boost::unique_lock<boost::mutex> ul(mutex);
	printf("fun1 , before sleep_for\n");
	boost::this_thread::sleep_for(boost::chrono::seconds(10));
	printf("fun1 , after sleep_for\n");
	//mutex.unlock();

}

void fun2()
{
	Sleep(1000);
	//mutex.lock();
	//Sleep(1000);
	boost::unique_lock<boost::mutex> ul(mutex);
	printf("fun2 , before sleep_for\n");
	printf("fun22 , after sleep_for\n");
	//mutex.unlock();

}
int main()
{
	boost::thread t1{fun1};
	boost::thread t2{fun2};
	t1.join();
	t2.join();
	getchar();
	return 0;

}




#endif
