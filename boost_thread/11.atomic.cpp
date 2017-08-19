#include"which_to_run.h"
#ifdef ATOMIC
#include<boost/atomic.hpp>
#include<boost/thread.hpp>

boost::atomic<int> a{0};

void f()
{
	a++;
}
int main()
{
	boost::thread t{f};
	boost::thread t2{f};
	t.join();
	t2.join();
	std::cout << a << std::endl;
	getchar();
}
#endif