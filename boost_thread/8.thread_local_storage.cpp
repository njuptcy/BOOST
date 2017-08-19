#include"which_to_run.h"
#ifdef THREAD_LOCAL_STORAGE
#include<boost/thread.hpp>
#include<iostream>

boost::mutex mutex;
void init()
{
	using std::cout;
	using std::endl;
	boost::lock_guard<boost::mutex> lock_guard{mutex};
	static bool flag = false;
	if ( !flag)
	{
		flag = true;
		cout << "do it!" << endl;
	}
}
void thread()
{
	init();
	init();
}

int main()
{
	boost::thread t[3];
	for(int i = 0; i < 3; i++)
	{
		t[i] = boost::thread{thread};
	}
	for(int i = 0; i < 3; i++)
	{
		t[i].join();
	}
	getchar();
}
#endif