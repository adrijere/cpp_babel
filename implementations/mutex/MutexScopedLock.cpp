//
// MutexScopedLock.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:35:50 2015 Nicolas Lequain
// Last update Thu Oct 15 11:35:50 2015 Nicolas Lequain
//

#include "MutexScopedLock.hpp"

MutexScopedLock::MutexScopedLock(IMutex & mutex) : _mutex(mutex)
{
	this->_mutex.lock();
}

MutexScopedLock::~MutexScopedLock()
{
	this->_mutex.unlock();
}
