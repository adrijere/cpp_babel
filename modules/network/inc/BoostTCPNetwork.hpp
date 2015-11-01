//
// BoostTCPNetwork.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Wed Oct 28 20:01:28 2015 Nicolas Lequain
// Last update Wed Oct 28 20:01:28 2015 Nicolas Lequain
//

#ifndef BOOSTTCPNETWORK_H_
# define BOOSTTCPNETWORK_H_

# include <string>
# include <boost/array.hpp>
# include <boost/asio.hpp>
# include "INetwork.hpp"

class BoostTCPNetwork : virtual public INetwork
{
protected:
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::socket _socket;

public:
	BoostTCPNetwork();
	~BoostTCPNetwork();
	virtual void read(void *buffer, size_t size);
	virtual void write(const void *data, size_t size);
	boost::asio::ip::tcp::socket & getSocket();
};

#endif /* BOOSTTCPNETWORK_H_ */