#include"which_to_run.h"
#ifdef SEND_RECV_STRING
#include<boost/mpi.hpp>
#include<iostream>
#include<boost/serialization/string.hpp>
int main(int argc, char *argv[])
{
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;
	if(world.rank()==0)
	{
		std::string str_rec;
		world.recv(boost::mpi::any_source, 16, str_rec);
		std::cout << str_rec << std::endl;
	}
	else
	{
		std::string str_send = "hello world";
		world.send(0, 16, str_send);
	}
}
#endif