/*
** ACommand.hpp for ACommand in /home/mathon_j/rendu/babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
**
** Started on  Wed Oct 14 19:56:38 2015 Jérémy MATHON
** Last update Sat Oct 24 13:34:07 2015 Jérémy MATHON
*/

#ifndef ACOMMAND_HPP_
# define ACOMMAND_HPP_

# include	<iostream>
# include	<string>
# include	<cstring>
# include	<sstream>
# include	<map>
# include	<list>
# include   "INetwork.hpp"

class ACommand : public std::stringstream {
protected:
    unsigned char	_id;
    unsigned int    _size;
    INetwork        *_peer;

public:
    ACommand(){
        this->_id = 255;
        this->_size = 0;
        this->_peer = NULL;
    };
    virtual ~ACommand(){};

    unsigned char getId() { return this->_id; }
    unsigned int getSize() { return this->_size; }
    INetwork *getPeer() { return this->_peer; }

    virtual void parse(INetwork *) = 0;
    virtual void write() = 0;

    void writeString(std::string);
    void writeInt(unsigned int);
    void writeShort(unsigned short);
    void writeChar(unsigned char);

    void readString(std::string &);
    void readInt(unsigned int *);
    void readShort(unsigned short *);
    void readChar(unsigned char *);
};

#endif /* !ACOMMAND_HPP_ */
