#include"which_to_run.h"
#ifdef  STEADY_TIMER
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

int main()
{
	//���������io_service���ڶ���߳���run
	//��������ö��ϵͳapi���Ǻ��ǻ�Ҫ���ݾ���ʹ���������
	io_service ioservice;
	//timer�ڶ���֮������ʼ��ʱ
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
