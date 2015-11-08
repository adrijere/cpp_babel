#include <iostream>
#include <cstdlib>
#include "PlugAudio.hh"

/*
bool PlugAudio::initThreadIn()
{
  this->_socketIn = this->_server->waitConnection();
  return true;
}

bool PlugAudio::initThreadOut()
{
  IClient * clientOut = ImplementationFactory::createUDPClient();
  clientOut->connect()
  this->_socketOut = clientOut;
  return true;
}

bool PlugAudio::destroyThreadIn()
{
  return true;
}

bool PlugAudio::destroyThreadOut()
{
  return true;
}

bool PlugAudio::runThreadIn()
{
  std::cout << "[IN]" << std::endl;
  sleep(1);
  return true;
}

bool PlugAudio::runThreadOut()
{
  std::cout << "[OUT]" << std::endl;
  sleep(1);
  return true;
}
*/

bool PlugAudio::playInput(void *data) {
  /*
  BabelOpus::EncodePack *pack = static_cast<BabelOpus::EncodePack *>(data);
  if ( _opus.OpusDecode(pack))
    return _audio.writeInput(_opus.getDec());
  return false;
  */
  (void)data;
  return true;
}

void *PlugAudio::getOutput() {
  /*
  unsigned char *sample;
  if ((sample = _audio.readOutput()) == NULL)
    return (NULL);
  if (_opus.OpusEncode(sample, 960))
    return static_cast<void *>(_opus.getEnc());
  */
  return NULL;
}

PlugAudio::PlugAudio() : APlugin(APlugin::AUDIO_ID) {
  /*
  // exception, think about it

  // init Audio
  if (!_audio.openStream() || !_audio.startStream(_audio.getInputStream()) || !_audio.startStream(_audio.getOutputStream()))
    std::cerr << "can't initialize stream" << std::endl;

  // init encoder and Decode
  if (!_opus.initEncode() ||  !_opus.initDecode())
    std::cerr << "can't initialize opus" << std::endl;
  */
}

PlugAudio::~PlugAudio() {
  // stop streams
  /*
  _audio.stopStream(_audio.getInputStream());
  _audio.stopStream(_audio.getOutputStream());
  */
}
