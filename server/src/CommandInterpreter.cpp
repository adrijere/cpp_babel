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

ACommand *CommandInterpreter::interpretComError(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComError *command = reinterpret_cast<Command::ComError *>(abstractCommand);
    (void)mainCore;
    std::cout << "Client " << idClient << " sent an error : " << command->getError() << std::endl;
    return NULL;
}

ACommand *CommandInterpreter::interpretComListRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComListRequest *command = reinterpret_cast<Command::ComListRequest *>(abstractCommand);
    (void)command;
    return new Command::ComListResponse(mainCore->getNetworkList()[idClient], mainCore->getContactList());
}

ACommand *CommandInterpreter::interpretComListResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComListResponse *command = reinterpret_cast<Command::ComListResponse *>(abstractCommand);
    /* not used server-side */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretComCoRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoRequest *command = reinterpret_cast<Command::ComCoRequest *>(abstractCommand);
    (void)mainCore;
    (void)command;
    (void)idClient;
    mainCore->getContactList()[idClient] = command->getName();
    return new Command::ComCoResponse(mainCore->getNetworkList()[idClient], idClient);
}

ACommand *CommandInterpreter::interpretComCoResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoResponse *command = reinterpret_cast<Command::ComCoResponse *>(abstractCommand);
    /* not used server-side */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretPing(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::Ping *command = reinterpret_cast<Command::Ping *>(abstractCommand);
    /* not used server-side */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretComCoChange(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoChange *command = reinterpret_cast<Command::ComCoChange *>(abstractCommand);
    /* not yet implemented */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretComFriendRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComFriendRequest *command = reinterpret_cast<Command::ComFriendRequest *>(abstractCommand);
    /* not yet implemented */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretComFriendResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComFriendResponse *command = reinterpret_cast<Command::ComFriendResponse *>(abstractCommand);
    /* not used server-side */
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}
