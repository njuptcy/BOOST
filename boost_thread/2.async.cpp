#include"which_to_run.h"
#define BOOST_THREAD_PROVIDES_FUTURE
#ifdef ASYNC
#include<boost/thread.hpp>

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

Assamble func()
{
	Assamble result;
	result.a = 1;
	result.b = 2;
	result.str = "hello";
	return result;

}
int main()
{
	boost::future<Assamble> f = boost::async(func);
	Assamble r = f.get();
	printf("result.a:%d\n", r.a);
	printf("result.b:%d\n", r.b);
	printf("result.a:%s\n", r.str.c_str());
	getchar();
	
}

#endif