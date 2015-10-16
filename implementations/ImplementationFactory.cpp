//
// ImplementationFactory.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:43:01 2015 Nicolas Lequain
// Last update Thu Oct 15 11:43:01 2015 Nicolas Lequain
//

#include <cstdlib>
#include "ImplementationFactory.hpp"
#include "UnixMutex.hpp"

IThread * ImplementationFactory::createThread()
{
	#ifdef WIN32
		return NULL;
	#else
		return NULL;
	#endif
}

IMutex * ImplementationFactory::createMutex()
{
	#ifdef WIN32
		return NULL;
	#else
		return new UnixMutex();
	#endif
}
