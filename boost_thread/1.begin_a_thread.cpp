#include"which_to_run.h"
#ifdef BEGIN_A_THREAD
#include<boost\thread.hpp>
#include<iostream>
#include<Windows.h>
void func()
{
	using std::cout;
	using std::endl;
	//try
	//{
	//	boost::this_thread::sleep_for(boost::chrono::seconds(5));
	//}
	//catch(boost::thread_interrupted & e)
	//{
	//	cout << "interrupted!" << endl;
	//}
	//
	try
	{
		for (int i = 0; i < 5; i++)
		{
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
			cout << "thread 1" << endl;
		}
	}
	catch (boost::thread_interrupted & a)
	{
		cout << "interrupted" << endl;
	}

}

int main()
{
	boost::thread t(func);
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	//Sleep(1);
	t.interrupt();
	getchar();
}
#endif