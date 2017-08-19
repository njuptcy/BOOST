#include"which_to_run.h"
#ifdef AUTHOR_DEAD_LOCK

#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

boost::mutex mutex;
boost::condition_variable_any cond;
std::vector<int> random_numbers;

void fill()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	for (int i = 0; i < 3; ++i)
	{
		boost::unique_lock<boost::mutex> lock{ mutex };
		random_numbers.push_back(std::rand());
		cond.notify_all();
		cond.wait(mutex);
	}
}

void print()
{

	std::size_t next_size = 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	for (int i = 0; i < 3; ++i)
	{
		boost::unique_lock<boost::mutex> lock{ mutex };

		//能够避免出现死锁
		//假如fill中的notify_all先执行，然后fill中wait
		//此时如果在print中wait，则没有人再来notity print，则print就死锁了
		//所以在random_number.size()==next_size时，就不必再wait了
		//while (random_numbers.size() != next_size)
		//	cond.wait(mutex);
		cond.wait(mutex);
		std::cout << random_numbers.back() << '\n';
		++next_size;
		cond.notify_all();
	}
}

int main()
{
	boost::thread t1{ fill };
	boost::thread t2{ print };
	t1.join();
	t2.join();
	std::cout << "over" << std::endl;
	getchar();
}
#endif