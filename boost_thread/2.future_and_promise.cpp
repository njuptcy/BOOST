#include"which_to_run.h"
#ifdef FUTURE_AND_PROMISE

#define BOOST_THREAD_PROVIDES_FUTURE
#include<boost/thread.hpp>
#include<boost/thread/future.hpp>
#include<string>
#include<iostream>
struct Assamble
{
	Assamble()
	{
		using std::cout;
		using std::endl;
		cout << "Assamble() called" << endl;
	}
	int a;
	int b;
	std::string str;
};

void func( boost::promise<Assamble> & p)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	//p.str = "abc";
	Assamble a;
	a.a = 10;
	a.b = 20;
	a.str = "abc";
	//p.set_value(std::move(a));
	p.set_value(std::move(a));
}




int main()
{
	using std::cout;
	using std::endl;
	boost::promise<Assamble> p;
	boost::future<Assamble> f = p.get_future();
	boost::thread t{func, std::ref(p)};
	cout << "main continue" << endl;
	cout << "waitting..." << endl;
	Assamble result = f.get();
	cout << result.a << endl;
	cout << result.b << endl;
	cout << result.str << endl;
	getchar();


}

#endif