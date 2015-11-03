//
// ACommand.cpp for babel in /home/loir_j/rendu/cpp_babel/server/src
//
// Made by Julien Loir
// Login   <loir_j@epitech.eu>
//
// Started on  Mon Oct  26 00:15:51 2015 Julien Loir
// Last update Mon Oct  26 00:15:51 2015 Julien Loir
//

#include "ACommand.hpp"

void ACommand::writeString(std::string elem) {
    this->writeShort((unsigned short)elem.size());
    this->_peer->write(elem.c_str(), elem.size());
}

void ACommand::writeInt(unsigned int elem) {
    this->_peer->write(&elem, 4);
}

void ACommand::writeShort(unsigned short elem) {
    this->_peer->write(&elem, 2);
}

void ACommand::writeChar(unsigned char elem) {
    this->_peer->write(&elem, 1);
}

void ACommand::readString(std::string &elem) {
    unsigned short stringSize = 0;
    this->readShort(&stringSize);
    char *tmp = new char[stringSize + 1];
    tmp[stringSize] = 0;
    this->_peer->read(tmp, stringSize);
    elem = tmp;
}

void ACommand::readInt(unsigned int *elem) {
    this->_peer->read(elem, 4);
}

void ACommand::readShort(unsigned short *elem) {
    this->_peer->read(elem, 2);
}

void ACommand::readChar(unsigned char *elem) {
    this->_peer->read(elem, 1);
}

