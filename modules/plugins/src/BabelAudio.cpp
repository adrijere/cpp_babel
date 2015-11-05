#include <iostream>
#include "BabelAudio.hh"

bool BabelAudio::writeInput(unsigned char *buff) {
  if ((err = Pa_WriteStream(outputStream, buff, FRAMES_PER_BUFFER)) != paNoError)
    return (false);
  return (true);
}

unsigned char *BabelAudio::readOutput() {
  if ((err = Pa_ReadStream(inputStream, readBuff, FRAMES_PER_BUFFER )) != paNoError) {
    std::cerr << "Portaudio error: ";
    std::cerr << Pa_GetErrorText(err) << std::endl;
    return (NULL);
  }
  return (readBuff);
}

bool BabelAudio::startStream(PaStream *stream) {
  if ((err = Pa_StartStream(stream)) != paNoError) {
    std::cerr << "PortAudio error: ";
    std::cerr << Pa_GetErrorText(err) << std::endl;
    return false;
  }
  return true;
}

bool BabelAudio::stopStream(PaStream *stream) {
  if ((err = Pa_StopStream(stream)) != paNoError) {
    std::cerr << "PortAudio error: ";
    std::cerr << Pa_GetErrorText(err) << std::endl;
    return false;
  }
  return true;
}

bool BabelAudio::openStream() {
  input.device = Pa_GetDefaultInputDevice();
  input.channelCount = NUM_CHANNELS;
  input.sampleFormat = PA_SAMPLE_TYPE;
  input.suggestedLatency = Pa_GetDeviceInfo(input.device)->defaultLowInputLatency;
  input.hostApiSpecificStreamInfo = NULL;

  output.device = Pa_GetDefaultOutputDevice();
  output.channelCount = NUM_CHANNELS;
  output.sampleFormat = PA_SAMPLE_TYPE;
  output.suggestedLatency = Pa_GetDeviceInfo(output.device)->defaultLowOutputLatency;
  output.hostApiSpecificStreamInfo = NULL;

  readBuff = new unsigned char[BUFFER_SIZE];
  cleanBuff();
  if (Pa_OpenStream(&inputStream, &input, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL) != paNoError)
    return false;
    if (Pa_OpenStream(&outputStream, NULL, &output, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL) != paNoError)
    return false;
  return true;
}

void BabelAudio::cleanBuff() {
  for(unsigned int i=0; i < BUFFER_SIZE; ++i)
    readBuff[i] = 0;
}

PaStream *BabelAudio::getInputStream() {
  return inputStream;
}

PaStream *BabelAudio::getOutputStream() {
  return outputStream;
}

BabelAudio::BabelAudio() {
  readBuff =  NULL;
  if ((err = Pa_Initialize()) != paNoError) {
    std::cerr << "PortAudio error:";
    std::cerr << Pa_GetErrorText(err) << std::endl;
    /* penser exception */
  }
}

BabelAudio::~BabelAudio() {
  if (((err = Pa_Terminate())) != paNoError) {
    std::cerr << "PortAudio error:";
    std::cerr << Pa_GetErrorText(err) << std::endl;
    // penser exception
  }
  if (readBuff != NULL) delete[] readBuff;
}
