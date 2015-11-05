//
// Errors.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/errors/src
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Nov 05 10:00:52 2015 Nicolas Lequain
// Last update Thu Nov 05 10:00:52 2015 Nicolas Lequain
//

#include "Errors.hpp"

/*
** Error
*/

const std::string Error::_separator = "::";

Error::Error(const std::string & location, const std::string & message) :
	_location("error" + this->_separator + location), _message(message)
{

}

Error::~Error()
{

}

const std::string & Error::what() const
{
	return this->_message;
}

const std::string & Error::where() const
{
	return this->_location;
}

/*
** Client
*/

Error::Client::Client(const std::string & location, const std::string & message) :
	Error("client" + this->_separator + location, message)
{

}

Error::Client::~Client()
{

}

/*
** Server
*/

Error::Server::Server(const std::string & location, const std::string & message) :
	Error("server" + this->_separator + location, message)
{

}

Error::Server::~Server()
{

}

/*
** Module
*/

Error::Module::Module(const std::string & location, const std::string & message) :
	Error("module" + this->_separator + location, message)
{

}

Error::Module::~Module()
{

}

/*
** Module : Command
*/

Error::Module::Command::Command(const std::string & location, const std::string & message) :
	Error::Module("command" + this->_separator + location, message)
{

}

Error::Module::Command::~Command()
{

}

/*
** Module : Implementation
*/

Error::Module::Implementation::Implementation(const std::string & location, const std::string & message) :
	Error::Module("implementation" + this->_separator + location, message)
{

}

Error::Module::Implementation::~Implementation()
{

}

/*
** Module : Network
*/

Error::Module::Network::Network(const std::string & location, const std::string & message) :
	Error::Module("network" + this->_separator + location, message)
{

}

Error::Module::Network::~Network()
{

}

/*
** Main
*/

/*
#include <iostream>

int main()
{
	Error::Module::Network::ReadError error;
	Error::Module::Network::WriteError error2;

	std::cout << "[ReadError] what() : " << error.what() << std::endl;
	std::cout << "[ReadError] where() : " << error.where() << std::endl;
	std::cout << std::endl;
	std::cout << "[WriteError] what() : " << error2.what() << std::endl;
	std::cout << "[WriteError] where() : " << error2.where() << std::endl;
	return 0;
}
*/