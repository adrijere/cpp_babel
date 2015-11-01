//
// Core.hpp for babel in /home/loir_j/rendu/cpp_babel/server/inc
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:45 2015 Julien Loir
// Last update Mon Oct  26 00:15:45 2015 Julien Loir
//

#ifndef _CORE_HPP_
# define _CORE_HPP_

# include <map>
# include <list>
# include <thread>
# include <mutex>
# include <iostream>
# include "ImplementationFactory.hpp"
# include "Command.hpp"

class Core {
private:
    IServer *_connectionsListener;
    std::map<unsigned short, std::string> _contactList;
    std::list<std::thread *> _threadList;
    std::mutex _mainMutex;
public:
    Core();
    ~Core();
    void run();
    static void connection(INetwork *, std::map<unsigned short, std::string> *, std::mutex *);
};

#endif