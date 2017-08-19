#include"which_to_run.h"
#ifdef MEMFUNC_SERIALIZE
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<sstream>
#include<iostream>

class Animal
{
private:
	friend boost::serialization::access;
	template<typename Archive>
	void serialize(Archive & a, const unsigned int version)
	{
		a & _legs;
		a & _c;
	}
	int _legs;
	char _c;
public:
	Animal(int lg, char c) :_legs(lg), _c(c)
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

std::stringstream ss;
int main()
{
	Animal a{4,'b'};
	boost::archive::text_oarchive oa{ss};
	oa << a;

	boost::archive::text_iarchive ia{ss};
	Animal temp{0,0};
	ia >> temp;

	using std::cout;
	using std::endl;

	cout << temp.legs() << endl;
	cout << temp.c() << endl;
	

}





#endif