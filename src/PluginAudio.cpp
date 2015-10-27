#include "PluginAudio"

PluginAudio::openStream() {

}

PluginAudio::stopStream() {

}

PluginAudio::startStream() {
  
}

PluginAudio::PluginAudio() {
  if ((self.err = Pa_Initialize()) != paNoError) {
    std::cerr << "PortAudio error: " + Pa_GetErrorText(self.err) << std::endl;
  }
}

PluginAudio::~PluginAudio() {
  if (((self.err = Pa_Terminate)) != paNoError) {
    std::cerr << "PortAudio error:" + Pa_GetErrorText(self.err) << std::endl;
  }
}
