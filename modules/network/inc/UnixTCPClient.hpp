//
// UnixTCPClient.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/network/inc
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Sun Nov 08 03:43:46 2015 Nicolas Lequain
// Last update Sun Nov 08 03:43:46 2015 Nicolas Lequain
//

#ifndef UNIXTCPCLIENT_H_
# define UNIXTCPCLIENT_H_

#  include "IClient.hpp"

class UnixTCPClient : public IClient
{
private:
	int _socket;

public:
	UnixTCPClient();
	~UnixTCPClient();
    void connect(const std::string & addr, const short port);
	std::string getLocalAddress() const;
    void read(void *buffer, size_t size);
    void write(const void *data, size_t size);
};

#endif /* UNIXTCPCLIENT_H_ */