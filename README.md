# Boost
 demonstrate how to use boost library, and modify the which_to_run.h file to specify which program you want to run.

# How to build
 1.Build your boost library ( Mine is boost_1_62 )
 2.Modify CMakeLists.txt, change BOOST_INCLUDE_DIR,BOOST_LIB_DIR to corresponding directories 
 ( please refer to the path of mine)
 3.If you want to use Boost MPI library, you need a MPI tool, Mine is MPICH2, the directories where the
  MPICH2 has installed in, contain the header files and libraries files we need.Just modify the path used by MPI_INCLUDE_DIR
  and MPICH2_LIBS suitably;