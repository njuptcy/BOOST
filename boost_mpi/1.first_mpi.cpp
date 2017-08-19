#include"which_to_run.h"
#ifdef FIRST_MPI
#include<boost/mpi.hpp>
#include<iostream>
int main(int argc, char *argv[])
{
	using std::endl;
	using std::cout;
	boost::mpi::environment env{argc, argv};
	boost::mpi::communicator world;
	cout << world.rank() << "," << world.size() << endl;

}
#endif