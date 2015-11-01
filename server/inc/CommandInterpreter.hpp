//
// CommandInterpreter.hpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#ifndef CPP_BABEL_COMMANDINTERPRETER_H
#define CPP_BABEL_COMMANDINTERPRETER_H

# include "Command.hpp"
# include "ServerCore.hpp"

class ServerCore;

class CommandInterpreter {
public:
    static ACommand *interpretComError(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComListRequest(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComListResponse(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComCoRequest(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComCoResponse(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretPing(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComCoChange(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComFriendRequest(ServerCore *, ACommand *, unsigned short);
    static ACommand *interpretComFriendResponse(ServerCore *, ACommand *, unsigned short);
};


#endif //CPP_BABEL_COMMANDINTERPRETER_H
