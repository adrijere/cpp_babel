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

# include <utility>
# include <map>
# include <vector>
# include <thread>
# include <mutex>
# include <iostream>
# include "IServer.hpp"
# include "ImplementationFactory.hpp"
# include "BoostTCPNetwork.hpp"
# include "Command.hpp"
# include "CommandInterpreter.hpp"
# include "Errors.hpp"

class ServerCore {
private:
    typedef ACommand *(*fct)(ServerCore *, ACommand *, unsigned short);

    IServer *_connectionsListenerIn;
    IServer *_connectionsListenerOut;
    std::map<unsigned short, std::string> _contactList;
    std::map<unsigned short, fct> _interpreter;
    std::map<unsigned short, std::pair<INetwork *, INetwork *> > _networkList;
    std::map<unsigned short, std::thread *> _threadList;
public:
    ServerCore();
    ~ServerCore();

    IServer *getConnectionsListenerIn() { return this->_connectionsListenerIn; }
    std::map<unsigned short, std::string> &getContactList() { return this->_contactList; }
    std::map<unsigned short, fct> &getInterpreter() { return this->_interpreter; };
    std::map<unsigned short, std::thread *> &getThreadList() { return this->_threadList; }
    std::map<unsigned short, std::pair<INetwork *, INetwork *> > &getNetworkList() { return this->_networkList; }

    void run();
    void connection(unsigned short);
};

#endif