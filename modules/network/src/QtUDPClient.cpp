//
// QtUDPClient.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef _SERVER_

# include "QtUDPClient.hpp"

void QtUDPClient::connect(const std::string & addr, const short port) {
    this->_socket.connectToHost(QString(addr.c_str()), (quint16)port);
}

void QtUDPClient::read(void *buffer, size_t size, bool littleEndian) {
    this->_socket.read((char *)buffer, (quint64)size);
}

void QtUDPClient::write(const void *data, size_t size) {
    this->_socket.write((char *)data, (quint64)size);
}

#endif