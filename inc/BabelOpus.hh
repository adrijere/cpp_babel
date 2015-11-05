#ifndef _BABEL_OPUS_HH_
# define _BABEL_OPUS_HH_

#include "opus.h"

# define FRAME_SIZE (480)
# define SAMPLE_RATE (48000)
# define CHANNELS (1)
# define MAX_FRAME_SIZE (6 * FRAME_SIZE)

class BabelOpus {
  private:
    OpusEncoder *encode;
    OpusDecoder *decode;

    opus_int16 *input;
    opus_int16 *output;

    unsigned char *retDecode;
    int error;

  public:
    struct EncodePack {
      int nbBytes;
      unsigned char pack[960];
    };

    bool initDecode();
    bool initEncode();

    bool OpusDecode(EncodePack *);
    bool OpusEncode(unsigned char *, unsigned int);

    unsigned char *getDec();
    EncodePack *getEnc();

    BabelOpus();
    ~BabelOpus();
  private:

  EncodePack retEncode;
};

#endif
