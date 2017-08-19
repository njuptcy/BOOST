
#include"which_to_run.h"
#ifdef MPI_SEND_CUSTOM_OBJ
#include<boost/mpi.hpp>
#include<iostream>



struct Assamble
{
	int id;
	std::string name;
	unsigned int version;
	template<typename Archive>
	//这个函数需要被boost::serialization::access类访问得到
	void serialize(Archive &ar, const unsigned int v)
	{
		ar & id;
		ar & name;
		ar & version;
	}
};

//template<typename Archive>
//void serialize(Archive &ar, Assamble & obj, const unsigned int version)
//{
//	ar&obj.id;
//	ar&obj.name;
//	ar&obj.version;
//}

int main(int argc, char *argv[])
{
	using std::cout;
	using std::endl;
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;

	if( world.rank() == 0)
	{
		Assamble result;
		boost::mpi::status s = world.recv(boost::mpi::any_source, 16, result);
		cout << result.id << endl;
		cout << result.name << endl;
		cout << result.version << endl;
		cout << "from :" << s.source() << endl;
		
	}
	else
	{
		Assamble to_send;
		to_send.id = 100;
		to_send.name = "hello world";
		to_send.version = 10;
		world.send(0,16,to_send);
	}

}


#endif