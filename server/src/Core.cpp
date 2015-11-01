//
// Core.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#include "Core.hpp"

Core::Core() {
    this->_connectionsListener = ImplementationFactory::createTCPServer();
}

Core::~Core() { }

void Core::run() {
    this->_connectionsListener->listen(4243);
    INetwork *peer = this->_connectionsListener->waitConnection();
    while(peer != NULL) {
        std::thread *newThread = new std::thread(Core::connection, peer, &this->_contactList, &this->_mainMutex);
        this->_threadList.push_back(newThread);
        peer = this->_connectionsListener->waitConnection();
    }
}

void Core::connection(INetwork *peer, std::map<unsigned short, std::string> *contactList, std::mutex *mainMutex) {
    std::cout << "New Connection !" << std::endl;
    ACommand *newCommand = Command::parseCommand(peer);
    while (newCommand != NULL) {
        std::cout << newCommand->_id << std::endl;
        newCommand = Command::parseCommand(peer);
    }
    std::cout << "Fin de Connection !" << std::endl;
}
