//
// IClient.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:33:40 2015 Nicolas Lequain
// Last update Tue Oct 27 16:33:40 2015 Nicolas Lequain
//

#ifndef ICLIENT_H_
# define ICLIENT_H_

# include <string>
# include "INetwork.hpp"

class IClient : virtual public INetwork
{
public:
	~IClient() {}
	/*
	** Connects the socket to the address and port sent as an argument.
	*/
	virtual void connect(const std::string & addr, const short port) = 0;
};

#endif /* ICLIENT_H_ */