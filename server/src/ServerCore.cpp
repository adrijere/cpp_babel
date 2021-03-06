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
    this->_connectionsListenerIn = ImplementationFactory::createTCPServer();
    this->_connectionsListenerOut = ImplementationFactory::createTCPServer();

    this->_interpreter[COM_ERROR_ID] = CommandInterpreter::interpretComError;
    this->_interpreter[COM_LIST_REQUEST_ID] = CommandInterpreter::interpretComListRequest;
    this->_interpreter[COM_LIST_RESPONSE_ID] = CommandInterpreter::interpretComListResponse;
    this->_interpreter[COM_CO_REQUEST_ID] = CommandInterpreter::interpretComCoRequest;
    this->_interpreter[COM_CO_CHANGE_ID] = CommandInterpreter::interpretComCoChange;
    this->_interpreter[COM_CALL_REQUEST_ID] = CommandInterpreter::interpretComCallRequest;
    this->_interpreter[COM_CALL_CANCEL_ID] = CommandInterpreter::interpretComCallCancel;
    this->_interpreter[COM_CALL_RESPONSE_ID] = CommandInterpreter::interpretComCallResponse;
    this->_interpreter[COM_MESSAGE_SEND_ID] = CommandInterpreter::interpretComMessageSend;
    this->_interpreter[COM_MESSAGE_RECEIVE_ID] = CommandInterpreter::interpretComMessageReceive;
}

ServerCore::~ServerCore() { }

void ServerCore::run() {
    this->_connectionsListenerIn->listen(SERVER_PORT_IN);
    this->_connectionsListenerOut->listen(SERVER_PORT_OUT);
    INetwork *peerIn = this->_connectionsListenerIn->waitConnection();
    INetwork *peerOut = this->_connectionsListenerOut->waitConnection();
    int idClients = 1;
    while(peerIn != NULL && peerOut != NULL) {
        this->_networkList[idClients] = std::pair<INetwork *, INetwork *>(peerIn, peerOut);
        this->_threadList[idClients] = new std::thread(&ServerCore::connection, this, idClients);
        idClients++;
        peerIn = this->_connectionsListenerIn->waitConnection();
        peerOut = this->_connectionsListenerOut->waitConnection();
    }
}

void ServerCore::connection(unsigned short idClient) {
    try {
        std::cout << "New Connection !" << std::endl;
        ACommand *newCommand = Command::parseCommand(this->_networkList[idClient].first);
        while (newCommand != NULL) {
            ACommand *responseCommand = this->_interpreter[newCommand->getId()](this, newCommand, idClient);
            if (responseCommand) {
                responseCommand->write();
                delete responseCommand;
            }
//            delete newCommand;
            newCommand = Command::parseCommand(this->_networkList[idClient].first);
        }
        std::cout << "Fin de Connection !" << std::endl;
    } catch(const Error &e) {
        std::cout << "[Error occurred] (" << e.where() << ") " << e.what() << std::endl;
    }
    this->_contactList.erase(this->_contactList.find(idClient));
    this->_networkList.erase(this->_networkList.find(idClient));
    this->_threadList.erase(this->_threadList.find(idClient));
}
