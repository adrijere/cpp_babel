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

void BoostTCPNetwork::read(void *buffer, size_t size, bool littleEndian)
{
	boost::array<char, 1> readBuffer;
	size_t readLength = 0;
	boost::system::error_code error;

	while (readLength < size)
	{
		readLength += this->_socket.read_some(boost::asio::buffer(readBuffer), error);
		if (error == boost::asio::error::eof)
			return ; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.
		if (littleEndian)
			std::memcpy((char *)(buffer) + readLength - 1, &readBuffer[0], 1);
		else
			std::memcpy((char *)(buffer) + size - readLength, &readBuffer[0], 1);
	}
}

void BoostTCPNetwork::write(const void *data, size_t size)
{
	boost::array<char, 1> writeBuffer;
	size_t writeLength = 0;
	boost::system::error_code error;

	while (writeLength < size)
	{
		writeBuffer[0] = ((char *)data)[writeLength];
		writeLength += boost::asio::write(this->_socket, boost::asio::buffer(writeBuffer), error);
		if (error == boost::asio::error::eof)
			return ; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.
	}
}

boost::asio::ip::tcp::socket & BoostTCPNetwork::getSocket()
{
	return this->_socket;
}
