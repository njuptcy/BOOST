#include"which_to_run.h"
#ifdef WITH_VERSION
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<iostream>
#include<sstream>


using namespace std;
stringstream ss;
class Animal
{
public :
	Animal() = default;
	Animal(int legs, const string &name) :
		legs_{ legs }, name_{name}
	{

	}
	int legs() const
	{
		return legs_;
	}
	string name() const
	{
		return name_;
	}
private:
	int legs_;
	string name_;
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &a ,  unsigned int version)
	{
		a & legs_;
		if(version > 0)
		{
			a & name_;
		}
	}

};

BOOST_CLASS_VERSION(Animal, 1)

void save()
{
	boost::archive::text_oarchive oa{ss};
	Animal a{4, "hello"};
	oa << a;
}

void load()
{
	boost::archive::text_iarchive ia{ss};
	Animal temp;
	ia >> temp;
	cout << temp.legs() << endl;
	cout << temp.name() << endl;
}


int main()
{
	
}


#endif