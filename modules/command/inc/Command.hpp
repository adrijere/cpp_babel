/*
** Command.hpp for Command in /home/mathon_j/rendu/babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
**
** Started on  Wed Oct 14 19:56:57 2015 Jérémy MATHON
** Last update Sat Oct 24 13:58:55 2015 Jérémy MATHON
*/

#ifndef COMMAND_HPP_
# define COMMAND_HPP_

# include <map>
# include "ACommand.hpp"
# include "CommandManager.hpp"
# include "INetwork.hpp"

typedef enum {
    COM_ERROR_ID,
    COM_LIST_REQUEST_ID,
    COM_LIST_RESPONSE_ID,
    COM_CO_REQUEST_ID,
    COM_CO_CHANGE_ID,
    COM_CALL_REQUEST_ID,
    COM_CALL_CANCEL_ID,
    COM_CALL_RESPONSE_ID,
    COM_MESSAGE_SEND_ID,
    COM_MESSAGE_RECEIVE_ID
} commandId;

class Command {
public:
    class ComError : public ACommand {
    private:
        std::string _error;

    public:
        ComError(unsigned int size) : ACommand() {
            this->_id = COM_ERROR_ID;
            this->_size = size;
        }
        ComError(INetwork *peer, const std::string &error) : ACommand() {
            this->_id = COM_ERROR_ID;
            this->_peer = peer;
            this->_error = error;
        }
        ~ComError(){}

        const std::string &getError() const { return this->_error; }
        void setError(const std::string &error) { this->_error = error; }

        void parse(INetwork *);
        void write();
    };

    class ComListRequest : public ACommand {
    public:
        ComListRequest(unsigned int size) : ACommand() {
            this->_id = COM_LIST_REQUEST_ID;
            this->_size = size;
        }
        ComListRequest(INetwork *peer) : ACommand() {
            this->_id = COM_LIST_REQUEST_ID;
            this->_peer = peer;
        }
        ~ComListRequest(){}

        void parse(INetwork *);
        void write();
    };

    class ComListResponse : public ACommand {
    private:
        std::map<unsigned short, std::string> _contactList;
    public:
        ComListResponse(unsigned int size) : ACommand() {
            this->_id = COM_LIST_RESPONSE_ID;
            this->_size = size;
        };
        ComListResponse(INetwork *peer, std::map<unsigned short, std::string> &contactList) : ACommand() {
            this->_id = COM_LIST_RESPONSE_ID;
            this->_peer = peer;
            this->_contactList = contactList;
        }
        ~ComListResponse(){}

        const std::map<unsigned short, std::string> &getContactList() const { return this->_contactList; }
        void setContactList(const std::map<unsigned short, std::string> &contactList) { this->_contactList = contactList; }

        void parse(INetwork *);
        void write();
    };

    class ComCoRequest : public ACommand {
    private:
        std::string _name;

    public:
        ComCoRequest(unsigned int size) : ACommand() {
            this->_id = COM_CO_REQUEST_ID;
            this->_size = size;
        }
        ComCoRequest(INetwork *peer, const std::string &name) : ACommand() {
            this->_id = COM_CO_REQUEST_ID;
            this->_peer = peer;
            this->_name = name;
        }
        ~ComCoRequest(){}

        const std::string &getName() const { return this->_name; }
        void setName(const std::string &name) { this->_name = name; }

        void parse(INetwork *);
        void write();
    };

    class ComCoChange : public ACommand {
    private:
        unsigned char _status;

    public:
        ComCoChange(unsigned int size) : ACommand() {
            this->_id = COM_CO_CHANGE_ID;
            this->_size = size;
        }
        ComCoChange(INetwork *peer, unsigned char status) : ACommand() {
            this->_id = COM_CO_CHANGE_ID;
            this->_peer = peer;
            this->_status = status;
        }
        ~ComCoChange(){};

        unsigned char getStatus() { return this->_status; }
        void setStatus(unsigned char status) { this->_status = status; }

        void parse(INetwork *);
        void write();
    };

    class ComCallRequest : public ACommand {
    private:
        unsigned short _id_friend;

    public:
        ComCallRequest(unsigned int size) : ACommand() {
            this->_id = COM_CALL_REQUEST_ID;
            this->_size = size;
        }
        ComCallRequest(INetwork *peer, unsigned short id_friend) : ACommand() {
            this->_id = COM_CALL_REQUEST_ID;
            this->_peer = peer;
            this->_id_friend = id_friend;
        }
        ~ComCallRequest(){}

        unsigned short getIdFriend() { return this->_id_friend; }
        void setIdFriend(unsigned short idFriend) { this->_id_friend = idFriend; }

        void parse(INetwork *);
        void write();
    };

    class ComCallCancel : public ACommand {
    private:
        unsigned short _id_friend;

    public:
        ComCallCancel(unsigned int size) : ACommand() {
            this->_id = COM_CALL_CANCEL_ID;
            this->_size = size;
        }
        ComCallCancel(INetwork *peer, unsigned short id_friend) : ACommand() {
            this->_id = COM_CALL_CANCEL_ID;
            this->_peer = peer;
            this->_id_friend = id_friend;
        }
        ~ComCallCancel(){}

        unsigned short getIdFriend() { return this->_id_friend; }
        void setIdFriend(unsigned short idFriend) { this->_id_friend = idFriend; }

        void parse(INetwork *);
        void write();
    };

    class ComCallResponse : public ACommand {
    private:
        unsigned short _id_friend;
        std::string _addr;
        unsigned short _port;

    public:
        ComCallResponse(unsigned int size) : ACommand() {
            this->_id = COM_CALL_RESPONSE_ID;
            this->_size = size;
        }
        ComCallResponse(INetwork *peer, unsigned short id_friend, const std::string &addr, unsigned short port) : ACommand() {
            this->_id = COM_CALL_RESPONSE_ID;
            this->_peer = peer;
            this->_id_friend = id_friend;
            this->_addr = addr;
            this->_port = port;
        }
        ~ComCallResponse(){}

        unsigned short getIdFriend() { return this->_id_friend; }
        const std::string &getAddr() const { return this->_addr; }
        unsigned short getPort() { return this->_port; }
        void setIdFriend(unsigned short idFriend) { this->_id_friend = idFriend; }
        void setAddr(const std::string &addr) { this->_addr = addr; }
        void setPort(unsigned short port) { this->_port = port; }

        void parse(INetwork *);
        void write();
    };

    class ComMessageSend : public ACommand {
    private:
        unsigned short _id_friend;
        std::string _message;

    public:
        ComMessageSend(unsigned int size) : ACommand() {
            this->_id = COM_MESSAGE_SEND_ID;
            this->_size = size;
        }
        ComMessageSend(INetwork *peer, unsigned short id_friend, const std::string &message) : ACommand() {
            this->_id = COM_MESSAGE_SEND_ID;
            this->_peer = peer;
            this->_id_friend = id_friend;
            this->_message = message;
        }
        ~ComMessageSend(){}

        unsigned short getIdFriend() { return this->_id_friend; }
        const std::string &getMessage() const { return this->_message; }
        void setIdFriend(unsigned short idFriend) { this->_id_friend = idFriend; }
        void setMessage(const std::string &message) { this->_message = message; }

        void parse(INetwork *);
        void write();
    };

    class ComMessageReceive : public ACommand {
    private:
        unsigned short _id_friend;
        std::string _message;

    public:
        ComMessageReceive(unsigned int size) : ACommand() {
            this->_id = COM_MESSAGE_RECEIVE_ID;
            this->_size = size;
        }
        ComMessageReceive(INetwork *peer, unsigned short id_friend, const std::string &message) : ACommand() {
            this->_id = COM_MESSAGE_RECEIVE_ID;
            this->_peer = peer;
            this->_id_friend = id_friend;
            this->_message = message;
        }
        ~ComMessageReceive(){}

        unsigned short getIdFriend() { return this->_id_friend; }
        const std::string &getMessage() const { return this->_message; }
        void setIdFriend(unsigned short idFriend) { this->_id_friend = idFriend; }
        void setMessage(const std::string &message) { this->_message = message; }

        void parse(INetwork *);
        void write();
    };

public:
    static ACommand *parseCommand(INetwork *);
};

#endif /* !COMMAND_HPP_ */
