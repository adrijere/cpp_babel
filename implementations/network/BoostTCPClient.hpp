//
// BoostTCPClient.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/implementations/network
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Wed Oct 28 14:20:34 2015 Nicolas Lequain
// Last update Wed Oct 28 14:20:34 2015 Nicolas Lequain
//

#ifndef BOOSTTCPCLIENT_H_
# define BOOSTTCPCLIENT_H_

# include "BoostTCPNetwork.hpp"
# include "IClient.hpp"

class BoostTCPClient : virtual public BoostTCPNetwork, virtual public IClient
{
public:
	BoostTCPClient();
	~BoostTCPClient();
	virtual void connect(const std::string & addr, const short port);
};

#endif /* BOOSTTCPCLIENT_H_ */