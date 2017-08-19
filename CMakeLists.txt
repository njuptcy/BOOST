CMAKE_POLICY(SET CMP0015 NEW)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(BOOST_LEARNING )
SET(BOOST_INCLUDE_DIR "F:/FormalBuild_2/BOOST_LEARNING/boost_1_62_0/boost_1_62_0")
SET(BOOST_LIB_DIR  "F:/FormalBuild_2/BOOST_LEARNING/boost_1_62_0/boost_1_62_0/stage/x64/lib/")
SET(MPI_INCLUDE_DIR  "C:/Program Files/MPICH2/include")
FILE(GLOB MPICH2_LIBS "C:/Program Files/MPICH2/lib/*.lib")

INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIR}  ${MPI_INCLUDE_DIR})
LINK_LIBRARIES(${MPICH2_LIBS})
LINK_DIRECTORIES(${BOOST_LIB_DIR})

FILE(GLOB asio_src boost_asio/*.h boost_asio/*.cpp)
ADD_EXECUTABLE(asio ${asio_src})

FILE(GLOB mpi_src boost_mpi/*.h boost_mpi/*.cpp)
ADD_EXECUTABLE(mpi ${mpi_src})

FILE(GLOB serilization boost_serilization/*.cpp boost_serilization/*.h)
ADD_EXECUTABLE(serilization ${serilization})

#ADD_EXECUTABLE(socket)

FILE(GLOB thread_src boost_thread/*.h boost_thread/*.cpp)
ADD_EXECUTABLE(thread ${thread_src})
