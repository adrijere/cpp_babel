//
// QtTCPClient.hpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef _QTTCPCLIENT_HPP_
# define _QTTCPCLIENT_HPP_

# ifndef _SERVER_

#  include <cstring>
#  include <QTcpSocket>
#  include <QUdpSocket>
#  include "IClient.hpp"

class QtTCPClient : public IClient {
protected:
    QTcpSocket _socket;
public:
    QtTCPClient() {}
    ~QtTCPClient() {}
    void connect(const std::string & addr, const short port);
    void read(void *buffer, size_t size, bool littleEndian = false);
    void write(const void *data, size_t size);
};

#endif

#endif