#include"which_to_run.h"
#ifdef SERIALIZATION_VERSION
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<iostream>
#include<fstream>
//#include<sstream>
//std::stringstream ss;

struct Assamble
{
	int legs;
	std::string name;
};

template<typename Archive>
void serialize(Archive &ar, Assamble &obj, const unsigned int version)
{
	ar & obj.legs;
	ar & obj.name;
	/*if(version >= 1)
	{
		ar & obj.name;
	}*/
}

BOOST_CLASS_VERSION(Assamble, 0)

int main()
{
	std::ofstream of("ostream.text");
	boost::archive::text_oarchive oa{of};
	Assamble temp;
	temp.legs = 4;
	temp.name = "hello world";
	oa << temp;
	return 0;

}


#endif