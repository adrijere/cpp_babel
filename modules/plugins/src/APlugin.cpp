#include "APlugin.hh"
#include "ImplementationFactory.hpp"

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

		int try_connect = 0;
		while (try_connect < NB_TRY_CONNECT)
		{
			if (client->connect(this->_address, port) == true)
				break ;
			try_connect++;
		}
		if (try_connect == NB_TRY_CONNECT)
		{
			delete client;
			return NULL;
		}
		peer = client;
	}
	return peer;
}

#include <unistd.h>
#include <iostream>

bool APlugin::runThreadIn()
{
	INetwork * peer = this->initPeer(VOIP_PORT_IN);

	if (peer == NULL)
		return false;
	while (this->_running)
	{
		int nb = 0;
		peer->read(&nb, sizeof(nb));
		std::cout << nb << std::endl;
	}
	delete peer;
	return true;
}

bool APlugin::runThreadOut()
{
	INetwork * peer = this->initPeer(VOIP_PORT_OUT);

	if (peer == NULL)
		return false;
	while (this->_running)
	{
		int nb = 3;
		peer->write(&nb, sizeof(nb));
		sleep(1);
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