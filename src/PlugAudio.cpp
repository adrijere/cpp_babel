#include <cstdlib>
#include "PlugAudio.hh"

void PlugAudio::runTest() {
    sendData(getData(), (1024));
}

unsigned char *PlugAudio::getData() {
  unsigned char *sample;
  if ((sample = _audio.readOutput()) == NULL)
    return (NULL);
  return _opus.OpusEncode(sample, BUFFER_SIZE);
}

bool PlugAudio::sendData(unsigned char *buff, unsigned int size) {
  unsigned char *sample;
  if ((sample = _opus.OpusDecode(buff, size)) == NULL)
    return false;
  return _audio.writeInput(sample);
}

PlugAudio::PlugAudio() : APlugin(AUDIO_ID) {
  // exception, think about it

  // init Audio Mic
  _audio.openInputStream();
  _audio.startStream(_audio.getInputStream());

  // init Audio HP
  _audio.openOutputStream();
  _audio.startStream(_audio.getOutputStream());

  // init encoder and Decode
  _opus.initEncode();
  _opus.initDecode();

}

PlugAudio::~PlugAudio() {
  // stop streams
  _audio.stopStream(_audio.getInputStream());
  _audio.stopStream(_audio.getOutputStream());


}
