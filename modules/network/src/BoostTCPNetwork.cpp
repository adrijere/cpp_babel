//
// BoostTCPNetwork.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:53:36 2015 Nicolas Lequain
// Last update Tue Oct 27 16:53:36 2015 Nicolas Lequain
//

#include "BoostTCPNetwork.hpp"

BoostTCPNetwork::BoostTCPNetwork() : _socket(this->_io_service)
{

}

BoostTCPNetwork::~BoostTCPNetwork()
{

}

void BoostTCPNetwork::read(std::string & buffer)
{
	boost::array<char, 4096> readBuffer;
	size_t readLength;
	boost::system::error_code error;

	readLength = this->_socket.read_some(boost::asio::buffer(readBuffer), error);

	if (error == boost::asio::error::eof)
		return ; // Connection closed cleanly by peer.
	else if (error)
		throw boost::system::system_error(error); // Some other error.

	buffer.erase();
	buffer.insert(0, readBuffer.data(), readLength);
}

void BoostTCPNetwork::write(const std::string & data)
{
	boost::system::error_code ignored_error; /* Permet d'ignorer les erreurs */

	boost::asio::write(this->_socket, boost::asio::buffer(data), ignored_error);
}

boost::asio::ip::tcp::socket & BoostTCPNetwork::getSocket()
{
	return this->_socket;
}
