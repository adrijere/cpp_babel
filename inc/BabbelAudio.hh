#ifndef _BABBEL_AUDIO_HH_
# define _BABBEL_AUDIO_HH_

#include "portaudio.h"

# define SAMPLE_RATE (44100)
# define FRAMES_PER_BUFFER (1024)
# define NUM_CHANNELS (2)
# define SAMPLE_SIZE (3)
# define NUM_SECONDS (1)
# define PA_SAMPLE_TYPE paFloat32
# define BUFFER_SIZE (FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE)


class BabbelAudio {
  private:
    PaStream *inputStream;
    PaStream *outputStream;
    unsigned char *readBuff;
    PaError err;

    PaStreamParameters input, output;

  public:
    bool openInputStream();
    bool openOutputStream();

    PaStream *getInputStream();
    PaStream *getOutputStream();
    
    bool startStream(PaStream *);
    bool stopStream(PaStream *);

    void cleanBuff();

    bool writeInput(unsigned char *);
    unsigned char *readOutput();

    ~BabbelAudio();
    BabbelAudio();
};

#endif
