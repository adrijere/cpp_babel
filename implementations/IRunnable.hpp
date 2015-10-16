//
// IRunnable.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:35:41 2015 Nicolas Lequain
// Last update Thu Oct 15 11:35:41 2015 Nicolas Lequain
//

#ifndef __IRUNNABLE_HH__
# define __IRUNNABLE_HH__

class IRunnable
{
public:
	virtual ~IRunnable() {}
	virtual void run() = 0;
};

#endif /* !__IRUNNABLE_HH__ */