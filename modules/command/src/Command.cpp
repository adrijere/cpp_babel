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
  this->readShort(this->_id_name);
}
void Command::ComListRequest::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::ComListResponse::parse(INetwork *peer) {
  this->_peer = peer;
  unsigned int currSize = 0;
  while (currSize < this->_size) {
    unsigned short idName;
    std::string stringData;
    this->readShort(idName);
    this->readString(stringData);
    currSize += 2 + stringData.size();
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

void Command::ComCoResponse::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(this->_id_name);
}
void Command::ComCoResponse::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::Ping::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(this->_id_name);
}
void Command::Ping::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::ComCoChange::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(this->_id_name);
  this->readChar(this->_status);
}
void Command::ComCoChange::write() {
  unsigned int size = 3;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
  this->writeChar(this->_status);
}

void Command::ComFriendRequest::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(this->_id_friend);
}
void Command::ComFriendRequest::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
}

void Command::ComFriendResponse::parse(INetwork *peer) {
  this->_peer = peer;
  this->readShort(this->_id_friend);
  this->readString(this->_addr);
  this->readShort(this->_port);
}
void Command::ComFriendResponse::write() {
  unsigned int size = 6 + (unsigned int)this->_addr.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_addr);
  this->writeShort(this->_port);
}

ACommand *Command::parseCommand(INetwork *peer) {
  unsigned char id;
  unsigned int size;
  ACommand *cmd;

  peer->read(&id, 1);
  peer->read(&size, 4);
  switch (id)
  {
    case 0: {
      cmd = new Command::ComError(size);
      break;
    }
    case 1: {
      cmd = new Command::ComListRequest(size);
      break;
    }
    case 2: {
      cmd = new Command::ComListResponse(size);
      break;
    }
    case 3: {
      cmd = new Command::ComCoRequest(size);
      break;
    }
    case 4: {
      cmd = new Command::ComCoResponse(size);
      break;
    }
    case 5: {
      cmd = new Command::Ping(size);
      break;
    }
    case 6: {
      cmd = new Command::ComCoChange(size);
      break;
    }
    case 7: {
      cmd = new Command::ComFriendRequest(size);
      break;
    }
    case 8: {
      cmd = new Command::ComFriendResponse(size);
      break;
    }
    default: {
      return (NULL);
    }
  }
  cmd->parse(peer);
  return (cmd);
}
