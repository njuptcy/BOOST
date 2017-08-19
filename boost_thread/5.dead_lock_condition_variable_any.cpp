#include"which_to_run.h"
#ifdef DEAD_LOCK_CONDITION_VARIABLE_ANY
#include<boost/thread.hpp>

boost::condition_variable_any con;
boost::mutex mutex;
void func1()
{
	con.notify_all();
	con.wait(mutex);
}
void func2()
{
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	con.wait(mutex);
	con.notify_all();
}
int main()
{
	boost::thread t1{func1};
	boost::thread t2{func2};
	t1.join();
	t2.join();
	std::cout << "end" << std::endl;
}

#endif