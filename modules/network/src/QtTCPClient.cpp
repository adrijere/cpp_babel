//
// QtTCPClient.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef _SERVER_

# include "QtTCPClient.hpp"

void QtTCPClient::connect(const std::string & addr, const short port) {
    this->_socket.connectToHost(QString(addr.c_str()), (quint16)port);
}

void QtTCPClient::read(void *buffer, size_t size, bool littleEndian) {
    unsigned int readLength = 0;
    char readBuffer[1];

    while (readLength < size) {
        readLength += this->_socket.read(readBuffer, 1);
		if (littleEndian)
			std::memcpy((char *)(buffer) + readLength - 1, readBuffer, 1);
		else
			std::memcpy((char *)(buffer) + size - readLength, readBuffer, 1);
    }
}

void QtTCPClient::write(const void *data, size_t size) {
    this->_socket.write((char *)data, (quint64)size);
}

#endif