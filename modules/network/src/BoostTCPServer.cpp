//
// BoostTCPServer.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 20:21:03 2015 Nicolas Lequain
// Last update Tue Oct 27 20:21:03 2015 Nicolas Lequain
//

#ifdef _SERVER_

# include "BoostTCPNetwork.hpp"
# include "BoostTCPServer.hpp"

BoostTCPServer::BoostTCPServer() : _acceptor(NULL)
{

}

BoostTCPServer::~BoostTCPServer()
{
	if (this->_acceptor != NULL)
		delete this->_acceptor;
}

void BoostTCPServer::listen(const short port)
{
	if (this->_acceptor != NULL)
		delete this->_acceptor;
	this->_acceptor = new boost::asio::ip::tcp::acceptor(this->_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
}

INetwork * BoostTCPServer::waitConnection()
{
	BoostTCPNetwork * newConnection = new BoostTCPNetwork();

	if (this->_acceptor == NULL)
		return NULL;
	this->_acceptor->accept(newConnection->getSocket());
	return newConnection;
}

#endif