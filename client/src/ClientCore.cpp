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

ClientCore::ClientCore(const std::string &name, const std::string &addr) {
    this->_name = name;
    this->_mainConnectionOut = ImplementationFactory::createTCPClient();
    this->_mainConnectionOut->connect(addr, CLIENT_PORT_OUT);
    this->_mainConnectionIn = ImplementationFactory::createTCPClient();
    this->_mainConnectionIn->connect(addr, CLIENT_PORT_IN);

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

    this->_contactsUpdate = false;
    this->_callingUpdate = false;
    this->_cancellingUpdate = false;
    this->_messagesUpdate = false;
    this->_callingFriend = -1;

    this->_readerThread = new std::thread(&ClientCore::reader, this);
}

void ClientCore::reader() {
    try {
        ACommand *newCommand = Command::parseCommand(this->_mainConnectionIn);
        while (newCommand != NULL) {
            ACommand *responseCommand = this->_interpreter[newCommand->getId()](this, newCommand);
            if (responseCommand) {
                responseCommand->write();
                delete responseCommand;
            }
            delete newCommand;
            newCommand = Command::parseCommand(this->_mainConnectionIn);
        }
    } catch(const Error &e) {
        std::cout << "[Error occurred] (" << e.where() << ") " << e.what() << std::endl;
        std::exit(0);
    }
}

void ClientCore::sendComListRequest() {
    Command::ComListRequest command(this->_mainConnectionOut);
    command.write();
}

void ClientCore::sendComCoRequest() {
    Command::ComCoRequest command(this->_mainConnectionOut, this->_name);
    command.write();
}

void ClientCore::sendComCoChange(unsigned char status) {
    Command::ComCoChange command(this->_mainConnectionOut, status);
    command.write();
}

void ClientCore::sendComCallRequest(unsigned short idFriend) {
    Command::ComCallRequest command(this->_mainConnectionOut, idFriend);
    command.write();
}

void ClientCore::sendComCallCancel(unsigned short idFriend) {
    Command::ComCallCancel command(this->_mainConnectionOut, idFriend);
    command.write();
}

void ClientCore::sendComMessageSend(unsigned short idFriend, const std::string &message) {
    Command::ComMessageSend command(this->_mainConnectionOut, idFriend, message);
    command.write();
}

void ClientCore::sendComCallResponse(unsigned short idFriend, const std::string &addr) {
    Command::ComCallResponse command(this->_mainConnectionOut, idFriend, addr);
    command.write();
}
