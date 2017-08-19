#include"which_to_run.h"
#ifdef SERIALIZATION_VERSION2
#include<iostream>
#include<fstream>
#include<boost/archive/text_iarchive.hpp>
#include<boost/serialization/string.hpp>

struct Assamble
{
	int legs;
	std::string name;
};

template<typename Archive>
void serialize(Archive &ar, Assamble &obj, const unsigned int version)
{
	ar & obj.legs;
	if (version >= 1)
	{
		ar & obj.name;
	}
}

int main()
{
	std::ifstream ifs("ostream.text");
	boost::archive::text_iarchive ia{ifs};
	Assamble result;
	ia >> result;
	using std::cout;
	using std::endl;
	cout << result.legs<<endl;
	cout << result.name << endl;
	return 0;
}



#endif