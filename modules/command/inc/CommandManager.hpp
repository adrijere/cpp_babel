/*
** CommandManager.hpp for CommandManager in /home/mathon_j/rendu/cpp_babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@epitech.net>
**
** Started on  Sat Oct 24 13:33:34 2015 Jérémy MATHON
** Last update Sat Oct 24 13:33:47 2015 Jérémy MATHON
*/

#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <sstream>

class CommandManager : public std::stringstream {
 public:
  template <typename T>
  std::ostream &write(T data) {
    std::stringstream::write((char *)&data, sizeof(T));
    return *this;
  }
  template <typename T>
  std::istream &read(T *data) {
    std::stringstream::read((char *)data, sizeof(T));
    return *this;
  }
};

#endif /* COMMANDMANAGER_H_ */
