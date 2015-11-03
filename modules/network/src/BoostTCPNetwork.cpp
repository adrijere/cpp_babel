//
// BoostTCPNetwork.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:53:36 2015 Nicolas Lequain
// Last update Tue Oct 27 16:53:36 2015 Nicolas Lequain
//

#ifdef _SERVER_

# include "BoostTCPNetwork.hpp"

BoostTCPNetwork::BoostTCPNetwork() : _socket(this->_io_service)
{

}

BoostTCPNetwork::~BoostTCPNetwork()
{

}

void BoostTCPNetwork::read(void *buffer, size_t size)
{
	while (this->_socket.available() < size);
	boost::system::error_code error;
	this->_socket.read_some(boost::asio::buffer(buffer, size), error);
	if (error == boost::asio::error::eof)
		return ; // Connection closed cleanly by peer.
	else if (error)
		throw boost::system::system_error(error); // Some other error.
}

void BoostTCPNetwork::write(const void *data, size_t size)
{
	boost::system::error_code error;
	this->_socket.write_some(boost::asio::buffer(data, size), error);
	if (error == boost::asio::error::eof)
		return ; // Connection closed cleanly by peer.
	else if (error)
		throw boost::system::system_error(error); // Some other error.
	printf("%d\n", size);
}

boost::asio::ip::tcp::socket & BoostTCPNetwork::getSocket()
{
	return this->_socket;
}

#endif