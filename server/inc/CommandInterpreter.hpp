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

class Core;

class CommandInterpreter {
public:
    static ACommand *interpretComError(Core *, ACommand *);
    static ACommand *interpretComListRequest(Core *, ACommand *);
    static ACommand *interpretComListResponse(Core *, ACommand *);
    static ACommand *interpretComCoRequest(Core *, ACommand *);
    static ACommand *interpretComCoResponse(Core *, ACommand *);
    static ACommand *interpretPing(Core *, ACommand *);
    static ACommand *interpretComCoChange(Core *, ACommand *);
    static ACommand *interpretComFriendRequest(Core *, ACommand *);
    static ACommand *interpretComFriendResponse(Core *, ACommand *);
};


#endif //CPP_BABEL_COMMANDINTERPRETER_H
