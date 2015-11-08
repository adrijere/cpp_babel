#include "APlugin.hh"
#include "ImplementationFactory.hpp"

/*
	INetwork * _socketIn;
	INetwork * _socketOut;
	IServer * _server;
	std::string & _addr;
*/

INetwork * APlugin::initPeer(short port)
{
	INetwork * peer;

	if (this->_networkMode == APlugin::SERVER)
	{
		IServer * server = ImplementationFactory::createUDPServer();
		server->listen(port);
		peer = server->waitConnection();
		delete server;
	}
	else
	{
		IClient * client = ImplementationFactory::createUDPClient();
		client->connect(this->_address, port);
		peer = client;
	}
	return peer;
}

bool APlugin::runThreadIn()
{
	INetwork * peer = this->initPeer(VOIP_PORT_IN);

	while (this->_running)
	{
		
	}
	delete peer;
	return true;
}

bool APlugin::runThreadOut()
{
	INetwork * peer = this->initPeer(VOIP_PORT_OUT);

	while (this->_running)
	{
		
	}
	delete peer;
	return true;
}

bool APlugin::run(const std::string & address, APlugin::NetworkMode mode) {
	this->_address = address;
	this->_networkMode = mode;
	this->_running = true;
	this->_threadIn = new std::thread(&APlugin::runThreadIn, this);
	this->_threadOut = new std::thread(&APlugin::runThreadOut, this);
	return true;
}

bool APlugin::stop() {
	if (this->_running == false)
		return false;
	this->_running = false;
	this->_threadIn->join();
	this->_threadOut->join();
	delete this->_threadIn;
	delete this->_threadOut;
	return true;
}