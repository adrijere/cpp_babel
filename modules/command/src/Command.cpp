//
// Command.cpp for Command in /home/mathon_j/rendu/babel
//
// Made by Jérémy MATHON
// Login   <mathon_j@mathonj>
//
// Started on  Wed Oct 14 19:57:32 2015 Jérémy MATHON
// Last update Sat Oct 24 14:10:41 2015 Jérémy MATHON
//

#include "Command.hpp"

void Command::ComError::parse(INetwork *peer) {
  this->_peer = peer;
  this->readString(this->_error);
}
void Command::ComError::write() {
  unsigned int size = 2 + (unsigned int)this->_error.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeString(this->_error);
}

void Command::ComListRequest::parse(INetwork *peer) {
  this->_peer = peer;
}
void Command::ComListRequest::write() {
  unsigned int size = 0;

  this->writeChar(this->_id);
  this->writeInt(size);
}

void Command::ComListResponse::parse(INetwork *peer) {
  this->_peer = peer;
  unsigned int currSize = 0;
  while (currSize < this->_size) {
    unsigned short idName;
    std::string stringData;
    this->readShort(&idName);
    this->readString(stringData);
//    currSize += 4 + stringData.size();
    this->_size -= (4 + stringData.size()); // ca c'est moche
    this->_contactList[idName] = stringData;
  }
}
void Command::ComListResponse::write() {
  unsigned int size = 0;

  for (std::map<unsigned short, std::string>::iterator it = this->_contactList.begin(); it != this->_contactList.end(); ++it) {
    size += 4 + (*it).second.size();
  }
  this->writeChar(this->_id);
  this->writeInt(size);
  for (std::map<unsigned short, std::string>::iterator it = this->_contactList.begin(); it != this->_contactList.end(); ++it) {
    this->writeShort((*it).first);
    this->writeString((*it).second);
  }
}

void Command::ComCoRequest::parse(INetwork *peer) {
  this->_peer = peer;
  this->readString(this->_name);
}
void Command::ComCoRequest::write() {
  unsigned int size = 2 + (unsigned int)this->_name.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeString(this->_name);
}

void Command::ComCoChange::parse(INetwork *peer) {
  this->_peer = peer;
  this->readChar(&this->_status);
}
void Command::ComCoChange::write() {
  unsigned int size = 1;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeChar(this->_status);
}

void Command::ComCallRequest::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(&this->_id_friend);
  this->readString(this->_addr);
}
void Command::ComCallRequest::write() {
  unsigned int size = 4 + (unsigned int)this->_addr.size(); // a la base c'etait 2

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_addr);
}

void Command::ComCallCancel::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(&this->_id_friend);
}
void Command::ComCallCancel::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
}

void Command::ComCallResponse::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(&this->_id_friend);
  this->readString(this->_addr);
}
void Command::ComCallResponse::write() {
  unsigned int size = 4 + (unsigned int)this->_addr.size(); // a la base c'etait 6 + ...

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_addr);
}

void Command::ComMessageSend::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(&this->_id_friend);
  this->readString(this->_message);
}
void Command::ComMessageSend::write() {
  unsigned int size = 2 + (unsigned int)this->_message.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_message);
}

void Command::ComMessageReceive::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(&this->_id_friend);
  this->readString(this->_message);
}
void Command::ComMessageReceive::write() {
  unsigned int size = 2 + (unsigned int)this->_message.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_message);
}

ACommand *Command::parseCommand(INetwork *peer) {
  unsigned char id;
  unsigned int size;
  ACommand *cmd;

  peer->read(&id, 1);
  peer->read(&size, 4);
  switch (id)
  {
    case COM_ERROR_ID: {
      cmd = new Command::ComError(size);
      break;
    }
    case COM_LIST_REQUEST_ID: {
      cmd = new Command::ComListRequest(size);
      break;
    }
    case COM_LIST_RESPONSE_ID: {
      cmd = new Command::ComListResponse(size);
      break;
    }
    case COM_CO_REQUEST_ID: {
      cmd = new Command::ComCoRequest(size);
      break;
    }
    case COM_CO_CHANGE_ID: {
      cmd = new Command::ComCoChange(size);
      break;
    }
    case COM_CALL_REQUEST_ID: {
      cmd = new Command::ComCallRequest(size);
      break;
    }
    case COM_CALL_CANCEL_ID: {
      cmd = new Command::ComCallCancel(size);
      break;
    }
    case COM_CALL_RESPONSE_ID: {
      cmd = new Command::ComCallResponse(size);
      break;
    }
    case COM_MESSAGE_SEND_ID: {
      cmd = new Command::ComMessageSend(size);
      break;
    }
    case COM_MESSAGE_RECEIVE_ID: {
      cmd = new Command::ComMessageReceive(size);
      break;
    }
    default: {
      return (NULL);
    }
  }
  cmd->parse(peer);
  return (cmd);
}
