#include"which_to_run.h"
#ifdef SERIALIZATION_WITH_FREE_FUNC
#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>
#include<sstream>
#include<iostream>

class Animal
{
public:
	Animal() = default;
	Animal(int legs) :legs_{legs} {}
	int legs() const
	{
		return legs_;
	}
private:
	template<typename Archive>
	friend void serialize(Archive &a, Animal &ani, const unsigned int version);
	int legs_;
};


template<typename Archive>
void serialize( Archive& a,  Animal &ani, const unsigned int version)
{
	a & ani.legs_;
}

std::stringstream s;

void save()
{

	boost::archive::text_oarchive oa(s);
	Animal a{4};
	oa << a;
}

void load()
{

	boost::archive::text_iarchive  ia(s);
	Animal temp;
	ia >> temp;
	std::cout << temp.legs();



}


int main()
{
	save();
	load();
	getchar();

}



#endif