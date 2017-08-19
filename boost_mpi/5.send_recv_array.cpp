#include"which_to_run.h"
#ifdef SEND_RECV_ARRAY
#include<boost/mpi.hpp>
#include<iostream>

int main(int argc, char *argv[])
{
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;

	if(world.rank()==0)
	{
		char buffer[13];
		world.recv(boost::mpi::any_source, 16, buffer,13);
		std::cout << buffer << std::endl;
	}
	else
	{
		char *to_send = "hello world";
		world.send(0, 16, to_send, strlen(to_send)+1);
	}
}
#endif