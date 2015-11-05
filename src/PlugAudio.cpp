#include <iostream>
#include <cstdlib>
#include "PlugAudio.hh"

void PlugAudio::runTest() {
  for (int i=0; i < 600; ++i)
    sendData(getData(), (960));
}

unsigned char *PlugAudio::getData() {
  unsigned char *sample;
  if ((sample = _audio.readOutput()) == NULL)
    return (NULL);
  return _opus.OpusEncode(sample, 960);
}

bool PlugAudio::sendData(unsigned char *buff, unsigned int size) {
  unsigned char *sample;
  if ((sample = _opus.OpusDecode(buff, size)) == NULL)
    return false;
  return _audio.writeInput(sample);
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
