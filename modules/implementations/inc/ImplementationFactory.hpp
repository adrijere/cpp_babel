//
// ImplementationFactory.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:35:19 2015 Nicolas Lequain
// Last update Thu Oct 15 11:35:19 2015 Nicolas Lequain
//

#ifndef IMPLEMENTATIONFACTORY_H_
# define IMPLEMENTATIONFACTORY_H_

# ifdef _SERVER_

#  include "IServer.hpp"
#  include "BoostTCPServer.hpp"

class ImplementationFactory
{
public:
	static IServer * createTCPServer();
};

# else

#  include "IClient.hpp"
#  include "QtTCPClient.hpp"
#  include "QtUDPClient.hpp"
#  include "UnixTCPClient.hpp"

class ImplementationFactory
{
public:
	static IClient * createTCPClient();
	static IClient * createUDPClient();
};

# endif

#endif /* IMPLEMENTATIONFACTORY_H_ */