//
// ServerCore.hpp for babel in /home/loir_j/rendu/cpp_babel/server/inc
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
# include <vector>
# include <thread>
# include <mutex>
# include <iostream>
# include "ImplementationFactory.hpp"
# include "BoostTCPNetwork.hpp"
# include "Command.hpp"
# include "CommandInterpreter.hpp"

class ServerCore {
private:
    typedef ACommand *(*fct)(ServerCore *, ACommand *, unsigned short);

    IServer *_connectionsListener;
    std::map<unsigned short, std::string> _contactList;
    std::map<unsigned short, fct> _interpreter;
    std::map<unsigned short, INetwork *> _networkList;
    std::vector<std::thread *> _threadList;
    std::mutex _mainMutex;
public:
    ServerCore();
    ~ServerCore();

    IServer *getConnectionsListener() { return this->_connectionsListener; }
    std::map<unsigned short, std::string> &getContactList() { return this->_contactList; }
    std::map<unsigned short, fct> &getInterpreter() { return this->_interpreter; };
    std::vector<std::thread *> &getThreadList() { return this->_threadList; }
    std::vector<INetwork *> &getNetworkList() { return this->_networkList; }
    std::mutex &getMainMutex() { return this->_mainMutex; }

    void run();
    void connection(unsigned short);
};

#endif