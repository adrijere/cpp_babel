#include <cstring>
#include "BabbelOpus.hh"

unsigned char *BabbelOpus::OpusDecode(unsigned char *data, unsigned int size) {
  unsigned char *ret = new unsigned char [MAX_FRAME_SIZE * CHANNELS * 2];
  int   frame_size = opus_decode(decode, data, size, output, MAX_FRAME_SIZE * CHANNELS * 2, 0);

  if (frame_size < 0)
    return (NULL);
  memcpy(ret, output, size);
  return (ret);
}

unsigned char *BabbelOpus::OpusEncode(unsigned char *data, unsigned int size) {
  unsigned char *ret = new unsigned char[size];

  memcpy(input, data, size);
  nbBytes = opus_encode(encode, input, FRAME_SIZE, ret, size);
  if (nbBytes < 0)
    return NULL;
  return (ret);
}

bool BabbelOpus::initDecode() {
  if ((encode = opus_encoder_create(SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_VOIP, &error)) == NU\
LL)
    return false;
  return true;
}

bool BabbelOpus::initEncode() {
  if ((decode = opus_decoder_create(SAMPLE_RATE, CHANNELS, &error)) == NULL)
    return (false);
  return true;
}
