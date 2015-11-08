//
// UnixUDPClient.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/network/inc
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Sun Nov 08 03:43:46 2015 Nicolas Lequain
// Last update Sun Nov 08 03:43:46 2015 Nicolas Lequain
//

#ifndef UNIXUDPCLIENT_H_
# define UNIXUDPCLIENT_H_

#  include "IClient.hpp"

class UnixUDPClient : public IClient
{
private:
	int _socket;

public:
	UnixUDPClient();
	~UnixUDPClient();
    void connect(const std::string & addr, const short port);
    void read(void *buffer, size_t size);
    void write(const void *data, size_t size);
    void setSocket(int socket) { this->_socket = socket; }
};

#endif /* UNIXTCPCLIENT_H_ */