//
// UnixTCPClient.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/network/src
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
#include "UnixTCPClient.hpp"
#include "Errors.hpp"

UnixTCPClient::UnixTCPClient() : _socket(-1)
{

}

UnixTCPClient::~UnixTCPClient()
{

}

void UnixTCPClient::connect(const std::string & addr, const short port)
{
  struct sockaddr_in info;

  if ((this->_socket = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto)) == -1)
    return ;
  info.sin_family = AF_INET;
  info.sin_port = htons(port);
  info.sin_addr.s_addr = inet_addr(addr.c_str());
  if (::connect(this->_socket, (struct sockaddr *)&info, sizeof(info)) == -1)
    return ;
}

std::string UnixTCPClient::getLocalAddress() const
{
	return "";
}

void UnixTCPClient::read(void *buffer, size_t size)
{
	int ret = ::read(this->_socket, (char *)buffer, size);
	if (ret == -1)
		throw Error::Module::Network::ReadError();
	if (ret < size)
		this->read((char *)buffer + ret, size - ret);
    ((char *)buffer)[ret] = '\0';
}

void UnixTCPClient::write(const void *data, size_t size)
{
	int ret = ::write(this->_socket, data, size);
	if (ret == -1)
		throw Error::Module::Network::WriteError();
	if (ret < size)
		this->write((char *)data + ret, size - ret);
}