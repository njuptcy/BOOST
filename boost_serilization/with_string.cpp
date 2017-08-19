#include"which_to_run.h"
#ifdef WITH_STRING
#include<string>
#include<boost/serialization/string.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>
#include<sstream>
#include<iostream>
#include<utility>
class Animal
{
public:
	Animal() = default;
	Animal(int legs, const std::string& name) 
		: legs_{ legs }, name_{name}
		{    }
	int legs() const
	{
		return legs_;
	}
	std::string name() const
	{
		return name_;
	}
private:
	int legs_;
	std::string name_;

	friend class boost::serialization::access;
	template <typename Archive>
	//what happen if a is not reference?
	//Archive的拷贝构造函数是已删除的
	void serialize( Archive &a, const unsigned int version )
	{
		//Archive的&运算符的右操作数应该是个左值
		//a & legs();
		//a & 4;
		a & legs_;
		a & name_;
	}
};

std::stringstream ss;

void save()
{
	boost::archive::text_oarchive oa{ss};
	Animal a{4, "dogs"};
	oa << a;

}

void load()
{
	using std::cout;
	using std::endl;
	boost::archive::text_iarchive ia{ss};
	Animal temp;
	ia >> temp;
	cout << temp.legs() << endl;
	cout << temp.name() << endl; 
	std::string a_string{ std::move(temp.name()) };

}

int main()
{
	save();
	load();
	getchar();
}


#endif 