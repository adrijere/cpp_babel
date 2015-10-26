/*
** Command.hpp for Command in /home/mathon_j/rendu/babel
**
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
**
** Started on  Wed Oct 14 19:56:57 2015 Jérémy MATHON
** Last update Sat Oct 24 13:58:55 2015 Jérémy MATHON
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include "ACommand.hpp"

class Command {
 public:
  class ComError : public ACommand {
   private:
    std::string error;

   public:
    ComError(const std::string &tmp) {
      this->id = 0;
      this->cmd = tmp;
    };
    ~ComError(){};

    void parse();
    void execute(){};
  };

  class ComListRequest : public ACommand {
   public:
    ComListRequest(const std::string &tmp) {
      this->id = 1;
      this->cmd = tmp;
    };
    ~ComListRequest(){};

    void parse();
    void execute(){};
  };

  class ComListResponse : public ACommand {
   private:
    std::list<short> _id_name;
    std::list<std::string> _name;

   public:
    ComListResponse(const std::string &tmp) {
      this->id = 2;
      this->cmd = tmp;
    };
    ~ComListResponse(){};

    void parse();
    void execute(){};
  };

  class ComCoRequest : public ACommand {
   private:
    std::string _name;

   public:
    ComCoRequest(const std::string &tmp) {
      this->id = 3;
      this->cmd = tmp;
    };
    ~ComCoRequest(){};

    void parse();
    void execute(){};
  };

  class ComCoResponse : public ACommand {
   private:
    short _id_name;

   public:
    ComCoResponse(const std::string &tmp) {
      this->id = 4;
      this->cmd = tmp;
    };
    ~ComCoResponse(){};

    void parse();
    void execute(){};
  };

  class Ping : public ACommand {
   private:
    short _id_name;

   public:
    Ping(const std::string &tmp) {
      this->id = 5;
      this->cmd = tmp;
    };
    ~Ping(){};

    void parse();
    void execute(){};
  };

  class ComCoChange : public ACommand {
   private:
    short _id_name;
    char _status;

   public:
    ComCoChange(const std::string &tmp) {
      this->id = 6;
      this->cmd = tmp;
    };
    ~ComCoChange(){};

    void parse();
    void execute(){};
  };

  class ComFriendRequest : public ACommand {
   private:
    short _id_friend;

   public:
    ComFriendRequest(const std::string &tmp) {
      this->id = 7;
      this->cmd = tmp;
    };
    ~ComFriendRequest(){};

    void parse();
    void execute(){};
  };

  class ComFriendResponse : public ACommand {
   private:
    short _id_friend;
    std::string addr;
    short port;

   public:
    ComFriendResponse(const std::string &tmp) {
      this->id = 8;
      this->cmd = tmp;
    };
    ~ComFriendResponse(){};

    void parse();
    void execute(){};
  };

 public:
  static ACommand *parseCommand(const std::string &);
};

#endif /* !COMMAND_HPP_ */
