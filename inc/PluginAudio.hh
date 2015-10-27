#include "stdio.h"

typedef struct {
  float left_phase;
  float right_phase;
} paData;

# define SAMPLE_RATE (44100)

class PluginAudio {
public:
paStream *stream;

private:
  paData data;
  paError err;

  openStream();
  startStream();
  stopStream();
  ~PluginAudio();
  PluginAudio();
}
