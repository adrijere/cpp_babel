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
    this->_socket.waitForConnected();
}

void QtUDPClient::read(void *buffer, size_t size) {
    while(!(this->_socket.isReadable()
            && this->_socket.waitForReadyRead(2000)
            && this->_socket.bytesAvailable() >= (qint64)size));
    this->_socket.read((char *)buffer, (qint64)size);
}

void QtUDPClient::write(const void *data, size_t size) {
    while (!this->_socket.isWritable());
    QByteArray tmp((char *)data, (int)size);
    this->_socket.write(tmp);
    this->_socket.waitForBytesWritten();
}

#endif