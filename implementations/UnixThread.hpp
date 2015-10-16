//
// UnixThread.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 16:41:25 2015 Nicolas Lequain
// Last update Thu Oct 15 16:41:25 2015 Nicolas Lequain
//

#ifndef UNIXTHREAD_H_
# define UNIXTHREAD_H_

# include <pthread.h>
# include "IThread.hpp"

class UnixThread : public IThread
{
private:
	pthread_t _thread;

public:
	UnixThread();
	virtual ~UnixThread();
	virtual inline bool launchThread(IRunnable * objectToRun);
	virtual inline bool stopThread();

private:
	static void * execute(void * object);
};

#endif /* UNIXTHREAD_H_ */