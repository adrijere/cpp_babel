#include "APlugin.hh"

bool APlugin::runThreadIn_wrapper()
{
	while (this->_running)
	{
		if (this->runThreadIn() == false)
			return false;
	}
	return true;
}

bool APlugin::runThreadOut_wrapper()
{
	while (this->_running)
	{
		if (this->runThreadOut() == false)
			return false;
	}
	return true;
}

bool APlugin::run() {
	this->_running = true;
	this->_threadIn = new std::thread(&APlugin::runThreadIn_wrapper, this);
	this->_threadOut = new std::thread(&APlugin::runThreadOut_wrapper, this);
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