#include <iostream>
#include <cstdlib>
#include "PlugAudio.hh"

bool PlugAudio::playInput(void *data) {
  BabelOpus::EncodePack *pack = static_cast<BabelOpus::EncodePack *>(data);
  if ( _opus.OpusDecode(pack))
    return _audio.writeInput(_opus.getDec());
  return false;
}

void *PlugAudio::getOutput() {
  unsigned char *sample;
  if ((sample = _audio.readOutput()) == NULL)
    return (NULL);
  if (_opus.OpusEncode(sample, 960))
    return static_cast<void *>(_opus.getEnc());
}

void PlugAudio::init()
{
  // exception, think about it

  // init Audio
  if (!_audio.startStream(_audio.getInputStream()) || !_audio.startStream(_audio.getOutputStream()))
    std::cerr << "can't initialize stream" << std::endl;

  // init encoder and Decode
  if (!_opus.initEncode() ||  !_opus.initDecode())
    std::cerr << "can't initialize opus" << std::endl;
}

void PlugAudio::destroy()
{
  // stop streams
  _audio.stopStream(_audio.getInputStream());
  _audio.stopStream(_audio.getOutputStream());
}

PlugAudio::PlugAudio() : APlugin(APlugin::AUDIO_ID) {
  // init Audio
  if (!_audio.openStream())
    std::cerr << "can't initialize stream" << std::endl;

  // init encoder and Decode
  if (!_opus.initEncode() ||  !_opus.initDecode())
    std::cerr << "can't initialize opus" << std::endl;
}

PlugAudio::~PlugAudio() {

}
