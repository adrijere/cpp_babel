#include <cstring>
#include <iostream>
#include "BabbelOpus.hh"

unsigned char *BabbelOpus::OpusDecode(unsigned char *data, unsigned int size) {
  unsigned char *ret = new unsigned char [MAX_FRAME_SIZE * CHANNELS];
  int frame_size = opus_decode(decode, data, size, output, FRAME_SIZE, 0);

  if (frame_size <= 0)
    return (NULL);
  std::memcpy(ret, output, size);
  return (ret);
}

unsigned char *BabbelOpus::OpusEncode(unsigned char *data, unsigned int size) {
  unsigned char *ret = new unsigned char[size];

  std::memcpy(input, data, size);
  nbBytes = opus_encode(encode, input, FRAME_SIZE, ret, size);
  if (nbBytes <= 0)
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

BabbelOpus::~BabbelOpus() {
  if (encode)
    opus_encoder_destroy(encode);
  if (decode)
    opus_decoder_destroy(decode);
}
