#include"which_to_run.h"
#ifdef DETECT_SENDER
#include<boost/mpi.hpp>
#include<iostream>
int main(int argc, char *argv[])
{
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;

	if(world.rank() == 0)
	{
		int i;
		boost::mpi::status s = world.recv(
			boost::mpi::any_source, 16, i);
		std::cout << "status.source():" << s.source() << std::endl;
		std::cout << "recv value:" << i << std::endl;
	}
	else
	{
		world.send(0, 16, world.rank());
	}
}

#endif