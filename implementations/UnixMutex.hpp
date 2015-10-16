//
// UnixMutex.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 12:13:24 2015 Nicolas Lequain
// Last update Thu Oct 15 12:13:24 2015 Nicolas Lequain
//

#ifndef UNIXMUTEX_H_
# define UNIXMUTEX_H_

# include <pthread.h>
# include "IMutex.hpp"

class UnixMutex : public IMutex
{
private:
	pthread_mutex_t _mutex;

public:
	UnixMutex();
	virtual ~UnixMutex();
	virtual inline bool lock();
	virtual inline bool trylock();
	virtual inline bool unlock();
};

#endif /* UNIXMUTEX_H_ */