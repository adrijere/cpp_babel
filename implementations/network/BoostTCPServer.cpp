//
// BoostTCPServer.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 20:21:03 2015 Nicolas Lequain
// Last update Tue Oct 27 20:21:03 2015 Nicolas Lequain
//

#include "BoostTCPServer.hpp"

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

void BoostTCPServer::waitConnection()
{
	if (this->_acceptor == NULL)
		return ;
	this->_acceptor->accept(this->_socket);
}

int main()
{
	BoostTCPServer server;

	server.listen(4242);
	server.waitConnection();
	server.write("ok ta mer");
}