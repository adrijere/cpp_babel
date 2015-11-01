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

class Command {
public:
    class ComError : public ACommand {
    private:
        std::string _error;

    public:
        ComError(unsigned int size) : ACommand() {
            this->_id = 0;
            this->_size = size;
        }
        ComError(INetwork *peer, const std::string &error) {
            this->_id = 0;
            this->_peer = peer;
            this->_error = error;
        }
        ~ComError(){}

        void parse(INetwork *);
        void write();
    };

    class ComListRequest : public ACommand {
    private:
        unsigned short _id_name;

    public:
        ComListRequest(unsigned int size) : ACommand() {
            this->_id = 1;
            this->_size = size;
        }
        ComListRequest(INetwork *peer) {
            this->_id = 1;
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
            this->_id = 2;
            this->_size = size;
        };
        ComListResponse(INetwork *peer, std::map<unsigned short, std::string> &contactList) {
            this->_id = 1;
            this->_peer = peer;
            this->_contactList = contactList;
        }
        ~ComListResponse(){}

        void parse(INetwork *);
        void write();
    };

    class ComCoRequest : public ACommand {
    private:
        std::string _name;

    public:
        ComCoRequest(unsigned int size) : ACommand() {
            this->_id = 3;
            this->_size = size;
        }
        ComCoRequest(INetwork *peer, const std::string &name) {
            this->_id = 1;
            this->_peer = peer;
            this->_name = name;
        }
        ~ComCoRequest(){}

        void parse(INetwork *);
        void write();
    };

    class ComCoResponse : public ACommand {
    private:
        unsigned short _id_name;

    public:
        ComCoResponse(unsigned int size) : ACommand() {
            this->_id = 4;
            this->_size = size;
        }
        ComCoResponse(INetwork *peer, unsigned short id_name) {
            this->_id = 1;
            this->_peer = peer;
            this->_id_name = id_name;
        }
        ~ComCoResponse(){}

        void parse(INetwork *);
        void write();
    };

    class Ping : public ACommand {
    private:
        unsigned short _id_name;

    public:
        Ping(unsigned int size) : ACommand() {
            this->_id = 5;
            this->_size = size;
        }
        Ping(INetwork *peer, unsigned short id_name) {
            this->_id = 1;
            this->_peer = peer;
            this->_id_name = id_name;
        }
        ~Ping(){}

        void parse(INetwork *);
        void write();
    };

    class ComCoChange : public ACommand {
    private:
        unsigned short _id_name;
        unsigned char _status;

    public:
        ComCoChange(unsigned int size) : ACommand() {
            this->_id = 6;
            this->_size = size;
        }
        ComCoChange(INetwork *peer, unsigned short id_name, unsigned char status) {
            this->_id = 1;
            this->_peer = peer;
            this->_id_name = id_name;
            this->_status = status;
        }
        ~ComCoChange(){};

        void parse(INetwork *);
        void write();
    };

    class ComFriendRequest : public ACommand {
    private:
        unsigned short _id_friend;

    public:
        ComFriendRequest(unsigned int size) : ACommand() {
            this->_id = 7;
            this->_size = size;
        }
        ComFriendRequest(INetwork *peer, unsigned short id_friend) {
            this->_id = 1;
            this->_peer = peer;
            this->_id_friend = id_friend;
        }
        ~ComFriendRequest(){}

        void parse(INetwork *);
        void write();
    };

    class ComFriendResponse : public ACommand {
    private:
        unsigned short _id_friend;
        std::string _addr;
        unsigned short _port;

    public:
        ComFriendResponse(unsigned int size) : ACommand() {
            this->_id = 8;
            this->_size = size;
        }
        ComFriendResponse(INetwork *peer, unsigned short id_friend, const std::string &addr, unsigned short port) {
            this->_id = 1;
            this->_peer = peer;
            this->_id_friend = id_friend;
            this->_addr = addr;
            this->_port = port;
        }
        ~ComFriendResponse(){}

        void parse(INetwork *);
        void write();
    };

public:
    static ACommand *parseCommand(INetwork *);
};

#endif /* !COMMAND_HPP_ */
