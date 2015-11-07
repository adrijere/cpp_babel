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
# include "Errors.hpp"

class ClientCore {
private:
    typedef ACommand *(*fct)(ClientCore *, ACommand *);

    std::string _name;
    IClient *_mainConnectionIn;
    IClient *_mainConnectionOut;
    std::thread *_readerThread;
    std::map<unsigned short, fct> _interpreter;
    bool _contactsUpdate;
    std::map<unsigned short, std::string> _contactList;
    bool _callingUpdate;
    std::vector<unsigned short> _callingList;
    bool _cancellingUpdate;
    std::vector<unsigned short> _cancellingList;
    bool _messagesUpdate;
    std::map<unsigned short, std::vector<std::pair<messageType, std::string> > > _messagesList;
    short _callingFriend;
public:
    ClientCore(const std::string &, const std::string &);
    ~ClientCore() {}

    const std::string &getName() { return this->_name; }
    std::map<unsigned short, std::string> &getContactList() { return this->_contactList; };
    std::vector<unsigned short> &getCallingList() { return this->_callingList; }
    std::vector<unsigned short> &getCancellingList() { return this->_cancellingList; }
    std::map<unsigned short, std::vector<std::pair<messageType, std::string> > > &getMessagesList() { return this->_messagesList; }
    void setName(const std::string &name) { this->_name = name; }
    void setContactList(const std::map<unsigned short, std::string> &contactList) { this->_contactList = contactList; }
    const IClient * getMainConnectionIn() const { return this->_mainConnectionIn; }
    const IClient * getMainConnectionOut() const { return this->_mainConnectionOut; }

    bool getContactsUpdate() { return this->_contactsUpdate; }
    bool getCallingUpdate() { return this->_callingUpdate; }
    bool getCancellingUpdate() { return this->_cancellingUpdate; }
    bool getMessagesUpdate() { return this->_messagesUpdate; }
    short getCallingFriend() { return this->_callingFriend; }
    void setContactsUpdate(bool newValue) { this->_contactsUpdate = newValue; }
    void setCallingUpdate(bool newValue) { this->_callingUpdate = newValue; }
    void setCancellingUpdate(bool newValue) { this->_cancellingUpdate = newValue; }
    void setMessagesUpdate(bool newValue) { this->_messagesUpdate = newValue; }
    void setCallingFriend(short newValue) { this->_callingFriend = newValue; }

    void reader();
    void sendComListRequest();
    void sendComCoRequest();
    void sendComCoChange(unsigned char);
    void sendComCallRequest(unsigned short);
    void sendComCallCancel(unsigned short);
    void sendComMessageSend(unsigned short, const std::string &);
    void sendComCallResponse(unsigned short, const std::string &, unsigned short);
};

#endif
