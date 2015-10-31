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
#include "BoostTCPClient.hpp"
#include "BoostTCPServer.hpp"

IClient * ImplementationFactory::createTCPClient()
{
	return new BoostTCPClient();
}

IServer * ImplementationFactory::createTCPServer()
{
	return new BoostTCPServer();
}
