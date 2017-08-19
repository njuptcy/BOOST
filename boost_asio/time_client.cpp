#include"which_to_run.h"
#ifdef TIME_CLIENT
#include<boost/asio/ip/tcp.hpp>
#include<boost/asio/buffer.hpp>
#include<boost/asio/read.hpp>
#include<boost/asio/write.hpp>
#include<iostream>
#include<memory>
#include<string>
using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
	using socket_ptr = std::shared_ptr<tcp::socket>;
	boost::system::error_code error;
	std::array<char, 128> bytes;
	std::string to_send;
	io_service ioservice;
	tcp::endpoint ep{ address::from_string("127.0.0.1") , 2014 };
	//tcp::socket sock{ioservice};
	socket_ptr p_sock = std::make_shared<tcp::socket>(ioservice);
	(*p_sock).connect(ep);
	while(true)
	{
		std::getline(std::cin, to_send);
		/*if(to_send == "q")
		{
			break;
		}*/
		boost::system::error_code error;
		//(*p_sock).write_some(buffer(to_send), error);
		write((*p_sock), buffer(to_send), error);
		if(error)
		{
			break;
		}

		size_t len = (*p_sock).read_some(buffer(bytes), error);

		if (error)
		{
			break;
		}
		std::cout.write(bytes.data(), len);
	}
	//sock.connect(ep, error);
	//tcp::socket sock{ioservice , ep};
	//sock.open();
	//size_t len = read( sock, buffer(bytes));
	//size_t len = sock.read_some(buffer(bytes), error);
	//std::cout.write( bytes.data(), len );
	//getchar();
}





#endif