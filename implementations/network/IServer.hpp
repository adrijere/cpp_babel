//
// IServer.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:37:24 2015 Nicolas Lequain
// Last update Tue Oct 27 16:37:24 2015 Nicolas Lequain
//

#ifndef ISERVER_H_
# define ISERVER_H_

# include "INetwork.hpp"

class IServer : virtual public INetwork
{
public:
	~IServer() {}
	/*
	** Asks the server to listen on the port sent as an argument.
	*/
	virtual void listen(const short port) = 0;
	/*
	** Waits for a client to connect to the server.
	*/
	virtual void waitConnection() = 0;
};

#endif /* ISERVER_H_ */