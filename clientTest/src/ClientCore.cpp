//
// ClientCore.cpp for babel in /home/loir_j/rendu/cpp_babel/server/inc
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:45 2015 Julien Loir
// Last update Mon Oct  26 00:15:45 2015 Julien Loir
//

#include "ClientCore.hpp"

ClientCore::ClientCore(const std::string &name, const std::string &addr, unsigned short port) {
    this->_name = name;
    this->_mainConnection = ImplementationFactory::createTCPClient();
    this->_mainConnection->connect(addr, port);

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

    this->_readerThread = new std::thread(&ClientCore::reader, this);
}

void ClientCore::reader() {
    ACommand *newCommand = Command::parseCommand(this->_mainConnection);
    while (newCommand != NULL) {
        ACommand *responseCommand = this->_interpreter[newCommand->getId()](this, newCommand);
        if (responseCommand) {
            responseCommand->write();
            delete responseCommand;
        }
        delete newCommand;
        newCommand = Command::parseCommand(this->_mainConnection);
    }
}

void ClientCore::sendComListRequest() {

}

void ClientCore::sendComCoRequest() {

}

void ClientCore::sendComCoChange(unsigned char status) {
    (void)status;
}

void ClientCore::sendComCallRequest(unsigned short idFriend) {
    (void)idFriend;
}

void ClientCore::sendComCallCancel(unsigned short idFriend) {
    (void)idFriend;
}

void ClientCore::sendComMessageSend(unsigned short idFriend, const std::string &message) {
    (void)idFriend;
}
