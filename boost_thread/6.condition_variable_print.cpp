#include"which_to_run.h"
#ifdef CONDITION_VARIABLE_ANY
#include<boost/thread.hpp>
#include<iostream>
#include<fstream>
using namespace std;

boost::condition_variable_any con;
boost::mutex mutex;

ofstream fout("condition_output");
bool flag = false;

void print_a()
{
	boost::unique_lock<boost::mutex> ul{mutex};
	flag = true;
	while(1)
	{
		fout << 'a';
		con.notify_all();
		con.wait(mutex);
	}
}
void print_1()
{
	boost::unique_lock<boost::mutex> ul{mutex};
	while(true)
	{
		if(!flag)
		{
			con.wait(mutex);
		}
		fout << '1';
		con.notify_all();
		con.wait(mutex);
	}
}

int main()
{
	boost::thread t1{print_1};
	boost::thread t2{print_a};
	t1.join();
	t2.join();
	return 0;
	
}

#endif