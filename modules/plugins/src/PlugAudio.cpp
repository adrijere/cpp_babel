#include <iostream>
#include <cstdlib>
#include "PlugAudio.hh"

void PlugAudio::runTest() {

  for (int i=0; i < 600; ++i)
    sendData(getData());
}

void *PlugAudio::getData() {
  unsigned char *sample;
  if ((sample = _audio.readOutput()) == NULL)
    return (NULL);
  if (_opus.OpusEncode(sample, 960))
    return static_cast<void *>(_opus.getEnc());
  return NULL;
}

bool PlugAudio::sendData(void *data) {
  BabelOpus::EncodePack *pack = static_cast<BabelOpus::EncodePack *>(data);
  if ( _opus.OpusDecode(pack))
    return _audio.writeInput(_opus.getDec());
  return false;
}

PlugAudio::PlugAudio() : APlugin(AUDIO_ID) {
  // exception, think about it

  // init Audio
  if (!_audio.openStream() || !_audio.startStream(_audio.getInputStream()) || !_audio.startStream(_audio.getOutputStream()))
    std::cerr << "can't initialize stream" << std::endl;

  // init encoder and Decode
  if (!_opus.initEncode() ||  !_opus.initDecode())
    std::cerr << "can't initialize opus" << std::endl;

}

PlugAudio::~PlugAudio() {
  // stop streams
  _audio.stopStream(_audio.getInputStream());
  _audio.stopStream(_audio.getOutputStream());
}
