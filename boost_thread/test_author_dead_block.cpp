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

		//�ܹ������������
		//����fill�е�notify_all��ִ�У�Ȼ��fill��wait
		//��ʱ�����print��wait����û��������notity print����print��������
		//������random_number.size()==next_sizeʱ���Ͳ�����wait��
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