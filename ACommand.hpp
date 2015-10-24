/*
** ACommand.hpp for ACommand in /home/mathon_j/rendu/babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
**
** Started on  Wed Oct 14 19:56:38 2015 Jérémy MATHON
** Last update Sat Oct 24 13:34:07 2015 Jérémy MATHON
*/

#ifndef ACOMMAND_HPP_
# define ACOMMAND_HPP_

# include	<iostream>
# include	<string>
# include	<cstring>
# include	<sstream>
# include	<map>
# include	<list>

class ACommand : public std::stringstream {
protected:
  char		 id;
  std::string	 cmd;

public:
  ACommand(){};
  virtual ~ACommand(){};
  virtual void	parse() = 0;
  virtual void	execute() = 0;
};

#endif /* !ACOMMAND_HPP_ */
