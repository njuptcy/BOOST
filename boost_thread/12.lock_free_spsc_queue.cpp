#include"which_to_run.h"
#ifdef LOCK_FREE_SPSC_QUEUE
#include<boost/thread.hpp>
#include<iostream>
#include<boost/lockfree/spsc_queue.hpp>
#include<boost/lockfree/policies.hpp>
//spsc_queue���ɴ��100��Ԫ��
//spsc_queue�ڲ�ʹ���˻��ζ���ʵ��
//����ռ����ˣ���push�Ļ�push�᷵��false
//boost::lockfree::spsc_queue<int> q{100};
boost::lockfree::spsc_queue<int, boost::lockfree::capacity<100>> q;
int sum = 0;

void producer()
{
	for( int i = 0; i < 100; i++)
	{
		q.push(i);
	}
}

void consumer()
{
	int i = 0;
	while (q.pop(i))
		sum += i;
}

int main()
{
	using std::cout;
	using std::endl;
	boost::thread t1{producer};
	boost::thread t2{consumer};
	t1.join();
	t2.join();
	consumer();
	cout << "sum:" << sum << endl;
	getchar();
}
#endif