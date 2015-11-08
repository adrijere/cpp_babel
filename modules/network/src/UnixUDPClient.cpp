//
// UnixUDPClient.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/network/src
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Sun Nov 08 03:46:01 2015 Nicolas Lequain
// Last update Sun Nov 08 03:46:01 2015 Nicolas Lequain
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "UnixUDPClient.hpp"
#include "Errors.hpp"

UnixUDPClient::UnixUDPClient() : _socket(-1)
{

}

UnixUDPClient::~UnixUDPClient()
{

}

bool UnixUDPClient::connect(const std::string & addr, const short port)
{
  struct sockaddr_in info;

  if ((this->_socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto)) == -1)
    return false;
  info.sin_family = AF_INET;
  info.sin_port = htons(port);
  info.sin_addr.s_addr = inet_addr(addr.c_str());
  if (::connect(this->_socket, (struct sockaddr *)&info, sizeof(info)) == -1)
  	return false;
  return true;
}

void UnixUDPClient::read(void *buffer, size_t size)
{
	ssize_t ret = ::read(this->_socket, (char *)buffer, size);
	if (ret == -1)
		throw Error::Module::Network::ReadError();
	if (ret < (ssize_t)size)
		this->read((char *)buffer + ret, size - ret);
}

void UnixUDPClient::write(const void *data, size_t size)
{
	ssize_t ret = ::write(this->_socket, data, size);
	if (ret == -1)
		throw Error::Module::Network::WriteError();
	if (ret < (ssize_t)size)
		this->write((char *)data + ret, size - ret);
}
