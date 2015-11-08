//
// UnixUDPServer.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef _SERVER_

# include "UnixUDPServer.hpp"

void UnixUDPServer::listen(const short port) {
    struct sockaddr_in	info;
    int			fd;

    if ((fd = socket(AF_INET, SOCK_STREAM, getprotobyname("UDO")->p_proto)) == -1) {
        this->_fd_server = -1;
        return ;
    }
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&info, sizeof(struct sockaddr_in)) == -1) {
        this->_fd_server = -1;
        return ;
    }
    if (::listen(fd, port) == -1) {
        this->_fd_server = -1;
        return ;
    }
    this->_fd_server = fd;
}

INetwork * UnixUDPServer::waitConnection() {
    struct sockaddr_in addr;
    socklen_t len;
    UnixUDPClient *accepted = new UnixUDPClient();
    int fd = accept(_fd_server, (struct sockaddr *)&addr, &len);
    accepted->setSocket(fd);
    return accepted;
}

#endif