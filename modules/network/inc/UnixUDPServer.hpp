//
// UnixUDPServer.hpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef _UNIXUDPSERVER_HPP_
# define _UNIXUDPSERVER_HPP_

# ifndef _SERVER_

#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <netdb.h>
#  include "IServer.hpp"
#  include "UnixUDPClient.hpp"

class UnixUDPServer : public IServer {
private:
    int _fd_server;
public:
    void listen(const short port);
    INetwork * waitConnection();
};

# endif

#endif
