#include "PluginAudio"

void PluginAudio::recordCallback() {

}

void PluginAudio::playCallback() {

}

void PluginAudio::startStream(paStream *stream) {
  if (err = Pa_StartStream(stream) != paNoError) {
    std::cerr << "Portaudio error: " << std::endl;
  }
}

void PluginAudio::stopStream(paStream *stream) {
  if (err = Pa_StopStream(stream) != paNoError) {
    std::cerr << "Portaudio error: " << std::endl;
  }
}

void PluginAudio::openInputStream() {
  if (Pa_OpenStream(&outputStream, NULL, &output, SAMPLE_RATE, FRAMES_PER_BUFFER, paCLipOff, recordCallback, &inputData) != paNoError) {
    std::cerr << "PortAudio error:" << std::endl;
  }
}

void PluginAudio::openInputStream() {
  if (Pa_OpenStream(&inputStream, &input, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paCLipOff, recordCallback, &outputData) != paNoError) {
    std::cerr << "PortAudio error:" << std::endl;
  }
}

void PluginAudio::initData(paData &data) {
  for(i=0; i<numSamples; i++)
    data.recordedSamples[i] = 0;
}

PluginAudio::PluginAudio() {
  outputData.maxFrameIndex = inputData.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE;
  outputData.frameIndex = inputData.frameIndex = 0;
  numSamples = totalFrames * NUM_CHANNELS;
  numBytes = numSamples * sizeof(SAMPLE);

  // initialisation du buffer, a refaire en mode c++
  inputData.recordedSamples = (SAMPLE *) malloc( numBytes );
  outputData.recordedSamples = (SAMPLE *) malloc( numBytes );
  initRecord();

  // init portAudio
  if ((self.err = Pa_Initialize()) != paNoError) {
    std::cerr << "PortAudio error: " + Pa_GetErrorText(self.err) << std::endl;
    /* penser exception */
  }

  // init Input
  input.device = Pa_GetDefaultInputDevice();
  input.channelCount = NUM_CHANNELS;
  input.sampleFormat = PA_SAMPLE_TYPE;
  input.suggestedLatency = Pa_GetDeviceInfo(input.device)->defaultLowInputLatency;
  input.hostApiSpecificStreamInfo = NULL;

  // init Output
  output.device = Pa_GetDefaultOutputDevice();
  output.channelCount = NUM_CHANNELS;
  output.sampleFormat = PA_SAMPLE_TYPE;
  output.suggestLatency = Pa_GetDeviceInfo(output.device)->defaultLowOutputLatency;
  output.hostApiSpecificStreamInfo = NULL;

}

PluginAudio::~PluginAudio() {
  if (((self.err = Pa_Terminate)) != paNoError) {
    std::cerr << "PortAudio error:" + Pa_GetErrorText(self.err) << std::endl;
  }
}
