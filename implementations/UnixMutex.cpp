//
// UnixMutex.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 13:11:33 2015 Nicolas Lequain
// Last update Thu Oct 15 13:11:33 2015 Nicolas Lequain
//

#include "UnixMutex.hpp"

UnixMutex::UnixMutex()
{
	(void)pthread_mutex_init(&this->_mutex, NULL);
}

UnixMutex::~UnixMutex()
{
	(void)pthread_mutex_destroy(&this->_mutex);
}

inline bool UnixMutex::lock()
{
	return pthread_mutex_lock(&this->_mutex) ? false : true;
}

inline bool UnixMutex::trylock()
{
	return pthread_mutex_trylock(&this->_mutex) ? false : true;
}

inline bool UnixMutex::unlock()
{
	return pthread_mutex_unlock(&this->_mutex) ? false : true;
}

