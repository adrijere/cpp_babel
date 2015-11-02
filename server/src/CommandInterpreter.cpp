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
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " sent an error : " << command->getError();
    std::cout << "."<< std::endl;
    return NULL;
}

ACommand *CommandInterpreter::interpretComListRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComListRequest *command = reinterpret_cast<Command::ComListRequest *>(abstractCommand);
    (void)command;
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is asking for contact list." << std::endl;
    return new Command::ComListResponse(mainCore->getNetworkList()[idClient], mainCore->getContactList());
}

/* not used server-side */
ACommand *CommandInterpreter::interpretComListResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComListResponse *command = reinterpret_cast<Command::ComListResponse *>(abstractCommand);
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

ACommand *CommandInterpreter::interpretComCoRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoRequest *command = reinterpret_cast<Command::ComCoRequest *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is setting/changing his name : " << command->getName();
    std::cout << "." << std::endl;
    mainCore->getContactList()[idClient] = command->getName();
    return NULL;
}

/* not yet implemented */
ACommand *CommandInterpreter::interpretComCoChange(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoChange *command = reinterpret_cast<Command::ComCoChange *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is setting his status to : " << command->getStatus();
    std::cout << "." << std::endl;
    return NULL;
}

/* not yet implemented */
ACommand *CommandInterpreter::interpretComCallRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallRequest *command = reinterpret_cast<Command::ComCallRequest *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is calling the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    return NULL;
}

/* not yet implemented */
ACommand *CommandInterpreter::interpretComCallCancel(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallCancel *command = reinterpret_cast<Command::ComCallCancel *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is canceling his call to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    return NULL;
}

/* not yet implemented */
ACommand *CommandInterpreter::interpretComCallResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallResponse *command = reinterpret_cast<Command::ComCallResponse *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is accepting the call to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    return NULL;
}

/* not yet implemented */
ACommand *CommandInterpreter::interpretComMessageSend(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComMessageSend *command = reinterpret_cast<Command::ComMessageSend *>(abstractCommand);
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is sending the message \"" << command->getMessage() << "\"";
    std::cout << " to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    return NULL;
}

/* not used server-side */
ACommand *CommandInterpreter::interpretComMessageReceive(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComMessageReceive *command = reinterpret_cast<Command::ComMessageReceive *>(abstractCommand);
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}
