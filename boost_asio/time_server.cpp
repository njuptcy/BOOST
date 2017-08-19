#include"which_to_run.h"
#ifdef TIME_SERVER
#include<boost/asio/write.hpp>
#include<boost/asio/buffer.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<ctime>
#include<string>
#include<iostream>
#include<boost/asio/read.hpp>
using namespace boost::asio::ip;
using namespace boost::asio;
io_service ioservice;
tcp::endpoint ep{ tcp::v4(), 2014 };
tcp::acceptor tcp_accepter{ ioservice, ep };
//std::string data;
tcp::socket tcp_socket{ ioservice };

//void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
//{
//	if (!ec)
//	{
//		tcp_socket.shutdown(tcp::socket::shutdown_send);
//	}
//}

void accept_handler(const boost::system::error_code & ec)
{
	std::cout << "someone is connect!" << std::endl;
	
	if (!ec)
	{
		while (true)
		{
			//read的时候不能用string，会报错
			/*std::string data_recived;
			//string版本的buffer()返回的是unmodify buffer
			read(tcp_socket, buffer(data_recived, 256));*/
			
			//std::array<char, 256> bytes;
			char bytes[256];
			read(tcp_socket, buffer(bytes, sizeof(bytes)));			
			std::string  data_recived(bytes);
			
			std::cout <<"the data has been recived is:" 
				<<data_recived << std::endl;

			if(data_recived == "disconnect")
			{
				break;
			}
			else if(data_recived == "time")
			{
				std::time_t  time = std::time(0);
				std::string data = std::ctime(&time);
				//tcp_socket.async_write_some( buffer(data), write_handler  );
				//async_write(tcp_socket, buffer(data), write_handler);
				write( tcp_socket, buffer(data));
			}
			else
			{
				std::string data = "unknow command";
				write(tcp_socket, buffer(data));
			}
			


		}
		tcp_socket.shutdown( tcp::socket::shutdown_both);
		tcp_socket.close();

	}

}


int main()
{
	tcp_accepter.listen();
	tcp_accepter.async_accept(tcp_socket, accept_handler);
	std::cout << "waiting someone connect" << std::endl;
	ioservice.run();
}

#endif