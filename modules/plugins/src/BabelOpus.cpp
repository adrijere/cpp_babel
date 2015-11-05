#include <cstring>
#include <iostream>
#include "BabelOpus.hh"

bool BabelOpus::OpusDecode(EncodePack *reserve) {
  // voir const
  int frame_size = opus_decode(decode, reserve->pack, reserve->nbBytes, output, FRAME_SIZE, 0);
  if (frame_size <= 0)
    return (false);
  std::memcpy(retDecode, output, FRAME_SIZE * SAMPLE_RATE);
  return (true);
}

bool BabelOpus::OpusEncode(unsigned char *data, unsigned int size) {
  std::memcpy(input, data, size);
  retEncode.nbBytes = opus_encode(encode, input, FRAME_SIZE, retEncode.pack, size);
  if (retEncode.nbBytes <= 0)
    return (false);
  return (true);
}


bool BabelOpus::initDecode() {
  input = new opus_int16[(FRAME_SIZE * SAMPLE_RATE)];
  if ((encode = opus_encoder_create(SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_VOIP, &error)) == NULL)
    return false;
  return true;
}

bool BabelOpus::initEncode() {
  output = new opus_int16[(FRAME_SIZE * SAMPLE_RATE)];
  if ((decode = opus_decoder_create(SAMPLE_RATE, CHANNELS, &error)) == NULL)
    return (false);
  return true;
}

BabelOpus::EncodePack *BabelOpus::getEnc() {
  // a voir si const
  return &retEncode;
}

unsigned char *BabelOpus::getDec() {
  // a voir si const
  return retDecode;
}

BabelOpus::BabelOpus() {
retDecode = new unsigned char [FRAME_SIZE * SAMPLE_RATE];
}

BabelOpus::~BabelOpus() {
  if (encode)
    opus_encoder_destroy(encode);
  if (decode)
    opus_decoder_destroy(decode);
}
