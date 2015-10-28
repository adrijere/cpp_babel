//
// BoostTCPClient.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Wed Oct 28 14:23:06 2015 Nicolas Lequain
// Last update Wed Oct 28 14:23:06 2015 Nicolas Lequain
//

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "BoostTCPClient.hpp"

BoostTCPClient::BoostTCPClient()
{

}

BoostTCPClient::~BoostTCPClient()
{

}

void BoostTCPClient::connect(const std::string & addr, const short port)
{
	boost::asio::ip::tcp::resolver				resolver(this->_io_service);
	boost::asio::ip::tcp::resolver::query		query(addr, boost::lexical_cast<std::string>(port));
	boost::asio::ip::tcp::resolver::iterator 	endpoint_iterator = resolver.resolve(query);

	boost::asio::connect(this->_socket, endpoint_iterator);
}
