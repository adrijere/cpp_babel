/*
** Command.cpp for Command in /home/mathon_j/rendu/babel
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Oct 14 19:57:32 2015 Jérémy MATHON
** Last update Sat Oct 24 14:10:41 2015 Jérémy MATHON
*/

#include	"Command.hpp"
#include	"CommandManager.hpp"

void				Command::ComError::parse()
{
  CommandManager		os;
  short				_nb;
  std::string			tmp;

  tmp = this->cmd;
  os << tmp;
  os.read(&_nb);
  for (size_t index = 0; index < _nb; ++index)
    {
      char letter;
      os.read(&letter);
      this->error += letter;
    }
}

void				Command::ComListRequest::parse()
{

}

void				Command::ComListResponse::parse()
{
  short				_nb;
  CommandManager		os;
  std::string			tmp;
  std::string			tmp2;

  tmp = this->cmd;
  os << tmp;
  while (os.read(&_nb))
    {
      this->_id_name.push_back(_nb);
      os.read(&_nb);
      for (size_t index = 0; index < _nb; ++index)
	{
	  char letter;
	  os.read(&letter);
	  tmp2 += letter;
	}
      this->_name.push_back(tmp2);
      tmp2 = "";
    }
}

void				Command::ComCoRequest::parse()
{
  short				_nb;
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&_nb);
  for (size_t index = 0; index < _nb; ++index)
    {
      char letter;
      os.read(&letter);
      this->_name += letter;
    }
}

void				Command::ComCoResponse::parse()
{
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&this->_id_name);
}

void				Command::Ping::parse()
{
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&this->_id_name);
}

void				Command::ComCoChange::parse()
{
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&this->_id_name);
  os.read(&this->_status);
}

void				Command::ComFriendRequest::parse()
{
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&this->_id_friend);
}

void				Command::ComFriendResponse::parse()
{
  short				_nb;
  CommandManager		os;
  std::string			tmp;

  tmp =  this->cmd;
  os << tmp;
  os.read(&this->_id_friend);
  os.read(&_nb);
  for (size_t index = 0; index < _nb; ++index)
    {
      char letter;
      os.read(&letter);
      this->addr += letter;
    }
  os.read(&this->port);
}

std::map<char, ACommand*>	createMap(std::map<char, ACommand*> map, const std::string &tmp)
{
  map[0] = new Command::ComError(tmp);
  map[1] = new Command::ComListRequest(tmp);
  map[2] = new Command::ComListResponse(tmp);
  map[3] = new Command::ComCoRequest(tmp);
  map[4] = new Command::ComCoResponse(tmp);
  map[5] = new Command::Ping(tmp);
  map[6] = new Command::ComCoChange(tmp);
  map[7] = new Command::ComFriendRequest(tmp);
  map[8] = new Command::ComFriendResponse(tmp);
  return (map);
}

static	ACommand		*parseCommand(const std::string &tmp)
{
  CommandManager		os;
  std::map<char, ACommand *>	map;
  char				_id;
  ACommand			*cmd;
  std::string			_tmp;

  os << tmp;
  os.read(&_id);
  os.str("");
  os.str(tmp);
  _tmp = os.str();
  _tmp.erase(0,1);
  map = createMap(map, _tmp);
  cmd = map[_id];
  cmd->parse();
  return (cmd);
}
