#include"which_to_run.h"
#ifdef THREAD_LOCAL_STORAGE2
#include<boost/thread.hpp>
#include<iostream>

struct Test
{
	Test()
	{
		using std::cout;
		using std::endl;
		cout << "Test() is called." << endl;
	}
};


boost::mutex mutex;
void init()
{
	using std::cout;
	using std::endl;
	static boost::thread_specific_ptr<bool> ptr;
	//return the pointer associated with the current thread
	//the initial value is NULL
	if (!ptr.get())
	{
		//����ptr��ָ��Ķ�����ÿ���̶߳����ģ���˷�����ʱ����Ҫ����
		ptr.reset(new bool{true});
		boost::lock_guard<boost::mutex> lock_guard{mutex};
		cout << "do it!"<<endl;
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