//
// INetwork.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:29:39 2015 Nicolas Lequain
// Last update Tue Oct 27 16:29:39 2015 Nicolas Lequain
//

#ifndef INETWORK_H_
# define INETWORK_H_

# include <string>
# include "MainMutex.hpp"

# define SERVER_PORT_IN 4242
# define SERVER_PORT_OUT 4243
# define CLIENT_PORT_IN 4243
# define CLIENT_PORT_OUT 4242
# define VOIP_PORT_IN 4244
# define VOIP_PORT_OUT 4245

class INetwork
{
public:
	virtual ~INetwork() {}
	/*
	** Reads on the socket and stores the message into the buffer passed as an argument.
	*/
	virtual void read(void *buffer, size_t size) = 0;
	/*
	** Writes the data sent as an argument into the socket.
	*/
	virtual void write(const void *data, size_t size) = 0;
};

#endif /* INETWORK_H_ */