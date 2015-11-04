#ifndef _BABBEL_AUDIO_HH_
# define _BABBEL_AUDIO_HH_

#include "portaudio.h"

# define SAMPLE_RATE (48000)
# define FRAMES_PER_BUFFER (1024)
# define FRAMES_SIZE (960)
# define NUM_CHANNELS (2)
# define SAMPLE_SIZE (3)
# define NUM_SECONDS (15)
# define PA_SAMPLE_TYPE paInt32
# define BUFFER_SIZE (FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_RATE)


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
