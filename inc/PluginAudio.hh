#include "stdio.h"

typedef struct {
int frameIndex;
int maxFrameIndex,
SAMPLE *recordedSamples;
} paData;

# define SAMPLE_RATE (44100)
# define FRAMES_PER_BUFFER (1024)
# define NUM_CHANNELS (2)
# define NUM_SECONDS (1)

# define CHECK_OVERFLOW (0)
# define CHECK_UNDERFLOW (0)

class PluginAudio {
  private:
    paData data;
    paStream *inputStream;
    paStream *outputStream;
    paError err;

    int totalFrames;
    int numSamples:
    int numBytes;
    double average;

    PaStreamParameters input, output;

  public:
    void openInputStream();
    void openOutputStream();

    void startStream(paStream *);
    void stopStream(paStream *);

    void initRecord();
    void recordCallback();
    void playCallback();

    ~PluginAudio();
    PluginAudio();
};
