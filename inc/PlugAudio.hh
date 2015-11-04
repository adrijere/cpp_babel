#ifndef _PLUGAUDIO_HH_
# define _PLUGAUDIO_HH_

#include "APlugin.hh"
#include "BabbelOpus.hh"
#include "BabbelAudio.hh"

class PlugAudio : public APlugin {
  private:
    BabbelOpus _opus;
    BabbelAudio _audio;

  public:
    unsigned char *getData();
    bool sendData(unsigned char *, unsigned int);
    void runTest();

  PlugAudio();
  ~PlugAudio();
};

#endif
