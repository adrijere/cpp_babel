//
// IMutex.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Mon Oct 12 19:56:47 2015 Nicolas Lequain
// Last update Mon Oct 12 19:56:47 2015 Nicolas Lequain
//

#ifndef IMUTEX_H_
# define IMUTEX_H_

class IMutex
{
public:
	virtual ~IMutex() {}
	virtual bool lock() = 0;
	virtual bool trylock() = 0;
	virtual bool unlock() = 0;
};

#endif /* IMUTEX_H_ */