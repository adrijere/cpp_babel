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

#ifdef _SERVER_

ACommand *CommandInterpreter::interpretComError(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComError *command = reinterpret_cast<Command::ComError *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " sent an error : " << command->getError();
    std::cout << "."<< std::endl;
    MainMutex::mutex().unlock();
    return NULL;
}

ACommand *CommandInterpreter::interpretComListRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComListRequest *command = reinterpret_cast<Command::ComListRequest *>(abstractCommand);
    (void)command;
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is asking for contact list." << std::endl;
    ACommand *ret = new Command::ComListResponse(mainCore->getNetworkList()[idClient].second, mainCore->getContactList());
    MainMutex::mutex().unlock();
    return ret;
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
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is setting/changing his name to : " << command->getName();
    std::cout << "." << std::endl;
    mainCore->getContactList()[idClient] = command->getName();
    MainMutex::mutex().unlock();
    return NULL;
}

/* TO IMPLEMENT (not essential) */
ACommand *CommandInterpreter::interpretComCoChange(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCoChange *command = reinterpret_cast<Command::ComCoChange *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is setting his status to : " << command->getStatus();
    std::cout << "." << std::endl;
    MainMutex::mutex().unlock();
    return NULL;
}

ACommand *CommandInterpreter::interpretComCallRequest(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallRequest *command = reinterpret_cast<Command::ComCallRequest *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is calling the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    command->setPeer(mainCore->getNetworkList()[command->getIdFriend()].second);
    command->setIdFriend(idClient);
    MainMutex::mutex().unlock();
    return command;
}

ACommand *CommandInterpreter::interpretComCallCancel(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallCancel *command = reinterpret_cast<Command::ComCallCancel *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is canceling his call to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    command->setPeer(mainCore->getNetworkList()[command->getIdFriend()].second);
    command->setIdFriend(idClient);
    MainMutex::mutex().unlock();
    return command;
}

ACommand *CommandInterpreter::interpretComCallResponse(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComCallResponse *command = reinterpret_cast<Command::ComCallResponse *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is accepting the call to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    command->setPeer(mainCore->getNetworkList()[command->getIdFriend()].second);
    command->setIdFriend(idClient);
    MainMutex::mutex().unlock();
    return command;
}

ACommand *CommandInterpreter::interpretComMessageSend(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComMessageSend *command = reinterpret_cast<Command::ComMessageSend *>(abstractCommand);
    MainMutex::mutex().lock();
    std::cout << "Client " << idClient;
    std::cout << " (" << mainCore->getContactList()[idClient] << ")";
    std::cout << " is sending the message \"" << command->getMessage() << "\"";
    std::cout << " to the client " << command->getIdFriend();
    std::cout << " (" << mainCore->getContactList()[command->getIdFriend()] << ")";
    std::cout << "." << std::endl;
    ACommand *ret = new Command::ComMessageReceive(mainCore->getNetworkList()[command->getIdFriend()].second, idClient, command->getMessage());
    MainMutex::mutex().unlock();
    return ret;
}

/* not used server-side */
ACommand *CommandInterpreter::interpretComMessageReceive(ServerCore *mainCore, ACommand *abstractCommand, unsigned short idClient) {
    Command::ComMessageReceive *command = reinterpret_cast<Command::ComMessageReceive *>(abstractCommand);
    (void)mainCore;
    (void)command;
    (void)idClient;
    return NULL;
}

#else

/* TO IMPLEMENT */
ACommand *CommandInterpreter::interpretComError(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComError *command = reinterpret_cast<Command::ComError *>(abstractCommand);
    MainMutex::mutex().lock();
    (void)mainCore;
    (void)command;
    MainMutex::mutex().unlock();
    return NULL;
}

/* not used client-side */
ACommand *CommandInterpreter::interpretComListRequest(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComListRequest *command = reinterpret_cast<Command::ComListRequest *>(abstractCommand);
    (void)mainCore;
    (void)command;
    return NULL;
}

ACommand *CommandInterpreter::interpretComListResponse(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComListResponse *command = reinterpret_cast<Command::ComListResponse *>(abstractCommand);
    MainMutex::mutex().lock();
    mainCore->setContactList(command->getContactList());
    mainCore->setContactsUpdate(true);
    MainMutex::mutex().unlock();
    return NULL;
}

/* not used client-side */
ACommand *CommandInterpreter::interpretComCoRequest(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComCoRequest *command = reinterpret_cast<Command::ComCoRequest *>(abstractCommand);
    (void)mainCore;
    (void)command;
    return NULL;
}

/* not used client-side */
ACommand *CommandInterpreter::interpretComCoChange(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComCoChange *command = reinterpret_cast<Command::ComCoChange *>(abstractCommand);
    (void)mainCore;
    (void)command;
    return NULL;
}

ACommand *CommandInterpreter::interpretComCallRequest(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComCallRequest *command = reinterpret_cast<Command::ComCallRequest *>(abstractCommand);
    MainMutex::mutex().lock();
    mainCore->getCallingList().push_back(command->getIdFriend());
    mainCore->setCallingUpdate(true);
    MainMutex::mutex().unlock();
    return NULL;
}

ACommand *CommandInterpreter::interpretComCallCancel(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComCallCancel *command = reinterpret_cast<Command::ComCallCancel *>(abstractCommand);
    MainMutex::mutex().lock();
    mainCore->getCancellingList().push_back(command->getIdFriend());
    mainCore->setCancellingUpdate(true);
    MainMutex::mutex().unlock();
    return NULL;
}

ACommand *CommandInterpreter::interpretComCallResponse(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComCallResponse *command = reinterpret_cast<Command::ComCallResponse *>(abstractCommand);
    MainMutex::mutex().lock();
    mainCore->setCallingFriend((short)command->getIdFriend());
    MainMutex::mutex().unlock();
    return NULL;
}

/* not used client-side */
ACommand *CommandInterpreter::interpretComMessageSend(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComMessageSend *command = reinterpret_cast<Command::ComMessageSend *>(abstractCommand);
    (void)mainCore;
    (void)command;
    return NULL;
}

ACommand *CommandInterpreter::interpretComMessageReceive(ClientCore *mainCore, ACommand *abstractCommand) {
    Command::ComMessageReceive *command = reinterpret_cast<Command::ComMessageReceive *>(abstractCommand);
    MainMutex::mutex().lock();
    mainCore->getMessagesList()[command->getIdFriend()].push_back(std::pair<messageType, std::string>(FROM_OTHER, command->getMessage()));
    mainCore->setMessagesUpdate(true);
    MainMutex::mutex().unlock();
    return NULL;
}

#endif