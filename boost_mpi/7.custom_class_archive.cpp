#include"which_to_run.h"
#ifdef CUSTOM_CLASS_ARCHIVE
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<iostream>
#include<sstream>

std::stringstream ss;

class Animal
{
private:
	int _legs;
	char _c;
public:
	Animal(int lg, char c):_legs(lg),_c(c)
	{
	}
	int legs()
	{
		return _legs;
	}
	char c()
	{
		return _c;
	}
	void set_legs(int lg)
	{
		_legs = lg;
	}
	void set_c(char c)
	{
		_c = c;
	}
};
void operator<<(boost::archive::text_oarchive &oa, Animal &a)
{
	oa << a.legs();
	oa << a.c();
}
void operator >> (boost::archive::text_iarchive &ia, Animal &a)
{
	int lg;
	char c;
	ia >> lg;
	ia >> c;
	a.set_legs(lg);
	a.set_c(c);
}
int main()
{
	Animal a{4,'b'};
	boost::archive::text_oarchive oa{ss};
	oa << a;

	Animal temp{0,0};
	boost::archive::text_iarchive ia{ss};
	ia >> temp;

	using std::cout;
	using std::endl;

	cout << temp.legs() << endl;
	cout << temp.c() << endl;
	getchar();





}

#endif