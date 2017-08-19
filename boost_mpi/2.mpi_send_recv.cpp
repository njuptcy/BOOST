#include"which_to_run.h"
#ifdef SEND_RECV

#include<boost/mpi.hpp>
#include<iostream>

int main(int argc, char *argv[])
{
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;
	if(world.rank() == 0)
	{
		world.send(1, 16, 100);
	}
	else if( world.rank() == 1)
	{
		int i = 0;
		world.recv(0, 16, i);
		std::cout << i << std::endl;
	}
}

#endif