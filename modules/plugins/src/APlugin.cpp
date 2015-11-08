#include <unistd.h>
#include "APlugin.hh"
#include "ImplementationFactory.hpp"
#include "BabelOpus.hh"
#include "Errors.hpp"

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
			sleep(TRY_CONNECT_DELAY);
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

bool APlugin::runThreadIn()
{
	INetwork * peer = this->initPeer(this->_networkMode == APlugin::SERVER ? VOIP_PORT_IN : VOIP_PORT_OUT);

	if (peer == NULL)
		return false;
	this->initInput();
	try
	{
		while (this->_running)
		{
			BabelOpus::EncodePack data;
			peer->read(&data, sizeof(data));
			this->playInput(&data);
		}
	} catch (Error::Module::Network::ReadError & /*e*/) {

	}
	this->destroyInput();
	delete peer;
	return true;
}

bool APlugin::runThreadOut()
{
	INetwork * peer = this->initPeer(this->_networkMode == APlugin::SERVER ? VOIP_PORT_OUT : VOIP_PORT_IN);

	if (peer == NULL)
		return false;
	this->initOutput();
	try
	{
		while (this->_running)
		{
			BabelOpus::EncodePack * data;
			data = static_cast<BabelOpus::EncodePack *>(this->getOutput());
			if (data != NULL)
				peer->write(data, sizeof(*data));
		}
	} catch (Error::Module::Network::WriteError & /*e*/) {
		
	}
	this->destroyOutput();
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