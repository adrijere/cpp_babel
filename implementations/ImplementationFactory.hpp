//
// ImplementationFactory.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/babel
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Thu Oct 15 11:35:19 2015 Nicolas Lequain
// Last update Thu Oct 15 11:35:19 2015 Nicolas Lequain
//

#ifndef IMPLEMENTATIONFACTORY_H_
# define IMPLEMENTATIONFACTORY_H_

# include "IThread.hpp"
# include "IMutex.hpp"

class ImplementationFactory
{
public:
	static IThread * createThread();
	static IMutex * createMutex();
};

#endif /* IMPLEMENTATIONFACTORY_H_ */