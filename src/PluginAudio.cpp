#include "PluginAudio"

int PluginAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData) {
   paTestData *data = const_cast<paTestData*>userData;
   const SAMPLE *rptr = const_cast<const SAMPLE*>inputBuffer;
   SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
   long framesToCalc;
   long i;
   int finished;
   unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

   (void) outputBuffer;
   (void) timeInfo;
   (void) statusFlags;
   (void) userData;

   if (framesLeft < framesPerBuffer) {
     framesToCalc = framesLeft;
     finished = paComplete;
   }
   else {
     framesToCalc = framesPerBuffer;
     finished = paContinue;
   }
   if (inputBuffer == NULL) {
     for(i=0; i<framesToCalc; i++) {
       *wptr++ = SAMPLE_SILENCE;  /* left */
       if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
      }
   }
   else {
     for( i=0; i<framesToCalc; i++ ) {
       *wptr++ = *rptr++;  /* left */
       if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
      }
  }
   data->frameIndex += framesToCalc;
   return finished;
}

int PluginAudio::playCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData) {
  paData *data = static_cast<paData *>(userData);
  SAMPLE *rptr = &data->recordedSamples[data->framIndex * NUM_CHANNELS];
  SAMPLE *wptr = static_cast<SAMPLE *>outputBuffer;
  int finish;
  unsigned int i;
  unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

  (void) inputBuffer;
  (void) timeInfo;
  (void) statusFLags;
  (void) userDara;

  if (framesLeft < framesPerBuffer) {
    for (i = 0; i<framesLeft; i++) {
      *wptr++ = *rptr++;
      if (NUM_CHANNELS == 2) *wptr++ = *rptr++;
    }
    for (; i<framesPerBuffer; i++) {
      *wptr++ = 0;
      if (NUM_CHANNELS == 2) *wptr++ = 0;
    }
  data->frameIndex += framesLeft;
  finished = paComplete;
  }
  else {
    for( i=0; i<framesPerBuffer; i++ )
    {
        *wptr++ = *rptr++;  /* left */
        if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
    }
    data->frameIndex += framesPerBuffer;
    finished = paContinue;
  }
  return finished;
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

void PluginAudio::openOutputStream() {
  if (Pa_OpenStream(&outputStream, NULL, &output, SAMPLE_RATE, FRAMES_PER_BUFFER, paCLipOff, &PluginAudio::playCallback, this) != paNoError) {
    std::cerr << "PortAudio error:" << std::endl;
  }
}

void PluginAudio::openInputStream() {
  if (Pa_OpenStream(&inputStream, &input, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paCLipOff, &PluginAudio::recordCallback, this) != paNoError) {
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

  // initialisation du buffer
  inputData.recordedSamples = static_cast<SAMPLE *>(new char[numBytes]);
  outputData.recordedSamples = static_cast<SAMPLE *>(new char[numBytes]);
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
  delete[] inputData.recordedSamples;
  delete[] outputData.recordedSamples;
}
