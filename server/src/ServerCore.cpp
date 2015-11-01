//
// ServerCore.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#include "ServerCore.hpp"

ServerCore::ServerCore() {
    this->_connectionsListener = ImplementationFactory::createTCPServer();

    this->_interpreter[0] = CommandInterpreter::interpretComError;
    this->_interpreter[1] = CommandInterpreter::interpretComListRequest;
    this->_interpreter[2] = CommandInterpreter::interpretComListResponse;
    this->_interpreter[3] = CommandInterpreter::interpretComCoRequest;
    this->_interpreter[4] = CommandInterpreter::interpretComCoResponse;
    this->_interpreter[5] = CommandInterpreter::interpretPing;
    this->_interpreter[6] = CommandInterpreter::interpretComCoChange;
    this->_interpreter[7] = CommandInterpreter::interpretComFriendRequest;
    this->_interpreter[8] = CommandInterpreter::interpretComFriendResponse;
}

ServerCore::~ServerCore() { }

void ServerCore::run() {
    this->_connectionsListener->listen(4243);
    INetwork *peer = this->_connectionsListener->waitConnection();
    while(peer != NULL) {
        this->_networkList.push_back(peer);
        std::thread *newThread = new std::thread(&ServerCore::connection, this, this->_networkList.size() - 1);
        this->_threadList.push_back(newThread);
        peer = this->_connectionsListener->waitConnection();
    }
}

void ServerCore::connection(unsigned short idClient) {
    std::cout << "New Connection !" << std::endl;
    ACommand *newCommand = Command::parseCommand(this->_networkList[idClient]);
    while (newCommand != NULL) {
        ACommand *responseCommand = this->_interpreter[newCommand->getId()](this, newCommand, idClient);
        if (responseCommand)
            responseCommand->write();
        newCommand = Command::parseCommand(this->_networkList[idClient]);
    }
    std::cout << "Fin de Connection !" << std::endl;
}
