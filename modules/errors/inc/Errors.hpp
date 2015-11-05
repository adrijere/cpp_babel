//
// Errors.hpp for babel in /home/nlequain/projets/tek3/cpp_avance/cpp_babel/modules/errors/inc
//
// Made by Nicolas Lequain
// Login   <nlequain@epitech.eu>
//
// Started on  Wed Nov 04 18:47:08 2015 Nicolas Lequain
// Last update Wed Nov 04 18:47:08 2015 Nicolas Lequain
//

#ifndef ERRORS_H_
# define ERRORS_H_

# include <string>

/*
** Macro de definition d'erreurs
** - ParentClass : la classe mère
** - ClassName : la classe d'erreur
** - Location : string affichée lors d'un appel à la fonction where()
** - Message : string affichée lors d'un appel à la fonction what()
*/

# define DEFINE_ERROR(ParentClass, ClassName, Location, Message)	\
class ParentClass::ClassName : public ParentClass					\
{																	\
public:																\
	ClassName() : ParentClass(Location, Message) {};				\
	virtual ~ClassName() {};										\
};

/*
** Error
*/

class Error
{
protected:
	static const std::string _separator;

private:
	std::string _location;
	std::string _message;

protected:
	Error(const std::string & location, const std::string & message);

public:
	virtual ~Error();
	const std::string & what() const;
	const std::string & where() const;

public:
	class Client;
	class Server;
	class Module;
};

/*
** Client
*/

class Error::Client : public Error
{
protected:
	Client(const std::string & location, const std::string & message);
public:
	virtual ~Client();
public:
	/* Client Errors */
};

/*
** Server
*/

class Error::Server : public Error
{
protected:
	Server(const std::string & location, const std::string & message);
public:
	virtual ~Server();
public:
	/* Server Errors */
};

/*
** Module
*/

class Error::Module : public Error
{
protected:
	Module(const std::string & location, const std::string & message);
public:
	virtual ~Module();
public:
	class Command;
	class Implementation;
	class Network;
};

/*
** Module : Command
*/

class Error::Module::Command : public Error::Module
{
protected:
	Command(const std::string & location, const std::string & message);
public:
	virtual ~Command();
public:
	/* Command Errors */
};

/*
** Module : Implementation
*/

class Error::Module::Implementation : public Error::Module
{
protected:
	Implementation(const std::string & location, const std::string & message);
public:
	virtual ~Implementation();
public:
	/* Implementation Errors */
};

/*
** Module : Network
*/

class Error::Module::Network : public Error::Module
{
protected:
	Network(const std::string & location, const std::string & message);
public:
	virtual ~Network();
public:
	class ReadError;
	class WriteError;
};

DEFINE_ERROR(Error::Module::Network, ReadError, "read", "Error while reading the socket");
DEFINE_ERROR(Error::Module::Network, WriteError, "write", "Error while writing on the socket");

/*
**
** /!\ Supprimer ce commentaire si l'utilisation de la macro est adoptée, sinon, /!\
** /!\ supprimer les macros ci-dessus et décommenter le code suivant.              /!\
**
** La macro ci-dessus (ReadError) remplace le code suivant :
**
** class Error::Module::Network::ReadError : public Error::Module::Network
** {
** public:
** 	ReadError() : Error::Module::Network("read", "Error while reading the socket") {};
** 	virtual ~ReadError() {};
** };
**
*/

#endif /* ERRORS_H_ */