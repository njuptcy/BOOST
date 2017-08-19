#include"which_to_run.h"
#ifdef SHARE_MUTEX_SHARE_LOCK
#include<boost/thread.hpp>
#include<vector>
#include<random>
#include<fstream>
using namespace std;
vector<int> v_result(10);
boost::shared_mutex shared_mutex;


//void fill()
//{
//	boost::unique_lock<boost::shared_mutex> ul{ shared_mutex };
//	random_device de;
//	default_random_engine e(de());
//	uniform_int_distribution<int> d(1,100);
//	for (int i = 0; i < 10; i++)
//	{
//		v_result.push_back(d(e));
//	}
//}


void watch()
{
	while (1)
	{
		int index, value;
		scanf("%d:%d", &index, &value);
		boost::unique_lock<boost::shared_mutex> ul{shared_mutex};
		v_result[index] = value;
	}

}

void display()
{

	ofstream fout("output");
	while (1)
	{
		for (int i = 0; i < v_result.size(); i++)
		{
			boost::shared_lock<boost::shared_mutex> sl{shared_mutex};
			fout << v_result[i] << " ";
		}
		fout << endl;
		//boost::this_thread::sleep_for(boost::chrono::seconds(1));
	}
}

void p_sum()
{
	while(1)
	{
		int sum = 0;
		for(int i = 0; i < v_result.size(); i++)
		{
			boost::shared_lock<boost::shared_mutex> sl{shared_mutex};
			sum += v_result[i];
		}
//		cout << "sum:" << sum << endl;
	}
}


int main()
{
	boost::thread t{watch};
	boost::thread t2{p_sum};
	boost::thread t3{display};

	t.join();
	t2.join();
	t3.join();
	getchar();



}

#endif