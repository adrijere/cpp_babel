#ifndef _BABBEL_OPUS_HH_
# define _BABBEL_OPUS_HH_

#include "opus.h"

# define FRAME_SIZE (1024)
# define SAMPLE_RATE (44100)
# define CHANNELS (2)
# define MAX_FRAME_SIZE (6 * FRAME_SIZE)

class BabbelOpus {
  private:
    OpusEncoder *encode;
    OpusDecoder *decode;

    opus_int16 input[FRAME_SIZE*CHANNELS];
    opus_int16 output[MAX_FRAME_SIZE*CHANNELS];
    int nbBytes;
    int error;

  public:
    bool initDecode();
    bool initEncode();

    unsigned char *OpusDecode(unsigned char *, unsigned int);
    unsigned char *OpusEncode(unsigned char *, unsigned int);

    BabbelOpus() {};
    ~BabbelOpus() {};
};

#endif
