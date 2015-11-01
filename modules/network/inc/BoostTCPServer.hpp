//
// BoostTCPServer.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 20:19:37 2015 Nicolas Lequain
// Last update Tue Oct 27 20:19:37 2015 Nicolas Lequain
//

#ifndef BOOSTTCPSERVER_H_
# define BOOSTTCPSERVER_H_

# include <boost/asio.hpp>
# include "IServer.hpp"

class BoostTCPServer : public IServer
{
private:
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::acceptor * _acceptor;

public:
	BoostTCPServer();
	~BoostTCPServer();
	virtual void listen(const short port);
	virtual INetwork * waitConnection();
};

#endif /* BOOSTTCPSERVER_H_ */