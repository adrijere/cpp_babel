//
// ABoostTCPNetwork.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Tue Oct 27 16:51:27 2015 Nicolas Lequain
// Last update Tue Oct 27 16:51:27 2015 Nicolas Lequain
//

#ifndef ABOOSTTCPNETWORK_H_
# define ABOOSTTCPNETWORK_H_

# include <boost/asio.hpp>
# include "INetwork.hpp"

class ABoostTCPNetwork : virtual public INetwork
{
protected:
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::socket _socket;

public:
	~ABoostTCPNetwork();
	virtual void read(std::string & buffer);
	virtual void write(const std::string & data);

protected:
	ABoostTCPNetwork();
};

#endif /* ABOOSTTCPNETWORK_H_ */