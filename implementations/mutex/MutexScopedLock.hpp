//
// MutexScopedLock.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:35:32 2015 Nicolas Lequain
// Last update Thu Oct 15 11:35:32 2015 Nicolas Lequain
//

#ifndef __MUTEXSCOPEDLOCK_HH__
# define __MUTEXSCOPEDLOCK_HH__

# include "IMutex.hpp"

class MutexScopedLock
{
private:
	IMutex & _mutex;

public:
	MutexScopedLock(IMutex & mutex);
	~MutexScopedLock();
};

#endif /* !__MUTEXSCOPEDLOCK_HH__ */