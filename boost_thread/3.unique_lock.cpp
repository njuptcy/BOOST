#include"which_to_run.h"
#ifdef UNIQUE_LOCK
#include<boost/thread.hpp>
boost::mutex mutex;
boost::timed_mutex tmutex;


void func()
{
	using std::cout;
	using std::endl;
	boost::thread::id id = boost::this_thread::get_id();
	for(int i = 0; i < 5; i++)
	{
		boost::unique_lock<boost::mutex> ul{mutex};
		//boost::unique_lock<boost::mutex> ul2 = ul;
		//ul.unlock();
		cout << "the thread id is:" << id << endl;
	}

}

void func2()
{
	using std::cout;
	using std::endl;
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	boost::thread::id id = boost::this_thread::get_id();

	boost::unique_lock<boost::timed_mutex> ul{ tmutex, boost::try_to_lock };
	if(ul.owns_lock())
	{
		cout << "func2 owns lock!" << endl;
	}
	else
	{
		cout << "func2 did not owns lock,try again." << endl;
		if(ul.try_lock_for( boost ::chrono::seconds(1)))
		{
			cout << "try again:func2 owns lock!" << endl;
		}
		else
		{
			cout << "still did not own lock!" << endl;
		}
		
	}
	/*if (ul.owns_lock() || ul.try_lock_for(boost::chrono::seconds(1)))
	{
		cout << "success get lock, and thread is:" << id << endl;
	}*/
	//boost::unique_lock<boost::mutex> ul2 = ul;
	//ul.unlock();	


}


void func3()
{
	tmutex.lock();
	boost::this_thread::sleep_for(boost::chrono::seconds(10));
	tmutex.unlock();
}

int main()
{
	//boost::thread t1{func};
	//boost::thread t2{func};

	boost::thread t2{ func3 };
	boost::thread t1{func2};
	t1.join();
	t2.join();
	getchar();
}


#endif