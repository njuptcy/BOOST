#include"which_to_run.h"
#ifdef FREEFUNC_SERIALIZE
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<iostream>
#include<sstream>

std::stringstream ss;

class Animal
{
public:
	int _legs;
	char _c;
	std::string _str;
};
template<typename Archive>
void serialize(Archive &ar, Animal & ani, const unsigned int version )
{
	ar & ani._legs;
	ar & ani._c;
    ar & ani._str;
}

int main()
{
	Animal animal{4,'b',"helloworld"};
	boost::archive::text_oarchive oa{ss};
	oa << animal;

	Animal temp{0,0};
	boost::archive::text_iarchive ia{ss};
	ia >> temp;
	using std::cout;
	using std::endl;
	cout << temp._legs<<endl;
	cout << temp._c<<endl;
	cout << temp._str << endl;
	getchar();

}


#endif