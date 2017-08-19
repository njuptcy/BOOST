#include"which_to_run.h"
#define BOOST_THREAD_PROVIDES_FUTURE
#include<boost/thread.hpp>
#ifdef LOCK

boost::mutex mutex;

struct Assamble
{
	boost::thread::id a;
	int b;
	std::string str;
};

void func(boost::promise<Assamble> & p)
{
	using std::cout;
	using std::endl;
	boost::thread::id id = boost::this_thread::get_id();
	for(int i = 0; i < 5; i++)
	{
		//直接在mutex上调用lock与unlock函数
		/*mutex.lock();
		cout << "the thread id is:" << id << endl;
		mutex.unlock();*/

		//通过lock_guard管理mutex
		boost::lock_guard<boost::mutex> lock_guard{mutex};
		cout << "the thread id is:" << id << endl;
	}
	Assamble temp;
	temp.a = id;
	temp.b = 1;
	temp.str = "hello world";
	p.set_value(temp);

}
int main()
{
	boost::promise<Assamble> p;
	boost::promise<Assamble> p_temp;
	boost::future<Assamble> f = p.get_future();
	boost::thread t1{func, std::ref(p)};
	boost::thread t2{func,std::ref(p_temp)};
	Assamble result = f.get();
	getchar();
}
#endif