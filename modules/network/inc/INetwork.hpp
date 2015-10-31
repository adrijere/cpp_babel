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

class INetwork
{
public:
	~INetwork() {}
	/*
	** Reads on the socket and stores the message into the buffer passed as an argument.
	*/
	virtual void read(std::string & buffer) = 0;
	/*
	** Writes the data sent as an argument into the socket.
	*/
	virtual void write(const std::string & data) = 0;
};

#endif /* INETWORK_H_ */