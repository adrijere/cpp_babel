//
// CommandInterpreter.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#include "CommandInterpreter.hpp"

ACommand *CommandInterpreter::interpretComError(Core *mainCore, ACommand *abstractCommand) {
    Command::ComError *command = reinterpret_cast<Command::ComError *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComListRequest(Core *mainCore, ACommand *abstractCommand) {
    Command::ComListRequest *command = reinterpret_cast<Command::ComListRequest *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComListResponse(Core *mainCore, ACommand *abstractCommand) {
    Command::ComListResponse *command = reinterpret_cast<Command::ComListResponse *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComCoRequest(Core *mainCore, ACommand *abstractCommand) {
    Command::ComCoRequest *command = reinterpret_cast<Command::ComCoRequest *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComCoResponse(Core *mainCore, ACommand *abstractCommand) {
    Command::ComCoResponse *command = reinterpret_cast<Command::ComCoResponse *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretPing(Core *mainCore, ACommand *abstractCommand) {
    Command::Ping *command = reinterpret_cast<Command::Ping *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComCoChange(Core *mainCore, ACommand *abstractCommand) {
    Command::ComCoChange *command = reinterpret_cast<Command::ComCoChange *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComFriendRequest(Core *mainCore, ACommand *abstractCommand) {
    Command::ComFriendRequest *command = reinterpret_cast<Command::ComFriendRequest *>(abstractCommand);
}

ACommand *CommandInterpreter::interpretComFriendResponse(Core *mainCore, ACommand *abstractCommand) {
    Command::ComFriendResponse *command = reinterpret_cast<Command::ComFriendResponse *>(abstractCommand);
}

