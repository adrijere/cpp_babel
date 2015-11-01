/*
** Command.cpp for Command in /home/mathon_j/rendu/babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
**
** Started on  Wed Oct 14 19:57:32 2015 Jérémy MATHON
** Last update Sat Oct 24 14:10:41 2015 Jérémy MATHON
*/

#include "Command.hpp"

void Command::ComError::parse() {
  CommandManager os;
  unsigned short _nb;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&_nb);
  for (unsigned int index = 0; index < _nb; ++index) {
    char letter;
    os.read(&letter);
    this->_error += letter;
  }
}
void Command::ComError::write() {
  unsigned int size = 2 + (unsigned int)this->_error.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeString(this->_error);
}

void Command::ComListRequest::parse() {
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_name);
}
void Command::ComListRequest::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::ComListResponse::parse() {
  unsigned short _id_contact;
  unsigned short _size;
  CommandManager os;
  std::string tmp;
  std::string tmp2;

  tmp = this->_cmd;
  os << tmp;
  while (os.read(&_id_contact)) {
    os.read(&_size);
    for (unsigned int index = 0; index < _size; ++index) {
      char letter;
      os.read(&letter);
      tmp2 += letter;
    }
    this->_contactList[_id_contact] = tmp2;
    tmp2 = "";
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

void Command::ComCoRequest::parse() {
  unsigned short _nb;
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&_nb);
  for (unsigned int index = 0; index < _nb; ++index) {
    char letter;
    os.read(&letter);
    this->_name += letter;
  }
}
void Command::ComCoRequest::write() {
  unsigned int size = 2 + (unsigned int)this->_name.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeString(this->_name);
}

void Command::ComCoResponse::parse() {
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_name);
}
void Command::ComCoResponse::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::Ping::parse() {
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_name);
}
void Command::Ping::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
}

void Command::ComCoChange::parse() {
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_name);
  os.read(&this->_status);
}
void Command::ComCoChange::write() {
  unsigned int size = 3;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_name);
  this->writeChar(this->_status);
}

void Command::ComFriendRequest::parse() {
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_friend);
}
void Command::ComFriendRequest::write() {
  unsigned int size = 2;

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
}

void Command::ComFriendResponse::parse() {
  unsigned short _nb;
  CommandManager os;
  std::string tmp;

  tmp = this->_cmd;
  os << tmp;
  os.read(&this->_id_friend);
  os.read(&_nb);
  for (unsigned int index = 0; index < _nb; ++index) {
    char letter;
    os.read(&letter);
    this->_addr += letter;
  }
  os.read(&this->_port);
}
void Command::ComFriendResponse::write() {
  unsigned int size = 6 + (unsigned int)this->_addr.size();

  this->writeChar(this->_id);
  this->writeInt(size);
  this->writeShort(this->_id_friend);
  this->writeString(this->_addr);
  this->writeShort(this->_port);
}

static ACommand *parseCommand(INetwork *peer) {
  char id;
  unsigned int size;
  ACommand *cmd;

  peer->read(&id, 1);
  peer->read(&size, 4);
  char tmp[size];
  peer->read(tmp, size);
  switch (id)
  {
    case 0: {
      cmd = new Command::ComError(tmp);
      break;
    }
    case 1: {
      cmd = new Command::ComListRequest(tmp);
      break;
    }
    case 2: {
      cmd = new Command::ComListResponse(tmp);
      break;
    }
    case 3: {
      cmd = new Command::ComCoRequest(tmp);
      break;
    }
    case 4: {
      cmd = new Command::ComCoResponse(tmp);
      break;
    }
    case 5: {
      cmd = new Command::Ping(tmp);
      break;
    }
    case 6: {
      cmd = new Command::ComCoChange(tmp);
      break;
    }
    case 7: {
      cmd = new Command::ComFriendRequest(tmp);
      break;
    }
    case 8: {
      cmd = new Command::ComFriendResponse(tmp);
      break;
    }
    default: {
      cmd = new Command::ComError("");
      break;
    }
  }
  cmd->parse();
  return (cmd);
}
