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
# include <vector>
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
    IClient *_mainConnectionIn;
    IClient *_mainConnectionOut;
    std::thread *_readerThread;
    std::map<unsigned short, fct> _interpreter;
    std::map<unsigned short, std::string> _contactList;
    std::vector<unsigned short> _callingList;
    std::vector<unsigned short> _cancellingList;
    std::map<unsigned short, std::vector<std::pair<messageType, std::string> > > _messagesList;
    std::mutex _mainMutex;
public:
    ClientCore(const std::string &, const std::string &);
    ~ClientCore() {}

    const std::string &getName() { return this->_name; }
    std::map<unsigned short, std::string> &getContactList() { return this->_contactList; };
    std::vector<unsigned short> &getCallingList() { return this->_callingList; }
    std::vector<unsigned short> &getCancellingList() { return this->_cancellingList; }
    std::map<unsigned short, std::vector<std::pair<messageType, std::string> > > &getMessagesList() { return this->_messagesList; }
    std::mutex &getMutex() { return this->_mainMutex; }
    void setName(const std::string &name) { this->_name = name; }
    void setContactList(const std::map<unsigned short, std::string> &contactList) { this->_contactList = contactList; }

    void reader();
    void sendComListRequest();
    void sendComCoRequest();
    void sendComCoChange(unsigned char);
    void sendComCallRequest(unsigned short);
    void sendComCallCancel(unsigned short);
    void sendComMessageSend(unsigned short, const std::string &);
};

#endif
