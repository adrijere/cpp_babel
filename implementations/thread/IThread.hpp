//
// IThread.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Mon Oct 12 21:30:32 2015 Nicolas Lequain
// Last update Mon Oct 12 21:30:32 2015 Nicolas Lequain
//

#ifndef ITHREAD_H_
# define ITHREAD_H_

# include "IRunnable.hpp"

class IThread
{
public:
	virtual ~IThread() {}
	virtual bool launchThread(IRunnable * objectToRun) = 0;
	virtual bool stopThread() = 0;
};

#endif /* ITHREAD_H_ */