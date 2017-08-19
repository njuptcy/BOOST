#include"which_to_run.h"
#ifdef HTTP_REQUEST
#include<iostream>
#include<string>
#include<array>
#include<boost/asio/buffer.hpp>
#include<boost/asio/write.hpp>
#include<boost/asio/io_service.hpp>
#include<boost/asio/ip/tcp.hpp>
using namespace boost::asio;
io_service service;
ip::tcp::socket tcp_socket{service};
std::array<char, 4096> bytes;
ip::tcp::resolver resolver{service};

void read_handler( const boost::system::error_code &ec, std::size_t bytes_transferred )
{
	if(!ec)
	{
		std::cout.write(bytes.data(), bytes_transferred);
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

void connect_handler(const boost::system::error_code & ec )
{
	if(!ec)
	{
		std::string request = "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
		write(tcp_socket, buffer(request));
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
	
}


void resolve_handler(const boost::system::error_code & ec, ip::tcp::resolver::iterator it  )
{
	if(!ec)
	{
		tcp_socket.async_connect( *it, connect_handler );
	}

}




int main()
{
	ip::tcp::resolver::query  q{ "theboostcpplibraries.com", "80" };
	resolver.async_resolve(q, resolve_handler);
	service.run();
	getchar();

}

#endif