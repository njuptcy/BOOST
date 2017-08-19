#include"which_to_run.h"
#ifdef RECV_ANY
#include<boost/mpi.hpp>
#include<random>
#include<iostream>
int main(int argc, char*argv[])
{
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;
	
	if(world.rank() == 0)
	{
		for(int i = 0; i < world.size()-1;i++)
		{
			int recv = -1;
			world.recv(boost::mpi::any_source, 16, recv);
			std::cout << recv << std::endl;
		}
	}
	else
	{

		std::random_device rd;
		std::default_random_engine e(rd());
		std::uniform_int_distribution<int> d(1,100);
		world.send(0, 16, d(e));
	}
}
#endif