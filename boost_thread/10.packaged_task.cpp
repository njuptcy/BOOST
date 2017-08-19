#include"which_to_run.h"
#ifdef PACKAGED_TASK
#define BOOST_THREAD_PROVIDES_FUTURE
#include<boost/thread.hpp>
#include<iostream>
#include<utility>
#include<functional>
int sum(int a, int b)
{
	return a + b;
}

int main()
{
	using namespace std::placeholders;
	int a = 1, b = 2;
	boost::packaged_task<int> task{ std::bind(sum, std::ref(a) , std::ref(b))};
	boost::future<int> f = task.get_future();
	boost::thread t{ std::move(task)};
	std::cout << f.get() << std::endl;
	getchar();

}
#endif