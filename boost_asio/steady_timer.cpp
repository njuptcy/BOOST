#include"which_to_run.h"
#ifdef  STEADY_TIMER
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

int main()
{
	//如果定义多个io_service，在多个线程中run
	//则或许会调用多次系统api，是好是坏要根据具体使用情况来定
	io_service ioservice;
	//timer在定义之后立马开始计时
	steady_timer timer{ ioservice, std::chrono::seconds{ 3 } };
	getchar();
	//asynchronize operation usually used to access resource 
	//outside a process
	//an operation outside a process can be excuted currently
	timer.async_wait([](const boost::system::error_code &ec)
	{ std::cout << "3 sec\n"; });

	steady_timer timer_2{ ioservice , std::chrono::seconds{ 4 } };
	timer_2.async_wait([](const boost::system::error_code &ec)
	{ std::cout << "4 sec\n";  });
	ioservice.run();
	getchar();
}








#endif 
