//
// ImplementationFactory.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:43:01 2015 Nicolas Lequain
// Last update Thu Oct 15 11:43:01 2015 Nicolas Lequain
//

#include "ImplementationFactory.hpp"

#ifdef _SERVER_

IServer * ImplementationFactory::createTCPServer()
{
	return new BoostTCPServer();
}

#else

IClient * ImplementationFactory::createTCPClient()
{
	return new BoostTCPClient();
}

#endif
