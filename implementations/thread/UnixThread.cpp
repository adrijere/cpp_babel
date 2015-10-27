//
// UnixThread.cpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 16:42:24 2015 Nicolas Lequain
// Last update Thu Oct 15 16:42:24 2015 Nicolas Lequain
//

# include "UnixThread.hpp"

UnixThread::UnixThread()
{

}

UnixThread::~UnixThread()
{

}

inline bool UnixThread::launchThread(IRunnable * objectToRun)
{
	return pthread_create(&this->_thread, NULL, UnixThread::execute, (void *)objectToRun) ? false : true;
}

inline bool UnixThread::stopThread()
{
	return pthread_cancel(this->_thread) ? false : true;
}

void * UnixThread::execute(void * object)
{
	IRunnable * self = reinterpret_cast<IRunnable *>(object);
	self->run();
	return NULL;
}
