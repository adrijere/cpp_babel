//
// ClientCore.hpp for babel in /home/loir_j/rendu/cpp_babel/server/inc
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:45 2015 Julien Loir
// Last update Mon Oct  26 00:15:45 2015 Julien Loir
//

#ifndef _CLIENTCORE_HPP_
#define _CLIENTCORE_HPP_

# include <map>
# include <thread>
# include <mutex>
# include "ImplementationFactory.hpp"
# include "QtTCPClient.hpp"
# include "QtUDPClient.hpp"
# include "Command.hpp"
# include "CommandInterpreter.hpp"

class ClientCore {
private:
    typedef ACommand *(*fct)(ClientCore *, ACommand *);

    std::string _name;
    IClient *_mainConnection;
    std::thread *_readerThread;
    std::map<unsigned short, fct> _interpreter;
    std::mutex _mainMutex;
public:
    ClientCore(const std::string &, const std::string &, unsigned short);
    ~ClientCore() {}
    void reader();
    void sendComListRequest();
    void sendComCoRequest();
    void sendComCoChange(unsigned char);
    void sendComCallRequest(unsigned short);
    void sendComCallCancel(unsigned short);
    void sendComMessageSend(unsigned short);
};

#endif
