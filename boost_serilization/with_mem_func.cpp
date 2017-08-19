#include"which_to_run.h"
#ifdef SERIALIZATON_WITH_MEM_FUNC

#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<iostream>
#include<sstream>

class Animal
{

public:
	Animal() = default;
	Animal(int leg): leg_{leg} {}
	int leg() const
	{
		return leg_;
	}
private:
	friend boost::serialization::access;
	template<typename Archive>
	void serialize(Archive & a, const unsigned int version)
	{
		a & leg_;
	}
	int leg_;
};

std::stringstream s;

void save()
{
	boost::archive::text_oarchive oa(s);
	Animal monkey{2};
	oa << monkey;
}

void load()
{
	boost::archive::text_iarchive is{s};
	Animal temp;
	is >> temp;
	std::cout << temp.leg();




}



int main()
{
	save();
	load();
	getchar();
}

#endif