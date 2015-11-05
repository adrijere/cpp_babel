#ifndef _BABEL_AUDIO_HH_
# define _BABEL_AUDIO_HH_

#include "portaudio.h"

# define SAMPLE_RATE (48000)
# define FRAMES_PER_BUFFER (480)
# define FRAMES_SIZE (480)
# define NUM_CHANNELS (1)
# define SAMPLE_SIZE (3)
# define PA_SAMPLE_TYPE paInt16
# define BUFFER_SIZE (FRAMES_PER_BUFFER * SAMPLE_RATE)


class BabelAudio {
  private:
    PaStream *inputStream;
    PaStream *outputStream;
    unsigned char *readBuff;
    PaError err;

    PaStreamParameters input, output;

  public:
    bool openStream();

    PaStream *getInputStream();
    PaStream *getOutputStream();

    bool startStream(PaStream *);
    bool stopStream(PaStream *);

    void cleanBuff();

    bool writeInput(unsigned char *);
    unsigned char *readOutput();

    ~BabelAudio();
    BabelAudio();
};

#endif
